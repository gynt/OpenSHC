#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532BA0
        void UnitsState::recomputeTroopValuesForPlayer(int playerID)
        {
            int _campfireX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
            int _campfireY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
            DAT_GameState::instance.playerDataArray[playerID].enemyListCount = 0;
            DAT_GameState::instance.playerDataArray[playerID].totalEnemyUnitsCount = 0;
            DAT_GameState::instance.playerDataArray[playerID].sumOfTotalEnemyUnitsCount = 0;
            for (int ownerID = 1; ownerID < 9; ++ownerID) {
                DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValueByPlayerID[ownerID] = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue = 0;
            DAT_GameState::instance.playerDataArray[playerID].totalTeamTroopValue = 0;
            DAT_GameState::instance.playerDataArray[playerID].totalEnemyNonRangedTroopValue = 0;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY && playerID != 0
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                5000, '\0', DAT_GameState::instance.playerDataArray[playerID].enemyIDArray);
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].isHiddenInBuilding != 0) {
                    continue;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                        continue;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(_campfireX, _campfireY,
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 60) {
                        DAT_GameState::instance.playerDataArray[playerID].totalTeamTroopValue += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                            (UnitType)(short)DAT_UnitsState::instance.units[unitID].unitType);
                    }
                    continue;
                }
                /* unit not in our team */
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_TRADER:
                case OpenSHC::Map::Units::UT_TRADERHORSE:
                case OpenSHC::Map::Units::UT_CAMELSHBEAR:
                case OpenSHC::Map::Units::UT_GHOST:
                case OpenSHC::Map::Units::UT_MOTHER:
                case OpenSHC::Map::Units::UT_CHILD:
                    continue;
                }
                /* units of player 0 are not counted, but still stored in the enemy list */
                if (this->units[unitID].owner != 0) {
                    switch (this->units[unitID].unitType) {
                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                    case OpenSHC::Map::Units::UT_S_TOWER:
                    case OpenSHC::Map::Units::UT_S_SHIELD:
                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                        /* count of currently manning engineers */
                        if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            == 0) {
                            continue;
                        }
                    }
                    if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                        DAT_GameState::instance.playerDataArray[playerID].totalEnemyUnitsCount += 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(_campfireX, _campfireY,
                            DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < 60) {
                            int _enemyOwner = DAT_UnitsState::instance.units[unitID].owner;
                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_enemyOwner] != -1
                                || DAT_GameSynchronyState::instance.currentAIArray[_enemyOwner] == 0
                                || DAT_UnitsState::instance.units[unitID].siegeTargetPlayerID == playerID) {
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .totalEnemyTroopValueByPlayerID[DAT_UnitsState::instance.units[unitID].owner]
                                    += MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)(
                                        (UnitType)(short)DAT_UnitsState::instance.units[unitID].unitType);
                                DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue
                                    += MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)(
                                        (UnitType)(short)DAT_UnitsState::instance.units[unitID].unitType);
                                if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_E_ARCHER
                                    && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_E_XBOW
                                    && DAT_UnitsState::instance.units[unitID].unitType
                                        != OpenSHC::Map::Units::UT_A_ARCHER
                                    && DAT_UnitsState::instance.units[unitID].unitType
                                        != OpenSHC::Map::Units::UT_A_SLINGER
                                    && DAT_UnitsState::instance.units[unitID].unitType
                                        != OpenSHC::Map::Units::UT_A_HARCHER
                                    && DAT_UnitsState::instance.units[unitID].unitType
                                        != OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                                    DAT_GameState::instance.playerDataArray[playerID].totalEnemyNonRangedTroopValue
                                        += MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                            DAT_TroopValueState::ptr)(
                                            (UnitType)(short)DAT_UnitsState::instance.units[unitID].unitType);
                                }
                            }
                        }
                    } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        DAT_GameState::instance.playerDataArray[playerID].totalEnemyUnitsCount += 1;
                    }
                }
                int _enemySlot;
                if (DAT_GameState::instance.playerDataArray[playerID].enemyListCount >= 2499) {
                    int _randomSlot = SEC_RNG::instance.currentNumber2 % 2500;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    if (_randomSlot >= 2499) {
                        continue;
                    }
                    _enemySlot = _randomSlot;
                } else {
                    _enemySlot = DAT_GameState::instance.playerDataArray[playerID].enemyListCount++;
                }
                DAT_GameState::instance.playerDataArray[playerID].enemyIDArray[_enemySlot] = (short)unitID;
                DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[playerID][_enemySlot]
                    = DAT_UnitsState::instance.units[unitID].uid;
            }
            DAT_GameState::instance.playerDataArray[playerID].sumOfTotalEnemyUnitsCount
                += DAT_GameState::instance.playerDataArray[playerID].totalEnemyUnitsCount;
        }

    }
}
}
