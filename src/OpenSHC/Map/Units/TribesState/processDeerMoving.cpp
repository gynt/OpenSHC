#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Wildlife cell = flat index (x / 10) * 40 + y / 10 of the leader (signed division, lea at 0x52ADA4), written as
        // grid[0][cellIndex]. size > 30 is a signed short compare (jle at 0x52ADDE). On alarm the second rally search
        // only runs when the first found nothing (jg at 0x52AF4B skips it).
        // FUNCTION: STRONGHOLDCRUSADER 0x0052AD50
        void TribesState::processDeerMoving(int tribeID)
        {
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            int const leaderX = DAT_UnitsState::instance.units[leaderUnitID].x;
            int const leaderY = DAT_UnitsState::instance.units[leaderUnitID].y;
            int const cellIndex = (leaderX / 10) * 40 + leaderY / 10;
            int const disturbedTileCount = DAT_WildlifeState::instance.grid[0][cellIndex].disturbedTileCount;
            int const dangerCount = DAT_WildlifeState::instance.grid[0][cellIndex].lionCount + DAT_WildlifeState::instance.grid[0][cellIndex].panicSourceCount;
            int const flag20000000TileCount = DAT_WildlifeState::instance.grid[0][cellIndex].flag20000000TileCount;
            short const size = this->tribes[tribeID].size;
            this->tribes[tribeID].unkIsAnimalTribe = 1;
            if (size > 30) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::trimTribeToSize, this)(tribeID, 30);
                this->tribes[tribeID].wildlifeMinSize = 15;
                this->tribes[tribeID].wildlifeMaxSize = 60;
            } else {
                this->tribes[tribeID].wildlifeMinSize = size / 2;
                this->tribes[tribeID].wildlifeMaxSize = size * 2;
            }
            if (dangerCount != 0 && this->tribes[tribeID].wildlifeAlarmTimer == 0) {
                this->tribes[tribeID].wildlifeAlarmTimer = 1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                    tribeID, 100, UT_ANTELOPESHDEER)
                != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                    DAT_WildlifeState::ptr)(tribeID, 2, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                    this->tribes[tribeID].rallyPointArray[this->tribes[tribeID].currentRallyPointIndex][0],
                    this->tribes[tribeID].rallyPointArray[this->tribes[tribeID].currentRallyPointIndex][1], 0, 0, Instructions::UMSE_0);
                this->tribes[tribeID].currentRallyPointIndex++;
                if (this->tribes[tribeID].currentRallyPointIndex >= this->tribes[tribeID].rallyPointCount) {
                    this->tribes[tribeID].rallyPointCount = 0;
                    this->tribes[tribeID].tribeBehaviorType = STBT_1;
                }
                return;
            }
            if (this->tribes[tribeID].wildlifeMoveState == 0) {
                int const leader = this->tribes[tribeID].leaderUnitID;
                this->tribes[tribeID].wildlifeMoveState = 1;
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
                        DAT_WildlifeState::ptr)(tribeID, 5, 0);
                    if (this->tribes[tribeID].rallyPointCount <= 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 5, 1);
                    }
                    if (this->tribes[tribeID].rallyPointCount > 0) {
                        int const leader = this->tribes[tribeID].leaderUnitID;
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[leader].x, DAT_UnitsState::instance.units[leader].y,
                            OpenSHC::DE::SHCDE::FX_DEER_RUN);
                        int const rallyCount = this->tribes[tribeID].rallyPointCount;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                            tribeID, this->tribes[tribeID].rallyPointArray[rallyCount - 1][0],
                            this->tribes[tribeID].rallyPointArray[rallyCount - 1][1], 0, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::scatterTribeUnitsRandomly, this)(
                            tribeID);
                    }
                }
                this->tribes[tribeID].wildlifeAlarmTimer++;
                if (this->tribes[tribeID].wildlifeAlarmTimer >= 800) {
                    this->tribes[tribeID].wildlifeAlarmTimer = 0;
                }
                return;
            }
            short const behaviorType = this->tribes[tribeID].tribeBehaviorType;
            if (behaviorType == STBT_NONE) {
                if (flag20000000TileCount != 0) {
                    this->tribes[tribeID].wildlifeWanderInterval = 200;
                }
                if (disturbedTileCount > 20) {
                    this->tribes[tribeID].wildlifeWanderInterval = 200;
                }
                this->tribes[tribeID].behaviorTickCounter++;
                if (this->tribes[tribeID].behaviorTickCounter < this->tribes[tribeID].wildlifeWanderInterval) {
                    return;
                }
                this->tribes[tribeID].behaviorTickCounter = 0;
                this->tribes[tribeID].wildlifeWanderInterval = (4 - (SEC_RNG::instance.currentNumber2 & 3)) * 200;
                if (this->tribes[tribeID].rallyPointCount <= 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(tribeID, 5, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                    tribeID, this->tribes[tribeID].rallyPointArray[this->tribes[tribeID].currentRallyPointIndex][0],
                    this->tribes[tribeID].rallyPointArray[this->tribes[tribeID].currentRallyPointIndex][1], 0, 0);
                this->tribes[tribeID].currentRallyPointIndex++;
                if (this->tribes[tribeID].currentRallyPointIndex >= this->tribes[tribeID].rallyPointCount) {
                    this->tribes[tribeID].tribeBehaviorType = STBT_1;
                    this->tribes[tribeID].rallyPointCount = 0;
                }
            } else if (behaviorType == STBT_1) {
                this->tribes[tribeID].behaviorTickCounter++;
                if (this->tribes[tribeID].behaviorTickCounter == 800) {
                    this->tribes[tribeID].behaviorTickCounter = 0;
                    this->tribes[tribeID].tribeBehaviorType = STBT_NONE;
                }
            }
        }

    }
}
}
