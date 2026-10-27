#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The rest limit is an int (800, or 10 while elapsedTicks <= 100) compared with the sign-extended counter
        // (movsx; cmp eax, ecx at 0x52B848).
        // FUNCTION: STRONGHOLDCRUSADER 0x0052B630
        void TribesState::updateCamelTribeBehavior(int tribeID)
        {
            BOOLEnum const isFree = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeFreeOfMovementState2Units, this)(
                tribeID, this->tribes[tribeID].uid);
            this->tribes[tribeID].elapsedTicks++;
            this->tribes[tribeID].unkIsAnimalTribe = 1;
            if (this->tribes[tribeID].elapsedTicks >= 8000) {
                this->tribes[tribeID].elapsedTicks = 4000;
            }
            if (isFree != FALSE
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::trySpawnAdditionalWildlifeForTribe,
                       this)(tribeID, 1000, 10, UT_CAMELSHBEAR)
                    != 0) {
                this->tribes[tribeID].wildlifeMoveState = 1;
                this->tribes[tribeID].behaviorTickCounter = 0;
                return;
            }
            short const moveState = this->tribes[tribeID].wildlifeMoveState;
            if (moveState == 0) {
                int const leader = this->tribes[tribeID].leaderUnitID;
                this->tribes[tribeID].behaviorTickCounter = 0;
                this->tribes[tribeID].wildlifeMoveState = 2;
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
            if (moveState == 1) {
                this->tribes[tribeID].behaviorTickCounter = 0;
                this->tribes[tribeID].wildlifeMoveState = 2;
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
                this->tribes[tribeID].tribeBehaviorType = STBT_1;
                return;
            }
            short const behaviorType = this->tribes[tribeID].tribeBehaviorType;
            if (behaviorType == STBT_NONE) {
                if (this->tribes[tribeID].behaviorTickCounter++ == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(tribeID, 2, 1);
                    if (this->tribes[tribeID].rallyPointCount > 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                        int const rallyCount = this->tribes[tribeID].rallyPointCount;
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
                int restTicks = 800;
                if (this->tribes[tribeID].elapsedTicks <= 100) {
                    restTicks = 10;
                }
                this->tribes[tribeID].behaviorTickCounter++;
                if (this->tribes[tribeID].behaviorTickCounter >= restTicks) {
                    this->tribes[tribeID].tribeBehaviorType = STBT_NONE;
                    this->tribes[tribeID].behaviorTickCounter = 0;
                }
            }
        }

    }
}
}
