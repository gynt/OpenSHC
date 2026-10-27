#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitState_WheatFarmer.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitState_WheatFarmer;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005521D0
    void Units::UpdateWheatFarmer()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int farm = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeSpecificRestingState = 1;
        OpenSHC::Map::Units::States::UnitState_WheatFarmerShort state
            = DAT_UnitsState::instance.units[unitID].state.wheatFarmer;
        if (state == OpenSHC::Map::Units::States::USWF_WAITING_0) {
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].isFadeActive = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = (OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum)2;
            return;
        }
        if (state == OpenSHC::Map::Units::States::USWF_WAITING_1) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 1;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWheatFarmerIdleA[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWheatFarmerIdleB[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            int idle;
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x300;
                DAT_UnitAnimationFinished::instance = 1;
                idle = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x300;
                idle = DAT_UnitAnimationFinished::instance;
            }
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 0) != 0) {
                return;
            }
            if (idle == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextWheatFarmWorkTile,
                    DAT_BuildingsState::ptr)(farm)
                == 0) {
                return;
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                = (OpenSHC::Map::Units::States::UnitState_WheatFarmer)DAT_BuildingsState::instance.buildings[farm]
                      .farmerNextWorkState;
            DAT_UnitsState::instance.units[unitID].destinationYPosition
                = DAT_ViewportRenderState::instance
                      .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
            DAT_UnitsState::instance.units[unitID].destinationXPosition
                = (short)DAT_BuildingsState::instance.farmerDestinationTile
                - (short)DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_UnitsState::instance.units[unitID].destinationYPosition]
                      .addXgetTile;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].destinationXPosition,
                    DAT_UnitsState::instance.units[unitID].destinationYPosition, 0)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.wheatFarmer
                    = OpenSHC::Map::Units::States::USWF_WAITING_1;
                return;
            }
        } else if (state == OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE) {
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
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.wheatFarmer
                        = (OpenSHC::Map::Units::States::UnitState_WheatFarmer)0x6e;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer = OpenSHC::Map::Units::States::USWF_WAITING_1;
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_3) {
            // walking to the field to plough
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset
                = DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan
                    >= DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan
                ? 0x81
                : 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer = OpenSHC::Map::Units::States::USWF_WORKING_4;
            int tile = DAT_UnitsState::instance.units[unitID].destinationTilePosition;
            DAT_UnitAnimationFinished::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y,
                tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_4) {
            // ploughing
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 0;
            DAT_UnitsState::instance.units[unitID].animCycle16 = 0;
            DAT_UnitsState::instance.units[unitID].substate = 1;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animWheatFarmerHoe[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x81;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x81
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 8) {
                DAT_TileMapState::instance.DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition]
                    = 1;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 4
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_HOE);
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextWheatFarmWorkTile,
                    DAT_BuildingsState::ptr)(farm)
                    != 0
                && DAT_BuildingsState::instance.buildings[farm].farmerNextWorkState == 3) {
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].state.wheatFarmer = OpenSHC::Map::Units::States::USWF_WORKING_3;
                DAT_UnitsState::instance.units[unitID].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[unitID].destinationXPosition
                    = (short)DAT_BuildingsState::instance.farmerDestinationTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[unitID].destinationYPosition]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].destinationXPosition,
                    DAT_UnitsState::instance.units[unitID].destinationYPosition, 0);
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.wheatFarmer
                    = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = (OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum)2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_5) {
            // walking to the next tile to sow
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].faceViewer = 0;
            DAT_UnitsState::instance.units[unitID].substate = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_TileMapState::instance.DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition] = 2;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextWheatFarmWorkTile,
                    DAT_BuildingsState::ptr)(farm)
                    != 0
                && DAT_BuildingsState::instance.buildings[farm].farmerNextWorkState == 5) {
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[unitID].destinationXPosition
                    = (short)DAT_BuildingsState::instance.farmerDestinationTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[unitID].destinationYPosition]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].destinationXPosition,
                    DAT_UnitsState::instance.units[unitID].destinationYPosition, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition
                    = DAT_BuildingsState::instance.farmerDestinationTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                    = DAT_BuildingsState::instance.farmerDestinationTile;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.wheatFarmer
                = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = (OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum)2;
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_6) {
            // walking to the wheat to harvest
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].faceViewer = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset
                = DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan
                    >= DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan
                ? 0x201
                : 0x181;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer = OpenSHC::Map::Units::States::USWF_WORKING_7;
            int tile = DAT_UnitsState::instance.units[unitID].destinationTilePosition;
            DAT_UnitAnimationFinished::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y,
                tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_HARVEST);
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_7) {
            // harvesting
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 0;
            DAT_UnitsState::instance.units[unitID].animCycle16 = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animWheatFarmerHarvest[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x201;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x201
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && (char)DAT_TileMapState::instance
                        .DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition]
                    < 120) {
                DAT_UnitsState::instance.units[unitID].resourcesGatheredCount += 1;
                if (DAT_UnitsState::instance.units[unitID].resourcesGatheredCount >= 3) {
                    DAT_UnitsState::instance.units[unitID].resourcesGatheredCount = 0;
                    DAT_TileMapState::instance
                        .DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition] = 121;
                } else {
                    DAT_TileMapState::instance
                        .DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition] = 120;
                }
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextWheatFarmWorkTile,
                    DAT_BuildingsState::ptr)(farm)
                    != 0
                && (DAT_BuildingsState::instance.buildings[farm].farmerNextWorkState
                        == OpenSHC::Map::Units::States::USWF_WORKING_6
                    || DAT_BuildingsState::instance.buildings[farm].farmerNextWorkState
                        == OpenSHC::Map::Units::States::USWF_WORKING_8)) {
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                    = (OpenSHC::Map::Units::States::UnitState_WheatFarmer)DAT_BuildingsState::instance.buildings[farm]
                          .farmerNextWorkState;
                DAT_UnitsState::instance.units[unitID].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[unitID].destinationXPosition
                    = (short)DAT_BuildingsState::instance.farmerDestinationTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[unitID].destinationYPosition]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].destinationXPosition,
                    DAT_UnitsState::instance.units[unitID].destinationYPosition, 0);
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.wheatFarmer
                    = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
        } else if (state == OpenSHC::Map::Units::States::USWF_WORKING_8) {
            // walking to the next tile to harvest
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                = OpenSHC::Map::Units::States::USWF_AWAITING_STORE_SPACE;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_TileMapState::instance.DamageOrCropStageLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition]
                = 120;
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_AWAITING_STORE_SPACE) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x281;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 10) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            int granary
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_WHEAT, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (granary == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::PlayStockpileIsFullWarning)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(granary, 1)
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0)
                == FALSE) {
                return;
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)granary;
            DAT_UnitsState::instance.units[unitID].targetUID = DAT_BuildingsState::instance.buildings[granary].uid;
            DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                = OpenSHC::Map::Units::States::USWF_TAKING_GOODS_TO_STORE;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit
                = (short)MACRO_CALL(OpenSHC::Map::Units_Func::ComputeGoodsProduced)(unitID, 2, FALSE);
            return;
        } else if (state == OpenSHC::Map::Units::States::USWF_TAKING_GOODS_TO_STORE) {
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x281;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
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
                    OpenSHC::Game::Resources::RT_WHEAT, 32)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_WHEAT, 1, 32, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_WHEAT);
            } else {
                // the stockpile is full: look for another one
                int stockpile = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WHEAT, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(stockpile, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)stockpile;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[stockpile].uid;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                            DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                        == FALSE) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit > 0) {
                return;
            }
            int workplace = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextWheatFarmWorkTile,
                    DAT_BuildingsState::ptr)(workplace)
                    != 0
                && (DAT_BuildingsState::instance.buildings[workplace].farmerNextWorkState
                        == OpenSHC::Map::Units::States::USWF_WORKING_6
                    || DAT_BuildingsState::instance.buildings[workplace].farmerNextWorkState
                        == OpenSHC::Map::Units::States::USWF_WORKING_8)) {
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                    = (OpenSHC::Map::Units::States::UnitState_WheatFarmer)DAT_BuildingsState::instance
                          .buildings[workplace]
                          .farmerNextWorkState;
                DAT_UnitsState::instance.units[unitID].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[unitID].destinationXPosition
                    = (short)DAT_BuildingsState::instance.farmerDestinationTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[unitID].destinationYPosition]
                          .addXgetTile;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                        DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[unitID].destinationXPosition,
                        DAT_UnitsState::instance.units[unitID].destinationYPosition, 0)
                    == FALSE) {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, TRUE);
                    DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                        = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    return;
                }
            } else {
                unitID = DAT_CurrentUnitSlotID::instance;
                MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, TRUE);
                DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                    = OpenSHC::Map::Units::States::USWF_GOING_TO_WORKPLACE;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
        } else if (state == (OpenSHC::Map::Units::States::UnitState_WheatFarmer)121) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(unitID);
            return;
        } else if (state == (OpenSHC::Map::Units::States::UnitState_WheatFarmer)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        } else if (state == (OpenSHC::Map::Units::States::UnitState_WheatFarmer)0x6f) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x5a0;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x588;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                    = (OpenSHC::Map::Units::States::UnitState_WheatFarmer)0x6e;
            }
            return;
        } else {
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                    DAT_UnitsState::ptr)(unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].facingDirection = 0;
                DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].gfxNumber = 0x588;
                    DAT_UnitAnimationFinished::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].animationFrame + 0x570;
                }
                if (DAT_UnitAnimationFinished::instance != 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].state.wheatFarmer
                == (OpenSHC::Map::Units::States::UnitState_WheatFarmer)0x6e) {
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
        // walk to the next tile of the field
        unitID = DAT_CurrentUnitSlotID::instance;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
            unitID, 1);
        DAT_UnitsState::instance.units[unitID].destinationTilePosition
            = DAT_BuildingsState::instance.farmerDestinationTile;
        DAT_UnitsState::instance.units[unitID].targetedBuildingTile = DAT_BuildingsState::instance.farmerDestinationTile;
    }

}
}
