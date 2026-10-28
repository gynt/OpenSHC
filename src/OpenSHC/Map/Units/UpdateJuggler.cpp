#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00549090
    void Units::UpdateJuggler()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[unitID].owner]
            .nonInteractiveUnitCountThisTick += 1;
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[unitID].aimPitchOrLifetimeTicks += 1;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[unitID].owner].areCarnivalUnitsPresent
            = TRUE;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
                DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xff;
                DAT_UnitsState::instance.units[unitID].stateAfterFade
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
                DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].aimPitchOrLifetimeTicks >= 2000) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                return;
            }
            // targetingType counts the steps of the performance
            switch (DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep) {
            case 0:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath, DAT_UnitsState::ptr)(
                    unitID, 2, 0, 1);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, 8);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)120;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep += 1;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                switch (SEC_RNG::instance.currentNumber2 & 3) {
                case 0:
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                    break;
                case 1:
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
                    break;
                case 2:
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    break;
                case 3:
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    break;
                }
                DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep += 1;
                break;
            case 5:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath, DAT_UnitsState::ptr)(
                    unitID, 1, 0, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)120;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                    = (SEC_RNG::instance.currentNumber2 & 1) + 3;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x12;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryY,
                    0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                    != FALSE
                && DAT_UnitsState::instance.units[unitID].destinationNeeded
                    == OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)120) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x12;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryY,
                    0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::isUnitMovementIdle, DAT_UnitsState::ptr)(unitID)
                    != FALSE
                && DAT_UnitsState::instance.units[unitID].destinationNeeded
                    == OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)2) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerAct2[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x90;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)3) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerAct3[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x90;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerAct4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0xa2;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerAct5Start[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x90;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerAct5End[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0xb4;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0xdc;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0xc4;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJugglerDeathOther[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0xf4;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0xdc;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
