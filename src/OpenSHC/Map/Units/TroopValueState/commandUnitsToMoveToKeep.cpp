#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using namespace OpenSHC::Map::Buildings;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C800
        void TroopValueState::commandUnitsToMoveToKeep()
        {
            int const playerID = DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID;
            int const keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
            if (keepID <= 0) {
                return;
            }
            int x;
            int y;
            if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_MANORHOUSE) {
                x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                y = DAT_BuildingsState::instance.buildings[keepID].y + 8;
            } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STONEKEEP) {
                x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                y = DAT_BuildingsState::instance.buildings[keepID].y + 3;
            } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STRONGHOLD) {
                x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                y = DAT_BuildingsState::instance.buildings[keepID].y + 3;
            } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_KEEPFOUR) {
                x = DAT_BuildingsState::instance.buildings[keepID].x + 4;
                y = DAT_BuildingsState::instance.buildings[keepID].y + 4;
            } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_KEEPFIVE) {
                x = DAT_BuildingsState::instance.buildings[keepID].x + 5;
                y = DAT_BuildingsState::instance.buildings[keepID].y + 5;
            } else {
                return;
            }
            int const swordTribeID
                = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
            DAT_TribesState::instance.tribes[swordTribeID].tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
            int const archerTribeID
                = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
            DAT_TribesState::instance.tribes[archerTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        != FALSE
                    && (DAT_UnitsState::instance.units[unitID].unitType == UT_E_MACE
                        || DAT_UnitsState::instance.units[unitID].unitType == UT_E_SWORD
                        || DAT_UnitsState::instance.units[unitID].unitType == UT_E_SPEAR
                        || ((DAT_UnitsState::instance.units[unitID].unitType == UT_E_ARCHER
                                || DAT_UnitsState::instance.units[unitID].unitType == UT_E_XBOW)
                            && (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile]
                                   & 0x10000100)
                                == 0))) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 30) {
                        MACRO_CALL_MEMBER(TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                            unitID, DAT_UnitsState::instance.units[unitID].tribeID);
                        if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_SWORD) {
                            MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                                unitID, swordTribeID);
                        } else {
                            MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                                unitID, archerTribeID);
                        }
                    }
                }
            }
            if (DAT_TribesState::instance.tribes[swordTribeID].size <= 0) {
                DAT_TribesState::instance.tribes[swordTribeID].tribeState = 3;
            } else {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    swordTribeID, x, y + 1, 0, 0, Instructions::UMSE_0);
            }
            if (DAT_TribesState::instance.tribes[archerTribeID].size <= 0) {
                DAT_TribesState::instance.tribes[archerTribeID].tribeState = 3;
            } else {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    archerTribeID, x, y, 0, 0, Instructions::UMSE_0);
            }
        }

    }
}
}
