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

    // FUNCTION: STRONGHOLDCRUSADER 0x00554CC0
    void Units::UpdateMiller()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int workplace = DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID;
        DAT_UnitsState::instance.units[unitID].unitTypeSpecificRestingState = 1;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        DAT_BuildingsState::instance.buildings[workplace].workers[DAT_UnitsState::instance.units[unitID].workerIndex]
            = (short)unitID;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
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
                DAT_UnitsState::instance.units[unitID].destinationNeeded = (DestinationNeededEnum)2;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // idling at the mill
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 1;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].substate == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(unitID);
            }
            short substate = DAT_UnitsState::instance.units[unitID].substate;
            if (substate == 100) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animMillerStandUp[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (substate == 0x65) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animMillerSitDown[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (substate != 0x6a && substate == 0x6b) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animMillerIdleSub6b[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animMillerIdleSub6a[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x189;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x180;
            }
            int idle = DAT_UnitAnimationFinished::instance;
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 0) != 0 || idle == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x65) {
                DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                DAT_UnitsState::instance.units[unitID].seated = 1;
            } else if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                DAT_UnitsState::instance.units[unitID].seated = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].substate += 1;
                if (DAT_UnitsState::instance.units[unitID].substate > 0x6b) {
                    DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            int granary = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(
                OpenSHC::Game::Resources::RT_WHEAT, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(granary, 1)
                != 0) {
                int id = DAT_CurrentUnitSlotID::instance;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(id)
                    == 0) {
                    DAT_UnitsState::instance.units[id].targetID_OR_targetBuildingID = (short)granary;
                    DAT_UnitsState::instance.units[id].targetUID = DAT_BuildingsState::instance.buildings[granary].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                        DAT_UnitsState::ptr)(id, DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                }
            }
            return;
        }
        if (state == (UnitState)2) {
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
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].substate = -1;
            }
            return;
        }
        if (state == (UnitState)3) {
            // fetching wheat from the granary
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            int granaryUID = DAT_UnitsState::instance.units[unitID].targetUID;
            int granary = DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(granary, granaryUID, OpenSHC::Game::Resources::RT_WHEAT)
                <= 0) {
                granary = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_WHEAT, 1, DAT_UnitsState::instance.units[unitID].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(granary, 1)
                    != 0) {
                    int id = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[id].targetID_OR_targetBuildingID = (short)granary;
                    DAT_UnitsState::instance.units[id].targetUID = DAT_BuildingsState::instance.buildings[granary].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                        DAT_UnitsState::ptr)(id, DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0);
                    return;
                }
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                    DAT_BuildingsState::ptr)(granary, granaryUID, OpenSHC::Game::Resources::RT_WHEAT, -1, 32, 1);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].resourceToDeposit
                    = (short)MACRO_CALL(OpenSHC::Map::Units_Func::ComputeGoodsProduced)(unitID, 1, FALSE);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[unitID].workerIndex + 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0);
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workerIndex + 1)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // carrying wheat to the mill
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId != 0
                || DAT_BuildingsState::instance.buildings[workplace].subAnimState2 != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId = (short)unitID;
            DAT_BuildingsState::instance.buildings[workplace].typeSpecificTimer = 300;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(unitID);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // grinding inside the mill
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId = (short)unitID;
            if (DAT_BuildingsState::instance.buildings[workplace].subAnimState2 == 3) {
                DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    unitID);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for the mill to be free
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId == 0
                && DAT_BuildingsState::instance.buildings[workplace].subAnimState2 == 0) {
                DAT_BuildingsState::instance.buildings[workplace].occupyingWorkerId = (short)unitID;
                DAT_BuildingsState::instance.buildings[workplace].typeSpecificTimer = 300;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    unitID);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // leaving the mill with flour
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber < 20) {
                if (DAT_UnitAnimationFinished::instance == 0) {
                    return;
                }
            } else {
                DAT_UnitAnimationFinished::instance = 1;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            int storage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_FLOUR, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (storage == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::PlayStockpileIsFullWarning)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(storage, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                       DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)
                    != FALSE) {
                int id = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[id].targetID_OR_targetBuildingID = (short)storage;
                DAT_UnitsState::instance.units[id].targetUID = DAT_BuildingsState::instance.buildings[storage].uid;
                DAT_UnitsState::instance.units[id].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                DAT_UnitsState::instance.units[id].resourceToDeposit
                    = (short)MACRO_CALL(OpenSHC::Map::Units_Func::ComputeGoodsProduced)(id, 0, TRUE);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // carrying flour to the stockpile
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::canBuildingStoreTheAmount,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_FLOUR, 32)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_FLOUR, 1, 32, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_HOPS);
            } else {
                int storage = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_FLOUR, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(storage, 1)
                    != 0) {
                    int id = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[id].targetID_OR_targetBuildingID = (short)storage;
                    DAT_UnitsState::instance.units[id].targetUID = DAT_BuildingsState::instance.buildings[storage].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                        DAT_UnitsState::ptr)(id, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0);
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                }
            }
            int id = DAT_CurrentUnitSlotID::instance;
            if (DAT_UnitsState::instance.units[id].resourceToDeposit > 0) {
                return;
            }
            int granary = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WHEAT, 1, DAT_UnitsState::instance.units[id].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(granary, 1)
                != 0) {
                id = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[id].targetID_OR_targetBuildingID = (short)granary;
                DAT_UnitsState::instance.units[id].targetUID = DAT_BuildingsState::instance.buildings[granary].uid;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    id, DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                return;
            }
            id = DAT_CurrentUnitSlotID::instance;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                    DAT_UnitsState::ptr)(id, DAT_UnitsState::instance.units[id].workerIndex + 1)
                != 0) {
                id = DAT_CurrentUnitSlotID::instance;
                MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(id, TRUE);
                DAT_UnitsState::instance.units[id].state.generic = (UnitState)2;
                DAT_UnitsState::instance.units[id].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == (UnitState)121) {
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(unitID) != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            }
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
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1a4;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x18c;
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                       DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1bc;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x1a4;
            }
        } else {
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
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            return;
        }
        if (DAT_UnitAnimationFinished::instance != 0) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
    }

}
}
