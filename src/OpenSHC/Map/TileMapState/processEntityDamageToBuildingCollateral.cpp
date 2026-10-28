
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
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_MERLON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00517790
    void TileMapState::processEntityDamageToBuildingCollateral(
        int tile, uint x, uint y, int damage, int playerID, undefined4 unused, int unitID)
    {
        int baseTile = tile;
        uint baseY = y;
        /* a negative player id is a request to spare that player's own team */
        int spareOwnTeam = 0;
        if (playerID < 0) {
            playerID = -playerID;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                spareOwnTeam = 1;
            }
        }

        for (int index = 0; index < 9; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                0, index, &tile, (int*)&y, baseTile, baseY);
            uint logic = this->LogicLayer[tile];
            if ((logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0 && this->BuildingLayer[tile] == 0) {
                /* bare wall: grind its height down towards the ground it stands on */
                if ((logic & L_WALL_OR_GATEHOUSE) == 0 || (logic & L_STOCKPILE) != 0) {
                    continue;
                }
                int wallOwner = (this->WallOwnerLayer[tile] & 7) + 1;
                if (spareOwnTeam != 0 && DAT_GameState::instance.mapAndTime.playerTeams[playerID] == DAT_GameState::instance.mapAndTime.playerTeams[wallOwner]) {
                    continue;
                }
                DAT_GameState::instance.playerDataArray[wallOwner].defensesDamagedByPlayer = (short)playerID;
                if (unitID != 0) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[wallOwner] == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                        DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount
                            = DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount + 1;
                    } else {
                        DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount = 0;
                    }
                }
                DAT_GameCore::instance.battleLevelAccumulator
                    = DAT_GameCore::instance.battleLevelAccumulator + damage * 10;
                for (int hit = 0; hit < damage; hit++) {
                    if (this->HeightLayer[tile] > this->DefaultHeightLayer[tile]) {
                        this->HeightLayer[tile] = this->HeightLayer[tile] - 1;
                        if ((char)this->DamageOrCropStageLayer[tile] < 200) {
                            this->DamageOrCropStageLayer[tile] = this->DamageOrCropStageLayer[tile] + 1;
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                            DAT_EntityState::ptr)(tile);
                        this->LogicLayer[tile] = this->LogicLayer[tile]
                            & ~(L_CRENEL_MERLON | L_UNKNOWN_WALL_RELATED | L_STAIRS | L_CRENEL
                                | L_WALL_OR_GATEHOUSE);
                        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                        this->DamageOrCropStageLayer[tile] = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                            DAT_PathFindingState::ptr)(y, tile);
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        DAT_TileMapState::instance.terrainChangedDirty = 1;
                        break;
                    }
                }
                continue;
            }

            int buildingID = this->BuildingLayer[tile];
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == (BuildingLogicalState)0 || DAT_BuildingsState::instance.buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_REMOVE) {
                continue;
            }
            short health = DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
            if (health == 0) {
                continue;
            }
            int buildingType = (short)DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            if (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[buildingType] == 0) {
                continue;
            }
            if ((logic & 0xf000000) != 0 || (logic & L_STOCKPILE) != 0) {
                continue;
            }
            if (spareOwnTeam != 0 && DAT_GameState::instance.mapAndTime.playerTeams[playerID] == DAT_GameState::instance.mapAndTime.playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]) {
                continue;
            }

            short newHealth = health - (short)damage;
            DAT_GameCore::instance.battleLevelAccumulator = DAT_GameCore::instance.battleLevelAccumulator + damage * 10;
            DAT_BuildingsState::instance.buildings[buildingID].currentHealth = newHealth;
            switch (buildingType) {
            case 0x2d:
            case 0x2e:
            case 0x4a:
            case 0x4b:
            case 0x4c:
            case 0x4d:
            case 0x4e:
                DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].defensesDamagedByPlayer = (short)playerID;
            }
            if (unitID != 0) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner] == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount
                        = DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount + 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount = 0;
                }
            }
            if (newHealth > 0) {
                continue;
            }

            if (buildingType != 0x4f && (buildingType <= 0x55 || buildingType > 0x59)) {
                int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedByPlayer[playerID]
                    = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedByPlayer[playerID] + 1;
                DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[owner]
                    = DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[owner] + 1;
                /* a per-attacker tally inside the owner's player data, 0x20 apart */
                int* tally = (int*)((char*)&DAT_GameState::instance.playerDataArray[owner].field889_0x2be0 + playerID * 0x20);
                *tally = *tally + 1;
            }
            switch (buildingType) {
            case 0x1c:
            case 0x2d:
            case 0x2e:
            case 0x4a:
            case 0x4b:
            case 0x4c:
            case 0x4d:
            case 0x4e:
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playAnger2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, playerID);
                break;
            default:
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playVictory2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, playerID);
            }

            int towerX;
            int towerY;
            int towerOwner;
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_TOWER1:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                    buildingID, 0x19);
                towerX = DAT_BuildingsState::instance.buildings[buildingID].x;
                towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                towerY = DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(towerOwner,
                    (short)towerX, (short)towerY, OpenSHC::Commands::M_MAPPER_TOWER1_DESTROYED, 3, 0xf);
                break;
            case OpenSHC::Map::Buildings::BT_TOWER2:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                    buildingID, 0x32);
                towerX = DAT_BuildingsState::instance.buildings[buildingID].x;
                towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                towerY = DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(towerOwner,
                    (short)towerX, (short)towerY, OpenSHC::Commands::M_MAPPER_TOWER2_DESTROYED, 4, 0xf);
                break;
            case OpenSHC::Map::Buildings::BT_TOWER3:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                    buildingID, 0x32);
                towerX = DAT_BuildingsState::instance.buildings[buildingID].x;
                towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                towerY = DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(towerOwner,
                    (short)towerX, (short)towerY, OpenSHC::Commands::M_MAPPER_TOWER3_DESTROYED, 5, 0xf);
                break;
            case OpenSHC::Map::Buildings::BT_TOWER4:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                    buildingID, 0x32);
                towerX = DAT_BuildingsState::instance.buildings[buildingID].x;
                towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                towerY = DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(towerOwner,
                    (short)towerX, (short)towerY, OpenSHC::Commands::M_MAPPER_TOWER4_DESTROYED, 6, 0xf);
                break;
            case OpenSHC::Map::Buildings::BT_TOWER5:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                    buildingID, 0x32);
                towerX = DAT_BuildingsState::instance.buildings[buildingID].x;
                towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                towerY = DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(towerOwner,
                    (short)towerX, (short)towerY, OpenSHC::Commands::M_MAPPER_TOWER5_DESTROYED, 6, 0xf);
                break;
            case OpenSHC::Map::Buildings::BT_OILSMELTER:
                if (DAT_BuildingsState::instance.buildings[buildingID].resources[7] == 0) {
                    goto destroyNormally;
                }
                {
                    /* a smelter with oil in it goes up, and a full one throws burning oil about */
                    int oilAmount = DAT_BuildingsState::instance.buildings[buildingID].resources[7];
                    uint smelterTile = DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted;
                    int smelterX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    int smelterOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                    int smelterY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                    if (oilAmount <= 4) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(smelterOwner, smelterX * 8 + 0x10,
                            smelterY * 8 + 0x10, this->HeightLayer[smelterTile], 3);
                    } else {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(smelterOwner, smelterX * 8 + 0x10,
                            smelterY * 8 + 0x10, this->HeightLayer[smelterTile], 5);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity,
                            DAT_EntityState::ptr)(0, smelterOwner, 0, smelterX * 8 + 0x10, smelterY * 8 + 0x10,
                            this->HeightLayer[smelterTile], 0, 0, 0,
                            OpenSHC::Map::Entities::ET_EXPLOSION, 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        smelterX, smelterY, OpenSHC::DE::SHCDE::FX_IGNITE_PITCH);
                }
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                {
                    /* a gatehouse takes its drawbridges with it */
                    int bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                    if (bridge != 0) {
                        this->showNoRubbleWhenDestroyingBuilding
                            = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[bridge].buildingType] == 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(bridge);
                        bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, bridge);
                        if (bridge != 0) {
                            this->showNoRubbleWhenDestroyingBuilding
                                = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[bridge].buildingType]
                                == 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(bridge);
                        }
                    }
                    ushort gateY = DAT_BuildingsState::instance.buildings[buildingID].y;
                    ushort gateX = DAT_BuildingsState::instance.buildings[buildingID].x;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                        buildingID, 0x32);
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType] == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (short)gateX, (short)gateY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                }
                break;
            case OpenSHC::Map::Buildings::BT_TUNNEL:
                {
                    /* the tunneller inside is buried where he stands */
                    int tunneller = DAT_BuildingsState::instance.buildings[buildingID].unitRefID;
                    if (DAT_UnitsState::instance.units[tunneller].state.generic
                        != (OpenSHC::Map::Units::States::US_STAND_UPUnk
                            | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        DAT_UnitsState::instance.units[tunneller].totalSizeOfPathPlan
                            = DAT_UnitsState::instance.units[tunneller].currentIndexInPathPlan;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::applyTunnelDamageAlongPathPlan,
                            DAT_UnitsState::ptr)(tunneller);
                    }
                    DAT_UnitsState::instance.units[tunneller].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[tunneller].fadeLevel = 0x20;
                    DAT_UnitsState::instance.units[tunneller].updateTickTracker = 0x20;
                }
                /* falls through: the tunnel itself is destroyed normally */
            default:
            destroyNormally:
                {
                    int destroyedType = (short)DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                    int destroyedOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[destroyedType] == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BUILDING_SMASH);
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && DAT_GameState::instance.mapAndTime.playerTeams[destroyedOwner] != DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        && DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        if (destroyedType == 0x13 || destroyedType == 0xb) {
                            /* "Excellent" */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_23.wav");
                        }
                        if (destroyedType == 8 || destroyedType == 9) {
                            /* "Bravo" */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_24.wav");
                        }
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                {
                    int rider = DAT_BuildingsState::instance.buildings[buildingID].unitRefID;
                    if (rider != 0 && DAT_BuildingsState::instance.buildings[buildingID].unitRefUID == DAT_UnitsState::instance.units[rider].uid) {
                        DAT_UnitsState::instance.units[rider].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                        DAT_UnitsState::instance.units[rider].fadeLevel = 0;
                        DAT_UnitsState::instance.units[rider].updateTickTracker = 0;
                        DAT_UnitsState::instance.units[rider].workplaceOrHomeBuildingID = 0;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                }
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(9, x, baseY);
    }

}
}
