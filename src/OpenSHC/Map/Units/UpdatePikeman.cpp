#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0055F110
    void Units::UpdatePikeman()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int attacked = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentPikemen += 1;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(unitID);
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].ownerColorIndex = owner;
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel
                    >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0x69;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                        DAT_BuildingsState::ptr)(owner, 4, DAT_CurrentUnitSlotID::instance)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                DAT_GameState::instance.playerDataArray[owner].rallyWaitingCountPerClass[4] += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                == OpenSHC::Map::Units::UIT_DIG_MOAT) {
                int moat = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findBestMoatTileForWork,
                    DAT_TileMapState::ptr)(owner, DAT_CurrentUnitSlotID::instance, 1);
                if (moat > -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeMoatDigTarget, DAT_TileMapState::ptr)(moat,
                        1, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                    DAT_PathFindingState::instance.climbIsIllegal = 1;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_TileMapState::instance.ALG_MoatXResult, DAT_TileMapState::instance.ALG_MoatYResult, 0)
                        != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1);
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            = (short)DAT_TileMapState::instance.ALG_MoatXResult;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .digTileY__OR__crewScatterSlotIndex
                            = (short)DAT_TileMapState::instance.ALG_MoatYResult;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = moat;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)124;
                        return;
                    }
                    DAT_TileMapState::instance.moats[moat].workerReservation -= 20;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVE;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                int moat = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findBestMoatTileForWork,
                    DAT_TileMapState::ptr)(owner, DAT_CurrentUnitSlotID::instance, 2);
                if (moat > -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeMoatDigTarget, DAT_TileMapState::ptr)(moat,
                        1, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        = (short)DAT_TileMapState::instance.ALG_MoatXResult;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__crewScatterSlotIndex
                        = (short)DAT_TileMapState::instance.ALG_MoatYResult;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = moat;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeMoatDigTarget, DAT_TileMapState::ptr)(
                            moat, 2, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)
                        == 0) {
                        DAT_TileMapState::instance.moats[moat].workerReservation -= 20;
                    } else {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_TileMapState::instance.ALG_MoatXResult, DAT_TileMapState::instance.ALG_MoatYResult,
                                0)
                            != FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_FILL_MOAT;
                            return;
                        }
                        DAT_TileMapState::instance.moats[moat].workerReservation -= 20;
                    }
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVE;
            }
            if (DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated > 0
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 400
                    || DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated == 100000)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                return;
            }
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance < 401
                    ? (UnitState)2
                    : OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        case (UnitState)0x69:
            // gathering at the rally point
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].SA = 1;
            DAT_UnitsState::instance.units[unitID].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[unitID].movementSpeed;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                if ((int)(DAT_GameCore::instance.mapTimeInTicks + DAT_CurrentUnitSlotID::instance) % 40 == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                           DAT_BuildingsState::ptr)(owner, 4, unitID)
                        != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
            }
            DAT_GameState::instance.playerDataArray[owner].rallyWaitingCountPerClass[4] += 1;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .rallyMode
                != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementRunUpTime != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
                if (DAT_TribesState::instance
                        .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                        .tribeBehaviorType
                    == OpenSHC::Map::Units::STBT_0x400) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetBehaviorType
                == 0x3f7) {
                // arrived at a moat to fill
                int moat
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = moat;
                if (moat != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_FILL_MOAT;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__crewScatterSlotIndex
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile];
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                        - (short)DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .digTileY__OR__crewScatterSlotIndex]
                              .addXgetTile;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
            return;
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            // arrived at the map edge: jump to the actual appear tile
            int tile = DAT_UnitsState::instance.units[unitID]
                           .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, DAT_UnitsState::ptr)(unitID,
                tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile],
                DAT_TileMapState::instance.HeightLayer[tile]);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].plannedDestinationX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].plannedDestinationY, 0);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeType = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeCounter = 0;
            return;
        }
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL: {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[unitID].attackAtTileX,
                DAT_UnitsState::instance.units[unitID].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanMeleeA
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x15b + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            int hurtSFX
                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingHurtSFXID, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
            if (hurtSFX == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_ATTACK_WOOD);
            } else if (hurtSFX == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_ATTACK_STONE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle > 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle = 0;
            }
            int tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile;
            int isWall = DAT_TileMapState::instance.LogicLayer[tile] & 0x100;
            int building;
            int damage;
            if (isWall != 0) {
                damage = 6;
                building = 0;
            } else {
                building = (short)DAT_TileMapState::instance.BuildingLayer[tile];
                if (building <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                damage = DAT_BuildingDefinedData::instance
                             .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        != FALSE
                    ? 4
                    : 20;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuildingThunk, DAT_TileMapState::ptr)(
                    tile, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY, damage,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, TRUE)
                != FALSE) {
                // the building has been destroyed
                if (isWall != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                           DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                        != 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .siegeTargetBehaviorType)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            int attacker = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[attacker] == -1) {
                // AI players give up on walls that are too dangerous
                // TODO: the per player AttackInfo blocks (stride 0x177bc) and the byte tile layers at 0x01EE2998 are
                // not modelled yet
                if (isWall != 0) {
                    if (*(unsigned char*)(*(int*)((int)&DAT_TroopValueState::instance.attackInfo
                                                      .record0ImageUnused_0x301c0
                                              + attacker * 0x177bc)
                                * 0x13a10
                            + 0x1ee2998
                            + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile)
                        > *(int*)((int)&DAT_TroopValueState::instance.attackInfo.record0ImageUnused_0x34060
                              + attacker * 0x177bc)
                            + 15) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                                DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .siegeTargetBehaviorType)
                            != 0) {
                            return;
                        }
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                            != 0) {
                            return;
                        }
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        return;
                    }
                } else if (DAT_BuildingDefinedData::instance
                               .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        != FALSE
                    && *(unsigned char*)(*(int*)((int)&DAT_TroopValueState::instance.attackInfo
                                                     .record0ImageUnused_0x301c0
                                             + attacker * 0x177bc)
                               * 0x13a10
                           + 0x1ee2998
                           + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile)
                        > *(int*)((int)&DAT_TroopValueState::instance.attackInfo.record0ImageUnused_0x34060
                              + attacker * 0x177bc)
                            + 10
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                           DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                           DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetBehaviorType)
                        == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        }
        case OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk:
        case (UnitState)124: {
            // digging a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)124;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__crewScatterSlotIndex)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__crewScatterSlotIndex]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileY__OR__crewScatterSlotIndex);
            if (DAT_DirectionAlgorithmState::instance.orientation != 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_MOAT_DIG);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanDigMoat
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1e3;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1db + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) != 0
                || ((short)DAT_TileMapState::instance.UnitLayer[tile] != 0
                    && DAT_UnitsState::instance.units[(short)DAT_TileMapState::instance.UnitLayer[tile]].someUnitStat4
                        == 0)) {
                // the tile is already dug or occupied
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::advanceMoatDigProgress, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget)
                == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        case OpenSHC::Map::Units::States::US_AIM_WEAPONUnk:
        case OpenSHC::Map::Units::States::US_FILL_MOAT: {
            // filling a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_FILL_MOAT;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__crewScatterSlotIndex)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__crewScatterSlotIndex]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileY__OR__crewScatterSlotIndex);
            if (DAT_DirectionAlgorithmState::instance.orientation != 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_MOAT_DIG);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanFillMoat
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1e3;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1db + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) == 0) {
                // the moat is already filled
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .siegeTargetBehaviorType)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::removeMoat, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile)
                != 1) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                    DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetBehaviorType)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        case OpenSHC::Map::Units::States::US_IDLEUnk: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].busyThisTick = 10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance < 400
                && DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount != 0) {
                DAT_UnitAnimationFinished::instance = 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber
                    = DAT_CurrentUnitSlotID::instance & 7;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
            }
            OpenSHC::Game::GameModeInt gameMode = DAT_GameSynchronyState::instance.currentGameMode;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6b) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                    // sitting down
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanSitDown
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                        DAT_UnitAnimationFinished::instance = 1;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 200;
                    }
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanSeatedIdleA
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 200;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6b;
                        DAT_UnitAnimationFinished::instance = 1;
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanSeatedIdleB
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 200;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                        DAT_UnitAnimationFinished::instance = 1;
                    }
                }
                // a selected pikeman in a single player game stops idling
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelected != 0
                    && gameMode == OpenSHC::Game::GM_SOLITARY) {
                    DAT_UnitAnimationFinished::instance = 1;
                } else if (DAT_UnitAnimationFinished::instance == 0) {
                    return;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate != 100) {
                // standing
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
                if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1) == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanStandIdleEven
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanStandIdleOdd
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitAnimationFinished::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0xc0;
                    if (DAT_UnitAnimationFinished::instance == 0) {
                        return;
                    }
                }
            } else {
                // standing up
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].faceViewer = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanStandUp
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitAnimationFinished::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 200;
                    if (DAT_UnitAnimationFinished::instance == 0) {
                        return;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelected == 0
                || gameMode != OpenSHC::Game::GM_SOLITARY) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0
                    && (DAT_TileMapState::instance
                               .LogicLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                           & 0x10000100)
                        == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x65;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 100;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        }
        case (UnitState)3:
            // cheering
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 4;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].busyThisTick = 10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionBasedOnBuilding, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_GameState::instance.mapAndTime.signpostIDs[0]);
            }
            if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanGuardIdleEven
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanGuardIdleOdd
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x79 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        case (UnitState)2:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].busyThisTick = 10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanStandIdleEven
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanStandIdleOdd
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0xc0;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        case (UnitState)0x6c:
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        case OpenSHC::Map::Units::States::US_FADE_TRANSITION:
            DAT_UnitsState::instance.units[unitID].fadeLevel
                += DAT_UnitsState::instance.units[unitID].fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 31) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].stateAfterFade;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep < 0) {
                if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::prepareCampgroundCoords,
                        DAT_BuildingsState::ptr)(owner);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                return;
            }
            if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep > 0
                && DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_TRANSITIONING;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x10a;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0xf2;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_03:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x122;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x10a;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0xf2;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0xda;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            int heightDifference
                = DAT_TileMapState::instance
                      .HeightLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                - DAT_TileMapState::instance.HeightLayer[DAT_UnitsState::instance.units[attacked].tile];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID);
            }
            // thrust down, level or up
            int thrustGfx;
            if (heightDifference < -15) {
                thrustGfx = 0x123;
            } else {
                thrustGfx = heightDifference < 16 ? 0x163 : 0x1a3;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanMeleeA
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanMeleeB
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanMeleeA
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animPikemanMeleeC
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + thrustGfx - 8
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            return;
        }
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[unitID].isDisbanded != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, unitID);
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.unitsLostToPlayer
                    [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID] += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.enemyHitCountByPlayer[owner] += 1;
            }
            return;
        }
    }

}
}
