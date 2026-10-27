#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
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
#include "OpenSHC/Globals/lastAssassinWarningTime.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005744D0
    void Units::UpdateAssassin()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].countAssassins += 1;
        DAT_UnitsState::instance.units[unitID].secondaryGmID = 0xc6;
        DAT_UnitsState::instance.units[unitID].overlayImageID = 0;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(unitID);
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
            != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinLayerImageOrYOffset = 0;
        }
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel
                    >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0x69;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getKeepLocationForAIUnit,
                    DAT_BuildingsState::ptr)(owner, 13, DAT_CurrentUnitSlotID::instance)
                != 0) {
                DAT_PathFindingState::instance.pathForAssassins = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                    DAT_BuildingsState::instance.DAT_TempYOffset, 0);
            }
            DAT_GameState::instance.playerDataArray[owner].rallyWaitingCountPerClass[13] += 1;
            return;
        case (UnitState)0x69:
            // gathering at the keep
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks += 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                if ((DAT_GameCore::instance.mapTimeInTicks + DAT_CurrentUnitSlotID::instance) % 40 == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getKeepLocationForAIUnit,
                           DAT_BuildingsState::ptr)(owner, 13, DAT_CurrentUnitSlotID::instance)
                        != 0) {
                    DAT_PathFindingState::instance.pathForAssassins = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
            }
            DAT_GameState::instance.playerDataArray[owner].rallyWaitingCountPerClass[13] += 1;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .rallyMode
                != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance <= 192) {
                    // sneaking
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                <= 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .tribeBehaviorType
                == OpenSHC::Map::Units::STBT_0x400) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetBehaviorType
                != 1015) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
                return;
            }
            // arrived at a moat to fill
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget
                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
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
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    <= 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            // arrived at the map edge: jump to the actual appear tile
            int tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                           .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance,
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinMelee
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x101;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 6) {
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
            }
            if ((short)DAT_TileMapState::instance.BuildingLayer
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                    == 0
                && (DAT_TileMapState::instance.LogicLayer
                           [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                       & 0x100)
                    == 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle > 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].wallHitNoDamageToggle = 0;
            }
            int tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile;
            int isWall = DAT_TileMapState::instance.LogicLayer[tile] & 0x100;
            int building;
            int damage;
            if (isWall == 0) {
                building = (short)DAT_TileMapState::instance.BuildingLayer[tile];
                if (building <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                damage = DAT_BuildingDefinedData::instance
                             .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        != FALSE
                    ? 6
                    : 70;
            } else {
                damage = 10;
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
                int danger = *(
                    unsigned char*)(*(int*)((int)&DAT_TroopValueState::instance.attackInfo.record0ImageUnused_0x301c0
                                        + attacker * 0x177bc)
                        * 0x13a10
                    + 0x1ee2998 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                int tolerance = *(
                    int*)((int)&DAT_TroopValueState::instance.attackInfo.record0ImageUnused_0x34060 + attacker * 0x177bc);
                if (isWall == 0) {
                    if (DAT_BuildingDefinedData::instance
                                .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                            != FALSE
                        && danger > tolerance + 10
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                               DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                               DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .siegeTargetBehaviorType)
                            == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        return;
                    }
                } else if (danger > tolerance + 15) {
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
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        }
        case OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            // the higher the wall, the higher the throw
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinHookThrowLow
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinHookThrowMid
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinHookThrowHigh
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1c1;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1b9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_GH_SWING);
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_GH_CATCH);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend = 32;
            // warn the player whose wall is scaled
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_GameSynchronyState::instance.currentPlayerSlotID
                    == (char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].ownerOfAssassinScaledObject
                && timeGetTime() - lastAssassinWarningTime::instance > 30000) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                    || DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "General_Warning18.wav");
                }
                lastAssassinWarningTime::instance = timeGetTime();
            }
            return;
        case OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinClimbDownStart
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1c1;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1b9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend = 32;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_ROPE_SLIDE);
            return;
        case OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            if ((short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend > 0) { // signed: 0x574F15/0x5750C5 jle
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend -= 2;
            }
            // rope length
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 7;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 100) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 6;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 130) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 5;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 4;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 190) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 3;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 210
                    ? 2
                    : 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinClimbUp
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x271;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x269 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber < 10
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 16)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset += 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference - 35
                > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset) {
                return;
            }
            // reached the top
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitMimmicLocation, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 0;
            return;
        case OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitMimmicLocation, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            if ((short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend > 0) { // signed: 0x574F15/0x5750C5 jle
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend -= 2;
            }
            // rope length
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 7;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 100) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 6;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 130) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 5;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 4;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 190) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID = 3;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].overlayImageID
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 210
                    ? 2
                    : 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 0x291;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset -= 4;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset > 30) {
                return;
            }
            // landed
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbOverlayBlend = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isAssassinHookClimbing = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_ASS_LAND);
            return;
        case (UnitState)0x68:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x181;
            return;
        case (UnitState)0x6c:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            return;
        case OpenSHC::Map::Units::States::US_FADE_TRANSITION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel
                += DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                       .fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel
                >= 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 31;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .fadeAlphaStep
                < 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::prepareCampgroundCoords,
                        DAT_BuildingsState::ptr)(owner);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                return;
            }
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .fadeAlphaStep
                    > 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isFadeActive != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_TRANSITIONING;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 32;
            }
            return;
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK: {
            int previousGfx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                    && (DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_SPEAR
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_PIKE
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_LORD
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_MACE
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_SWORD
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_KNIGHT
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_A_ASSASSIN
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_A_SWORDSMAN)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_STEEL1);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 4) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ASS_SWISH);
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animAssassinMelee
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x101;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber != previousGfx) {
                // motion blur of the previous frames
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinLayerImageOrYOffset
                    = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = previousGfx;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            return;
        }
        case OpenSHC::Map::Units::States::US_IDLEUnk: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].busyThisTick = 10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks += 1;
            int variant = DAT_CurrentUnitSlotID::instance & 3;
            if (variant == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .DAT_AssassinAnimationFrames0[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else if (variant == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .DAT_AssassinAnimationFrames1[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else if (variant == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .DAT_AssassinAnimationFrames2[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .DAT_AssassinAnimationFrames4[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x311;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x310;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                    == OpenSHC::Map::Units::UIT_DIG_MOAT
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType_OR_performanceStep
                    == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                DAT_UnitAnimationFinished::instance = 1;
            } else if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        }
        case OpenSHC::Map::Units::States::US_DEATH_01:
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset < 8) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset -= 8;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animDeathAssassin
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x33c;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x324;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animDeathAssassin
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x36a;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x352;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animStoneDeathAssassin
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x352;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x33c;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].climbHeightOffset = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinIdleTicks = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel
                <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisbanded != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, DAT_CurrentUnitSlotID::instance);
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
