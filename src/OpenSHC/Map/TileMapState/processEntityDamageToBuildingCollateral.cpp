#include "../../Map.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
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
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingLogicalStateShort;
    using Map::Buildings::BuildingType;
    using Map::Entities::EntityType;
    using Map::Units::States::UnitState;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00517790
    void TileMapState::processEntityDamageToBuildingCollateral(
        int tile, uint x_2, uint y_2, int damage, int playerID, undefined4 unused, int unitID)
    {
        short* psVar1;
        int x;
        int* piVar2;
        BuildingLogicalStateShort BVar3;
        short sVar4;
        ushort uVar5;
        ushort uVar6;
        int bVar7;
        short _newHealth;
        uint _defensiveStructureOwner;
        uint uVar8;
        int iVar9;
        int _buildingType;
        int _OilSmelterXPosition;
        int _oilSmelterOwnerPlayerIndex;
        int _OilSmelterYPosition;
        int _buildingID;
        int _iter0till8;
        int _tile;
        short _ownerPlayerIndex;
        uint _oilSmelterTilePosition;
        int _tile_2;
        uint _y;
        _y = y_2;
        _tile_2 = tile;
        bVar7 = false;
        if ((playerID < 0)
            && (_OilSmelterYPosition = -playerID, iVar9 = playerID * -4, playerID = _OilSmelterYPosition,
                *(int*)((int)DAT_GameSynchronyState::ptr + iVar9 + 0x6a8) == -1)) {
            bVar7 = true;
        }
        _iter0till8 = 0;
        do {
            /*
              relative lookaround by modifying tile and y
             */
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getTileForBrush, this)(
                0, _iter0till8, &tile, (int*)&y_2, _tile_2, _y);
            _tile = tile;
            uVar8 = this->LogicLayer[tile];
            if (((uVar8 & 0x10000400) == 0) && (this->BuildingLayer[tile] == 0)) {
                if ((((uVar8 & 0x100) != 0) && ((uVar8 & 2) == 0))
                    && ((_defensiveStructureOwner = this->WallOwnerLayer[tile] & 7,
                        !bVar7
                            || (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                != DAT_GameState::instance.mapAndTime.playerTeams[_defensiveStructureOwner + 1])))) {
                    DAT_GameState::instance.playerDataArray[_defensiveStructureOwner + 1].defensesDamagedByPlayer
                        = (short)playerID;
                    if (unitID != 0) {
                        if (DAT_GameState::instance.mapAndTime.playerTeams[_defensiveStructureOwner + 1]
                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                            psVar1 = &DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk;
                            *psVar1 = *psVar1 + 1;
                        } else {
                            DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
                        }
                    }
                    DAT_GameCore::instance.cowPoisonTrackerUnk
                        = DAT_GameCore::instance.cowPoisonTrackerUnk + damage * 10;
                    iVar9 = 0;
                    if (0 < damage) {
                        do {
                            if (this->HeightLayer[tile] <= this->DefaultHeightLayer[tile]) {
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                                    DAT_EntityState::ptr)(tile);
                                this->LogicLayer[_tile] = this->LogicLayer[_tile] & 0xffbef4ff;
                                this->HeightLayer[_tile] = this->DefaultHeightLayer[_tile];
                                this->DamageLayer[_tile] = 0;
                                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                      updatePathLinkagesInAllEightDirections,
                                    DAT_PathFindingState::ptr)(y_2, _tile);
                                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                                this->field204_0x554a30 = 1;
                                break;
                            }
                            this->HeightLayer[tile] = this->HeightLayer[tile] - 1;
                            if ((char)this->DamageLayer[tile] < 200) {
                                this->DamageLayer[tile] = this->DamageLayer[tile] + 1;
                            }
                            iVar9 = iVar9 + 1;
                        } while (iVar9 < damage);
                    }
                }
            } else {
                _buildingID = (int)this->BuildingLayer[tile];
                BVar3 = DAT_BuildingsState::instance.buildings[_buildingID].logicalState;
                if (((BVar3 != ((BuildingLogicalState)0))
                        && ((((BVar3 != Map::Buildings::BLS_REMOVE
                                  && (sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].currentHealth,
                                      sVar4 != 0))
                                 && (_buildingType
                                     = (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType,
                                     DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[_buildingType] != 0))
                            && (((uVar8 & 0xf000000) == 0 && ((uVar8 & 2) == 0))))))
                    && ((!bVar7
                        || (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_BuildingsState::instance.buildings[_buildingID].owner])))) {
                    _newHealth = sVar4 - (short)damage;
                    DAT_GameCore::instance.cowPoisonTrackerUnk
                        = DAT_GameCore::instance.cowPoisonTrackerUnk + damage * 10;
                    DAT_BuildingsState::instance.buildings[_buildingID].currentHealth = _newHealth;
                    switch (_buildingType) {
                    case 0x2d:
                    case 0x2e:
                    case 0x4a:
                    case 0x4b:
                    case 0x4c:
                    case 0x4d:
                    case 0x4e:
                        DAT_GameState::instance
                            .playerDataArray[DAT_BuildingsState::instance.buildings[_buildingID].owner]
                            .defensesDamagedByPlayer = (short)playerID;
                    }
                    if (unitID != 0) {
                        if (DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_BuildingsState::instance.buildings[_buildingID].owner]
                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                            psVar1 = &DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk;
                            *psVar1 = *psVar1 + 1;
                        } else {
                            DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
                        }
                    }
                    if (_newHealth < 1) {
                        if ((_buildingType != 0x4f) && ((_buildingType < 0x56 || (0x59 < _buildingType)))) {
                            _ownerPlayerIndex = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned + playerID;
                            *piVar2 = *piVar2 + 1;
                            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed
                                + _ownerPlayerIndex;
                            *piVar2 = *piVar2 + 1;
                            piVar2 = (int*)(_ownerPlayerIndex * 0x39f4 + 0x115e9d8 + playerID * 0x20);
                            *piVar2 = *piVar2 + 1;
                        }
                        switch (_buildingType) {
                        case 0x1c:
                        case 0x2d:
                        case 0x2e:
                        case 0x4a:
                        case 0x4b:
                        case 0x4c:
                        case 0x4d:
                        case 0x4e:
                            MACRO_CALL_MEMBER(
                                AI::AICState_Func::playAnger2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                                (int)DAT_BuildingsState::instance.buildings[_buildingID].owner, playerID);
                            break;
                        default:
                            MACRO_CALL_MEMBER(
                                AI::AICState_Func::playVictory2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                                (int)DAT_BuildingsState::instance.buildings[_buildingID].owner, playerID);
                        }
                        switch (DAT_BuildingsState::instance.buildings[_buildingID].buildingType) {
                        case Map::Buildings::BT_OILSMELTER:
                            iVar9 = DAT_BuildingsState::instance.buildings[_buildingID].resources[7];
                            if (iVar9 == 0)
                                goto switchD_00517b1f_caseD_1d;
                            _oilSmelterTilePosition
                                = DAT_BuildingsState::instance.buildings[_buildingID].currentTilePositionAdjusted;
                            _OilSmelterXPosition = (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].x;
                            _oilSmelterOwnerPlayerIndex
                                = (int)DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            _OilSmelterYPosition = (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            if (iVar9 < 5) {
                                MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(_oilSmelterOwnerPlayerIndex,
                                    _OilSmelterXPosition * 8 + 0x10, _OilSmelterYPosition * 8 + 0x10,
                                    (int)((int)((uint)this->HeightLayer[_oilSmelterTilePosition])), 3);
                            } else {
                                iVar9 = _OilSmelterYPosition * 8 + 0x10;
                                x = _OilSmelterXPosition * 8 + 0x10;
                                MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(_oilSmelterOwnerPlayerIndex, x,
                                    iVar9, (int)((int)((uint)this->HeightLayer[_oilSmelterTilePosition])), 5);
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                    DAT_EntityState::ptr)(0, (undefined4)((int)(_oilSmelterOwnerPlayerIndex)), 0, x,
                                    iVar9, (int)((int)((uint)this->HeightLayer[_oilSmelterTilePosition])), 0, 0, 0,
                                    Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                            }
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                _OilSmelterXPosition, _OilSmelterYPosition, DE::SHCDE::FX_IGNITE_PITCH);
                            break;
                        case Map::Buildings::BT_GATEHOUSELARGE:
                        case Map::Buildings::BT_GATEHOUSESMALL:
                            iVar9 = MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::findParticularBuilding,
                                DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[_buildingID].owner,
                                (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].x)),
                                (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].y)),
                                (int)((int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight)),
                                Map::Buildings::BT_DRAWBRIDGE, 0);
                            if (iVar9 != 0) {
                                this->showNoRubbleWhenDestroyingBuilding
                                    = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                                [(short)DAT_BuildingsState::instance.buildings[iVar9].buildingType]
                                        == 0);
                                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                                    DAT_BuildingsState::ptr)(iVar9);
                                iVar9 = MACRO_CALL_MEMBER(
                                    Map::Buildings::BuildingsState_Func::findParticularBuilding,
                                    DAT_BuildingsState::ptr)(
                                    (int)DAT_BuildingsState::instance.buildings[_buildingID].owner,
                                    (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].x)),
                                    (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].y)),
                                    (int)((int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight)),
                                    Map::Buildings::BT_DRAWBRIDGE, iVar9);
                                if (iVar9 != 0) {
                                    this->showNoRubbleWhenDestroyingBuilding
                                        = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                                    [(short)DAT_BuildingsState::instance.buildings[iVar9].buildingType]
                                            == 0);
                                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                                        DAT_BuildingsState::ptr)(iVar9);
                                }
                            }
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x32);
                            this->showNoRubbleWhenDestroyingBuilding
                                = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                            [(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType]
                                    == 0);
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)(short)uVar6, (int)((int)((short)uVar5)), DE::SHCDE::FX_TOWER_SMASH);
                            break;
                        case Map::Buildings::BT_TUNNEL:
                            uVar8 = (uint)DAT_BuildingsState::instance.buildings[_buildingID].unitRefID;
                            if (DAT_UnitsState::instance.units[uVar8].state.generic
                                != (Map::Units::States::US_STAND_UPUnk
                                    | Map::Units::States::US_IDLEUnk)) {
                                DAT_UnitsState::instance.units[uVar8].totalSizeOfPathPlan
                                    = DAT_UnitsState::instance.units[uVar8].currentIndexInPathPlan;
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::applyTunnelDamageAlongPathPlan,
                                    DAT_UnitsState::ptr)(uVar8);
                            }
                            DAT_UnitsState::instance.units[uVar8].state.generic
                                = Map::Units::States::US_DISAPPEAR;
                            DAT_UnitsState::instance.units[uVar8].disappearFadeAlphaCountdown = 0x20;
                            DAT_UnitsState::instance.units[uVar8].updateTickTracker = 0x20;
                        default:
                        switchD_00517b1f_caseD_1d:
                            iVar9 = (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            this->showNoRubbleWhenDestroyingBuilding
                                = (int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[iVar9] == 0);
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].x,
                                (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].y)),
                                DE::SHCDE::FX_BUILDING_SMASH);
                            if ((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                                     && (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                                    && (DAT_GameState::instance.mapAndTime.playerTeams[sVar4]
                                        != DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]))
                                && (DAT_GameCore::instance.genieVoiceActive != FALSE)) {
                                if ((iVar9 == 0x13) || (iVar9 == 0xb)) {
                                    /*
                                      "Excellent"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)("Genie_23.wav");
                                }
                                if ((iVar9 == 8) || (iVar9 == 9)) {
                                    /*
                                      "Bravo"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)("Genie_24.wav");
                                }
                            }
                            break;
                        case Map::Buildings::BT_SIEGETOWER_PLACED:
                            iVar9 = (int)DAT_BuildingsState::instance.buildings[_buildingID].unitRefID;
                            if ((iVar9 != 0)
                                && (DAT_BuildingsState::instance.buildings[_buildingID].unitRefUID
                                    == DAT_UnitsState::instance.units[iVar9].uid)) {
                                DAT_UnitsState::instance.units[iVar9].state.generic
                                    = Map::Units::States::US_DISAPPEAR;
                                DAT_UnitsState::instance.units[iVar9].disappearFadeAlphaCountdown = 0;
                                DAT_UnitsState::instance.units[iVar9].updateTickTracker = 0;
                                DAT_UnitsState::instance.units[iVar9].workplaceBuildingID_1 = 0;
                            }
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            break;
                        case Map::Buildings::BT_TOWER1:
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x19);
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)((int)sVar4,
                                (int)((int)((short)uVar5)), (int)((int)((short)uVar6)),
                                Commands::M_MAPPER_TOWER1_DESTROYED, 3, 0xf);
                            break;
                        case Map::Buildings::BT_TOWER2:
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x32);
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)((int)sVar4,
                                (int)((int)((short)uVar5)), (int)((int)((short)uVar6)),
                                Commands::M_MAPPER_TOWER2_DESTROYED, 4, 0xf);
                            break;
                        case Map::Buildings::BT_TOWER3:
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x32);
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)((int)sVar4,
                                (int)((int)((short)uVar5)), (int)((int)((short)uVar6)),
                                Commands::M_MAPPER_TOWER3_DESTROYED, 5, 0xf);
                            break;
                        case Map::Buildings::BT_TOWER4:
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x32);
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)((int)sVar4,
                                (int)((int)((short)uVar5)), (int)((int)((short)uVar6)),
                                Commands::M_MAPPER_TOWER4_DESTROYED, 6, 0xf);
                            break;
                        case Map::Buildings::BT_TOWER5:
                            MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(_buildingID, 0x32);
                            uVar5 = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            sVar4 = DAT_BuildingsState::instance.buildings[_buildingID].owner;
                            DAT_BuildingsState::instance.buildings[_buildingID].noRubble = 0;
                            uVar6 = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::deleteBuilding,
                                DAT_BuildingsState::ptr)(_buildingID);
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, this)((int)sVar4,
                                (int)((int)((short)uVar5)), (int)((int)((short)uVar6)),
                                Commands::M_MAPPER_TOWER5_DESTROYED, 6, 0xf);
                        }
                    }
                }
            }
            _iter0till8 = _iter0till8 + 1;
            if (8 < _iter0till8) {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                    DAT_PathFindingState::ptr)(9, x_2, _y);
            }
        } while (true);
    }

}
}
