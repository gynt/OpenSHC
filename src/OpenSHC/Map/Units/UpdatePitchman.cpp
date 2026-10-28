#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00551980
    void Units::UpdatePitchman()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeSpecificRestingState = 5;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                    DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                    DAT_UnitsState::instance.units[unitID].isFadeActive = 0;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded = (DestinationNeededEnum)2;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber += 1;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber < 10) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                    DAT_UnitsState::ptr)(unitID, 1)
                != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                    = DAT_BuildingsState::instance
                          .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .workplaceOrHomeBuildingID]
                          .uid;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 1;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animPitchmanFreetime[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            int idle;
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x128;
                DAT_UnitAnimationFinished::instance = 1;
                idle = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x120;
                idle = DAT_UnitAnimationFinished::instance;
            }
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 7) == 0 && idle != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL(OpenSHC::Map::Units_Func::UpdateWorker_ConsiderTakingFearFactorBreak)(unitID) != FALSE) {
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    != FALSE) {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 2;
                DAT_UnitsState::instance.units[unitID].stateAfterFade = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 1)
                != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID, 3);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 32;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeAlphaStep
                    = 0xfe;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].faceViewer = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            }
            return;
        }
        if (state == (UnitState)2) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 20) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            int storage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_PITCH, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(storage, 1)
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)
                != FALSE) {
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)storage;
                DAT_UnitsState::instance.units[unitID].targetUID = DAT_BuildingsState::instance.buildings[storage].uid;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
                DAT_UnitsState::instance.units[unitID].resourceToDeposit
                    = (short)MACRO_CALL(OpenSHC::Map::Units_Func::ComputeGoodsProduced)(unitID, 1, TRUE);
            }
            return;
        }
        if (state == (UnitState)3) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 5) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::canBuildingStoreTheAmount,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_PITCH, 16)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_PITCH, 1, 16, 1);
                DAT_GameSynchronyState::instance.finalResults
                    .finalPitchProduced[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner] += 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_PITCH);
            } else {
                int storage = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_PITCH, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(storage, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)storage;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[storage].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0);
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                }
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit <= 0) {
                MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, TRUE);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(unitID, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == (UnitState)121) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(unitID);
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FADE_TRANSITION) {
            DAT_UnitsState::instance.units[unitID].fadeLevel
                += DAT_UnitsState::instance.units[unitID].fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel >= 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 16) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].stateAfterFade;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        unitID);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 2);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animDeathPitchman[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x110;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x100;
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
                      .animDeathPitchman[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x120;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x110;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (DAT_UnitsState::instance.units[unitID].state.generic == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                if (DAT_UnitsState::instance.units[unitID].isDisbanded == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::setLastEncounteredTroopUnit,
                        DAT_GameState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitID);
                    unitID = DAT_CurrentUnitSlotID::instance;
                }
            }
            DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID]
                .aiRestaffCountdown = 4000;
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
