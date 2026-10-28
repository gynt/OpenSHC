#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // spawnDeerLionOrRabbit's result is ignored (0x52B430). The 150-tick compare uses the incremented counter
        // (cmp cx, 0x96 at 0x52B577). The wildlife cell is indexed flat as (x / 10) * 40 + y / 10 (lea at 0x52B3E4);
        // grid[0][cellIndex] reproduces that addressing, grid[x / 10][y / 10] compiles differently.
        // FUNCTION: STRONGHOLDCRUSADER 0x0052B390
        void TribesState::updateRabbitTribeBehavior(int tribeID)
        {
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            int const leaderX = DAT_UnitsState::instance.units[leaderUnitID].x;
            int const leaderY = DAT_UnitsState::instance.units[leaderUnitID].y;
            int const cellIndex = (leaderX / 10) * 40 + leaderY / 10;
            int const disturbedTileCount = DAT_WildlifeState::instance.grid[0][cellIndex].disturbedTileCount;
            int const flag20000000TileCount = DAT_WildlifeState::instance.grid[0][cellIndex].flag20000000TileCount;
            BOOLEnum const isFree = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeFreeOfMovementState2Units, this)(
                tribeID, this->tribes[tribeID].uid);
            this->tribes[tribeID].unkIsAnimalTribe = 1;
            int spawnInterval = 80;
            if (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation != 0) {
                spawnInterval = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                tribeID, spawnInterval, UT_RABBIT);
            if (this->tribes[tribeID].wildlifeMoveState == 0) {
                int const leader = this->tribes[tribeID].leaderUnitID;
                this->tribes[tribeID].wildlifeMoveState = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                    DAT_UnitsState::instance.units[leader].x, DAT_UnitsState::instance.units[leader].y, 0, 0,
                    Instructions::UMSE_0);
                this->tribes[tribeID].tribeBehaviorType = STBT_1;
                return;
            }
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                this->tribes[tribeID].elapsedTicks = 0;
                return;
            }
            short const alarmTimer = this->tribes[tribeID].wildlifeAlarmTimer;
            if (alarmTimer != 0) {
                if (alarmTimer == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(tribeID, 3, 0);
                    if (this->tribes[tribeID].rallyPointCount <= 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 3, 1);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::scatterTribeUnitsRandomly, this)(tribeID);
                }
                this->tribes[tribeID].wildlifeAlarmTimer++;
                if (this->tribes[tribeID].wildlifeAlarmTimer >= 3000) {
                    this->tribes[tribeID].wildlifeAlarmTimer = 0;
                }
                return;
            }
            short const behaviorType = this->tribes[tribeID].tribeBehaviorType;
            if (behaviorType == STBT_NONE) {
                if (this->tribes[tribeID].behaviorTickCounter++ == 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::buildRallyPointPathForTribe,
                            DAT_WildlifeState::ptr)(tribeID, 4)
                        == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 2, 1);
                    }
                    if (this->tribes[tribeID].rallyPointCount > 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::applyLadderDestructionToTribeUnits, this)(tribeID);
                    }
                } else if (this->tribes[tribeID].behaviorTickCounter == 150) {
                    short const rallyCount = this->tribes[tribeID].rallyPointCount;
                    if (rallyCount > 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                            tribeID, this->tribes[tribeID].rallyPointArray[rallyCount - 1][0],
                            this->tribes[tribeID].rallyPointArray[rallyCount - 1][1], 0, 0);
                    }
                } else if (isFree != FALSE) {
                    this->tribes[tribeID].tribeBehaviorType = STBT_1;
                    this->tribes[tribeID].behaviorTickCounter = 0;
                }
            } else if (behaviorType == STBT_1) {
                if (flag20000000TileCount != 0) {
                    this->tribes[tribeID].wildlifeWanderInterval = 20;
                } else if (disturbedTileCount > 20) {
                    this->tribes[tribeID].wildlifeWanderInterval = 20;
                } else {
                    this->tribes[tribeID].wildlifeWanderInterval = 400;
                }
                this->tribes[tribeID].behaviorTickCounter++;
                if (this->tribes[tribeID].behaviorTickCounter >= this->tribes[tribeID].wildlifeWanderInterval) {
                    this->tribes[tribeID].tribeBehaviorType = STBT_NONE;
                    this->tribes[tribeID].behaviorTickCounter = 0;
                }
            }
        }

    }
}
}
