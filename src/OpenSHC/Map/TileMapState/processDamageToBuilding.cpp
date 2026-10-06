#include "../../Map.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingLogicalStateShort;
    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeInt;
    using Map::Buildings::BuildingTypeShort;
    using Map::Entities::EntityType;
    using Map::Units::States::UnitState;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      beware the renames! this is for both stones as well as units hitting walls   decompilerscript: committed:
      2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00516B80
    BOOLEnum TileMapState::processDamageToBuilding(int tile, uint xPosition, uint yPosition, int damageUnk, int param_5,
        int playerID, BOOLEnum aiBuildDelayRelated, int unitID)
    {
        short* psVar1;
        int* piVar2;
        BuildingTypeShort BVar3;
        ushort uVar4;
        ushort uVar5;
        short sVar6;
        bool bVar7;
        bool bVar8;
        byte bVar9;
        int _drawbridgeBuildingID;
        int _drawbridgeBuildingID_2;
        int _owner;
        BOOLEnum BVar10;
        int _drawbridgeID;
        uint _buildingOwnerZeroBased;
        BuildingTypeInt _buildingType3;
        int _x;
        int _buildingIDAtTile;
        int iVar11;
        int iVar12;
        int _y;
        int _owner2;
        MappersEnum cbt;
        BOOLEnum local_8;
        int _pitch;
        int _microY;
        int _microX;
        ushort _gatehouseX;
        ushort _gatehouseY;
        short _health;
        short _health2;
        BuildingTypeShort _buildingType;
        BuildingTypeShort _buildingType2;
        BuildingLogicalStateShort _logicalState;
        _owner = 0;
        bVar7 = false;
        local_8 = FALSE;
        bVar9 = 0;
        bVar8 = false;
        if ((playerID < 0)
            && (iVar11 = -playerID, iVar12 = playerID * -4, playerID = iVar11,
                *(int*)((int)DAT_GameSynchronyState::ptr + iVar12 + 0x6a8) == -1)) {
            bVar7 = true;
            bVar8 = true;
        }
        _buildingOwnerZeroBased = DAT_TileMapState::instance.LogicLayer[tile];
        if ((!(_buildingOwnerZeroBased & 0x10000400)) && (DAT_TileMapState::instance.BuildingLayer[tile] == 0)) {
            if ((_buildingOwnerZeroBased & 0x100)) {
                if (((_buildingOwnerZeroBased & 2))
                    || ((_buildingOwnerZeroBased = DAT_TileMapState::instance.WallOwnerLayer[tile] & 7,
                        bVar7
                            && (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                == DAT_GameState::instance.mapAndTime.playerTeams[_buildingOwnerZeroBased + 1])))) {
                    return FALSE;
                }
                DAT_GameState::instance.playerDataArray[_buildingOwnerZeroBased + 1].defensesDamagedByPlayer
                    = (short)playerID;
                if (unitID) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[_buildingOwnerZeroBased + 1]
                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                        DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk
                            = DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk + 1;
                    } else {
                        DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
                    }
                }
                /*
                  checks if there are other wall tiles around this wall in a plus (cardinal   directions)
                 */
                MACRO_CALL_MEMBER(Map::TileMapState_Func::countLogicPropertyInSurroundingTiles, this)(
                    tile, (int)((int)(yPosition)), (uint)((int)(268435712)));
                if (DAT_TileMapState::instance.DAT_CardinalTilesAroundTile < 2) {
                    damageUnk = damageUnk + damageUnk / 2;
                } else if (2 < DAT_TileMapState::instance.DAT_CardinalTilesAroundTile) {
                    damageUnk = damageUnk / 2;
                }
                if (param_5) {
                    damageUnk = 0;
                }
                DAT_TroopValueState::instance.attackInfo.field128059_0x469e0
                    = DAT_TroopValueState::instance.attackInfo.field128059_0x469e0 + 1;
                DAT_GameCore::instance.cowPoisonTrackerUnk
                    = DAT_GameCore::instance.cowPoisonTrackerUnk + damageUnk * 10;
                if ((((!param_5)
                         && (!(
                             DAT_TileMapState::instance.LogicLayer[tile] & Map::LogicHelpers::L_UNKNOWN_WALL_RELATED)))
                        && (DAT_TileMapState::instance.DamageLayer[tile] == 0))
                    && (DAT_TileMapState::instance.DefaultHeightLayer[tile] + 60
                        < (uint)DAT_TileMapState::instance.HeightLayer[tile])) {
                    DAT_TileMapState::instance.HeightLayer[tile] = DAT_TileMapState::instance.HeightLayer[tile] - 20;
                }
                if (damageUnk < 1) {
                LAB_00516d9a:
                    MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(yPosition, tile);
                } else {
                    do {
                        if (DAT_TileMapState::instance.HeightLayer[tile]
                            <= DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                                DAT_EntityState::ptr)(tile);
                            DAT_TileMapState::instance.LogicLayer[tile] = DAT_TileMapState::instance.LogicLayer[tile]
                                & ~(Map::LogicHelpers::L_WALL_OR_GATEHOUSE
                                    | Map::LogicHelpers::L_CRENEL | Map::LogicHelpers::L_STAIRS
                                    | Map::LogicHelpers::L_UNKNOWN_WALL_RELATED
                                    | Map::LogicHelpers::L_CRENEL_VARIATIONUnk);
                            DAT_TileMapState::instance.HeightLayer[tile]
                                = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                            DAT_TileMapState::instance.DamageLayer[tile] = 0;
                            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                            DAT_TileMapState::instance.field204_0x554a30 = 1;
                            local_8 = TRUE;
                            goto LAB_00516d9a;
                        }
                        DAT_TileMapState::instance.HeightLayer[tile] = DAT_TileMapState::instance.HeightLayer[tile] - 1;
                        if ((char)DAT_TileMapState::instance.DamageLayer[tile] < 200) {
                            DAT_TileMapState::instance.DamageLayer[tile]
                                = DAT_TileMapState::instance.DamageLayer[tile] + 1;
                        }
                        _owner = _owner + 1;
                    } while (_owner < damageUnk);
                    MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(yPosition, tile);
                }
                goto LAB_0051769a;
            }
            goto LAB_005175ec;
        }
        _buildingIDAtTile = (int)DAT_TileMapState::instance.BuildingLayer[tile];
        _logicalState = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].logicalState;
        if (((_logicalState == ((BuildingLogicalState)0)) || (_logicalState == Map::Buildings::BLS_REMOVE))
            || (_health = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].currentHealth, !_health)) {
            return TRUE;
        }
        DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + damageUnk * 10;
        _buildingType = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType;
        if (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[(short)_buildingType] == 0) {
            return TRUE;
        }
        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0xf000000U)) {
            return TRUE;
        }
        if ((bVar8)
            && (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                == DAT_GameState::instance.mapAndTime
                    .playerTeams[DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner])) {
            return FALSE;
        }
        DAT_BuildingsState::instance.buildings[_buildingIDAtTile].currentHealth = _health - (short)damageUnk;
        if ((aiBuildDelayRelated == TRUE)
            && (((_buildingType == Map::Buildings::BT_GATEHOUSELARGE
                     || (_buildingType == Map::Buildings::BT_GATEHOUSESMALL))
                && (_drawbridgeBuildingID
                    = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner,
                        ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x)),
                        ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y)),
                        ((int)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].widthOrHeight)),
                        Map::Buildings::BT_DRAWBRIDGE, 0),
                    _drawbridgeBuildingID != 0)))) {
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                            [(short)DAT_BuildingsState::instance.buildings[_drawbridgeBuildingID].buildingType]
                    == 0);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                _drawbridgeBuildingID);
            _drawbridgeBuildingID_2 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findParticularBuilding,
                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner,
                ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x)),
                ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y)),
                ((int)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].widthOrHeight)),
                Map::Buildings::BT_DRAWBRIDGE, _drawbridgeBuildingID);
            if (_drawbridgeBuildingID_2) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                    = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                [(short)DAT_BuildingsState::instance.buildings[_drawbridgeBuildingID_2].buildingType]
                        == 0);
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(_drawbridgeBuildingID_2);
            }
        }
        _buildingType2 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType;
        switch (_buildingType2) {
        case Map::Buildings::BT_GATEHOUSELARGE:
        case Map::Buildings::BT_GATEHOUSESMALL:
        case Map::Buildings::BT_TOWER1:
        case Map::Buildings::BT_TOWER2:
        case Map::Buildings::BT_TOWER3:
        case Map::Buildings::BT_TOWER4:
        case Map::Buildings::BT_TOWER5:
            DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner]
                .defensesDamagedByPlayer = (short)playerID;
            break;
        default:
            break;
        }
        if (unitID) {
            if (DAT_GameState::instance.mapAndTime
                    .playerTeams[DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner]
                == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk
                    = DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk + 1;
            } else {
                DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
            }
        }
        _health2 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].currentHealth;
        if (0 < _health2) {
            if (((_buildingType2 == Map::Buildings::BT_SIEGETOWER_PLACED)
                    && (_owner = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].unitRefID, _owner))
                && ((DAT_BuildingsState::instance.buildings[_buildingIDAtTile].unitRefUID
                        == DAT_UnitsState::instance.units[_owner].uid
                    && (sVar6 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].maxHealth, sVar6)))) {
                DAT_UnitsState::instance.units[_owner].health
                    = ((int)_health2 * DAT_UnitsState::instance.units[_owner].maxHealth) / (int)sVar6;
            }
            goto LAB_0051769a;
        }
        if (DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner
            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL(Map::Version_Func::UpdateDestroyedBuildingCountData)(1);
        }
        _owner = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
        if ((aiBuildDelayRelated == TRUE)
            && (DAT_GameState::instance.playerDataArray[_owner].resourceRebuildDelay == 0)) {
            DAT_GameState::instance.playerDataArray[_owner].resourceRebuildDelay = 1;
        }
        _buildingType3 = (BuildingTypeInt)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType;
        if ((_buildingType3 != Map::Buildings::BT_UNKNOWN3)
            && (((int)_buildingType3 < 0x56 || (0x59 < (int)_buildingType3)))) {
            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned + playerID;
            *piVar2 = *piVar2 + 1;
            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted + playerID;
            *piVar2 = *piVar2 + DAT_BuildingDefinedData::instance.BuildingDestroyedScoreWeight[_buildingType3];
            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed + _owner;
            *piVar2 = *piVar2 + 1;
            piVar2 = (int*)(_owner * 0x39f4 + 0x115e9d8 + playerID * 0x20);
            *piVar2 = *piVar2 + 1;
        }
        switch (DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType) {
        case Map::Buildings::BT_OILSMELTER:
        case Map::Buildings::BT_GATEHOUSELARGE:
        case Map::Buildings::BT_GATEHOUSESMALL:
        case Map::Buildings::BT_TOWER1:
        case Map::Buildings::BT_TOWER2:
        case Map::Buildings::BT_TOWER3:
        case Map::Buildings::BT_TOWER4:
        case Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(AI::AICState_Func::playAnger2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                _owner, playerID);
            break;
        default:
            MACRO_CALL_MEMBER(AI::AICState_Func::playVictory2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                _owner, playerID);
        }
        if ((((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                   && (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                  && (DAT_GameState::instance.mapAndTime.playerTeams[_owner]
                      != DAT_GameState::instance.mapAndTime
                          .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]))
                 && (((BVar3 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType,
                          BVar3 == Map::Buildings::BT_TOWER4 || (BVar3 == Map::Buildings::BT_TOWER5))
                     || ((BVar3 == Map::Buildings::BT_GATEHOUSELARGE
                         || ((BVar3 == Map::Buildings::BT_CHURCH || (BVar3 == Map::Buildings::BT_CATHEDRAL))))))))
                && (BVar10 = MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)(),
                    !BVar10))
            && (MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)(),
                DAT_GameCore::instance.genieVoiceActive)) {
            /*
              "Watch it crumble"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_36.wav");
        }
        switch (DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType) {
        case Map::Buildings::BT_OILSMELTER:
            _pitch = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].resources[7];
            if (_pitch) {
                _x = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
                _owner2 = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
                _buildingOwnerZeroBased
                    = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].currentTilePositionAdjusted;
                DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
                _y = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                    DAT_BuildingsState::ptr)(_buildingIDAtTile);
                if (_pitch < 5) {
                    MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(_owner2, _x * 8 + 0x10, _y * 8 + 0x10,
                        (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[_buildingOwnerZeroBased])), 3);
                } else {
                    _microY = _y * 8 + 0x10;
                    _microX = _x * 8 + 0x10;
                    MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(_owner2, _microX, _microY,
                        (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[_buildingOwnerZeroBased])), 5);
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                        DAT_EntityState::ptr)(0, (undefined4)((int)(_owner2)), 0, _microX, _microY,
                        (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[_buildingOwnerZeroBased])), 0, 0, 0,
                        Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    _x, _y, DE::SHCDE::FX_IGNITE_PITCH);
                local_8 = TRUE;
                goto LAB_0051769a;
            }
        default:
            goto switchD_00517137_caseD_1d;
        case Map::Buildings::BT_GATEHOUSELARGE:
        case Map::Buildings::BT_GATEHOUSESMALL:
            _drawbridgeID = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findParticularBuilding,
                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner,
                ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x)),
                ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y)),
                ((int)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].widthOrHeight)),
                Map::Buildings::BT_DRAWBRIDGE, 0);
            if (_drawbridgeID) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                    = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                [(short)DAT_BuildingsState::instance.buildings[_drawbridgeID].buildingType]
                        == 0);
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(_drawbridgeID);
                _owner = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findParticularBuilding,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner,
                    ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x)),
                    ((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y)),
                    ((int)(DAT_BuildingsState::instance.buildings[_buildingIDAtTile].widthOrHeight)),
                    Map::Buildings::BT_DRAWBRIDGE, _drawbridgeID);
                if (_owner) {
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                        = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                    [(short)DAT_BuildingsState::instance.buildings[_owner].buildingType]
                            == 0);
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(_owner);
                }
            }
            _gatehouseY = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            _gatehouseX = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, (int)((int)(50)));
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                            [(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType]
                    == 0);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)(short)_gatehouseX, (int)((int)((short)_gatehouseY)), DE::SHCDE::FX_TOWER_SMASH);
            local_8 = TRUE;
            goto LAB_0051769a;
        case Map::Buildings::BT_TUNNEL:
            _buildingOwnerZeroBased = (uint)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].unitRefID;
            if (DAT_UnitsState::instance.units[_buildingOwnerZeroBased].state.generic
                != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_IDLEUnk)) {
                DAT_UnitsState::instance.units[_buildingOwnerZeroBased].totalSizeOfPathPlan
                    = DAT_UnitsState::instance.units[_buildingOwnerZeroBased].currentIndexInPathPlan;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::applyTunnelDamageAlongPathPlan,
                    DAT_UnitsState::ptr)(_buildingOwnerZeroBased);
            }
            DAT_UnitsState::instance.units[_buildingOwnerZeroBased].state.generic
                = Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[_buildingOwnerZeroBased].disappearFadeAlphaCountdown = 0x20;
            DAT_UnitsState::instance.units[_buildingOwnerZeroBased].updateTickTracker = 0x20;
            goto switchD_00517137_caseD_1d;
        case Map::Buildings::BT_SIEGETOWER_PLACED:
            _owner = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].unitRefID;
            if ((_owner)
                && (DAT_BuildingsState::instance.buildings[_buildingIDAtTile].unitRefUID
                    == DAT_UnitsState::instance.units[_owner].uid)) {
                DAT_UnitsState::instance.units[_owner].state.generic = Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[_owner].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[_owner].updateTickTracker = 0;
                DAT_UnitsState::instance.units[_owner].workplaceBuildingID_1 = 0;
            }
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            local_8 = TRUE;
            goto LAB_0051769a;
        case Map::Buildings::BT_TOWER1:
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, 0x19);
            sVar6 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
            uVar4 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            uVar5 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            iVar11 = 3;
            cbt = Commands::M_MAPPER_TOWER1_DESTROYED;
            goto LAB_0051717e;
        case Map::Buildings::BT_TOWER2:
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, 0x32);
            damageUnk = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
            _owner = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            iVar12 = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            iVar11 = 4;
            cbt = Commands::M_MAPPER_TOWER2_DESTROYED;
            break;
        case Map::Buildings::BT_TOWER3:
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, 0x32);
            damageUnk = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
            _owner = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            iVar12 = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            iVar11 = 5;
            cbt = Commands::M_MAPPER_TOWER3_DESTROYED;
            break;
        case Map::Buildings::BT_TOWER4:
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, 0x32);
            sVar6 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
            uVar4 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            uVar5 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            iVar11 = 6;
            cbt = Commands::M_MAPPER_TOWER4_DESTROYED;
        LAB_0051717e:
            damageUnk = (int)sVar6;
            iVar12 = (int)(short)uVar5;
            _owner = (int)(short)uVar4;
            break;
        case Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                DAT_BuildingsState::ptr)(_buildingIDAtTile, 0x32);
            damageUnk = (int)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
            _owner = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x;
            DAT_BuildingsState::instance.buildings[_buildingIDAtTile].noRubble = 0;
            iVar12 = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                _buildingIDAtTile);
            iVar11 = 6;
            cbt = Commands::M_MAPPER_TOWER5_DESTROYED;
        }
        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)(
            damageUnk, _owner, iVar12, cbt, iVar11, 0xf);
        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
            _owner, iVar12, DE::SHCDE::FX_TOWER_SMASH);
        bVar9 = 1;
        local_8 = TRUE;
    LAB_0051769a:
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(7, xPosition, yPosition);
        return ~-(uint)bVar9 & local_8;
    switchD_00517137_caseD_1d:
        _owner = (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].buildingType;
        sVar6 = DAT_BuildingsState::instance.buildings[_buildingIDAtTile].owner;
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
            = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[_owner] == 0);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
            _buildingIDAtTile);
        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
            (int)(short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].x,
            (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingIDAtTile].y)),
            DE::SHCDE::FX_BUILDING_SMASH);
        if ((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                 && (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                && (DAT_GameState::instance.mapAndTime.playerTeams[sVar6]
                    != DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]))
            && (DAT_GameCore::instance.genieVoiceActive)) {
            if ((_owner == 0x13) || (_owner == 0xb)) {
                /*
                  "Excellent"
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_23.wav");
            }
            if ((_owner == 8) || (_owner == 9)) {
                /*
                  "Bravo"
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_24.wav");
            }
        }
    LAB_005175ec:
        local_8 = TRUE;
        goto LAB_0051769a;
    }

}
}
