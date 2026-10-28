
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
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

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
      beware the renames! this is for both stones as well as units hitting walls   decompilerscript: committed:
      2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00516B80
    BOOLEnum TileMapState::processDamageToBuilding(int tile, uint xPosition, uint yPosition, int damageUnk,
        int param_5, int playerID, BOOLEnum aiBuildDelayRelated, int unitID)
    {
        BOOLEnum destroyed = FALSE;
        int replaced = 0;
        /* a negative player id is a request to spare that player's own team */
        int spareOwnTeam = 0;
        if (playerID < 0) {
            playerID = -playerID;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                spareOwnTeam = 1;
            }
        }

        uint logic = this->LogicLayer[tile];
        if ((logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0 && this->BuildingLayer[tile] == 0) {
            if ((logic & L_WALL_OR_GATEHOUSE) != 0) {
                if ((logic & L_STOCKPILE) != 0) {
                    return FALSE;
                }
                int wallOwner = (this->WallOwnerLayer[tile] & 7) + 1;
                if (spareOwnTeam != 0 && DAT_GameState::instance.mapAndTime.playerTeams[playerID] == DAT_GameState::instance.mapAndTime.playerTeams[wallOwner]) {
                    return FALSE;
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
                /* a wall standing alone takes half again the damage, a well connected one half */
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::countLogicPropertyInSurroundingTiles, this)(
                    tile, yPosition, L_KEEP_NON_MANOR_HOUSE | L_WALL_OR_GATEHOUSE);
                if ((int)this->DAT_CardinalTilesAroundTile < 2) {
                    damageUnk = damageUnk + damageUnk / 2;
                } else if ((int)this->DAT_CardinalTilesAroundTile > 2) {
                    damageUnk = damageUnk / 2;
                }
                if (param_5 != 0) {
                    damageUnk = 0;
                }
                DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount
                    = DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount + 1;
                DAT_GameCore::instance.battleLevelAccumulator
                    = DAT_GameCore::instance.battleLevelAccumulator + damageUnk * 10;
                if (param_5 == 0 && (this->LogicLayer[tile] & L_UNKNOWN_WALL_RELATED) == 0
                    && this->DamageOrCropStageLayer[tile] == 0
                    && this->HeightLayer[tile] > this->DefaultHeightLayer[tile] + 60) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] - 20;
                }
                for (int hit = 0; hit < damageUnk; hit++) {
                    if (this->HeightLayer[tile] <= this->DefaultHeightLayer[tile]) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                            DAT_EntityState::ptr)(tile);
                        this->LogicLayer[tile] = this->LogicLayer[tile]
                            & ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS | L_UNKNOWN_WALL_RELATED
                                | L_CRENEL_MERLON);
                        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                        this->DamageOrCropStageLayer[tile] = 0;
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        DAT_TileMapState::instance.terrainChangedDirty = 1;
                        destroyed = TRUE;
                        break;
                    }
                    this->HeightLayer[tile] = this->HeightLayer[tile] - 1;
                    if ((char)this->DamageOrCropStageLayer[tile] < 200) {
                        this->DamageOrCropStageLayer[tile] = this->DamageOrCropStageLayer[tile] + 1;
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)(yPosition, tile);
            } else {
                destroyed = TRUE;
            }
            goto finish;
        }

        int buildingID = this->BuildingLayer[tile];
        if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == (BuildingLogicalState)0 || DAT_BuildingsState::instance.buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_REMOVE) {
            return TRUE;
        }
        short health = DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
        if (health == 0) {
            return TRUE;
        }
        DAT_GameCore::instance.battleLevelAccumulator = DAT_GameCore::instance.battleLevelAccumulator + damageUnk * 10;
        if (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType] == 0) {
            return TRUE;
        }
        if ((this->LogicLayer[tile] & 0xf000000) != 0) {
            return TRUE;
        }
        if (spareOwnTeam != 0 && DAT_GameState::instance.mapAndTime.playerTeams[playerID] == DAT_GameState::instance.mapAndTime.playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]) {
            return FALSE;
        }
        DAT_BuildingsState::instance.buildings[buildingID].currentHealth = health - (short)damageUnk;

        if (aiBuildDelayRelated == TRUE
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)) {
            /* a damaged gatehouse loses its drawbridges straight away */
                int bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
            if (bridge != 0) {
                if (DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[bridge].buildingType] != 0) {
                    this->showNoRubbleWhenDestroyingBuilding = 0;
                } else {
                    this->showNoRubbleWhenDestroyingBuilding = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(bridge);
                int second = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, bridge);
                if (second != 0) {
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[second].buildingType] == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(second);
                }
            }
        }

        switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
        case OpenSHC::Map::Buildings::BT_TOWER1:
        case OpenSHC::Map::Buildings::BT_TOWER2:
        case OpenSHC::Map::Buildings::BT_TOWER3:
        case OpenSHC::Map::Buildings::BT_TOWER4:
        case OpenSHC::Map::Buildings::BT_TOWER5:
            DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].defensesDamagedByPlayer = (short)playerID;
            break;
        default:
            break;
        }
        if (unitID != 0) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner] == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount
                    = DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount + 1;
            } else {
                DAT_UnitsState::instance.units[unitID].friendlyStructureHitCount = 0;
            }
        }

        short remaining = DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
        if (remaining > 0) {
            /* a siege tower's rider takes the damage with it */
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED && DAT_BuildingsState::instance.buildings[buildingID].unitRefID != 0
                && DAT_BuildingsState::instance.buildings[buildingID].unitRefUID == DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID].uid && DAT_BuildingsState::instance.buildings[buildingID].maxHealth != 0) {
                DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID].health
                    = ((int)remaining * DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID].maxHealth) / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                DAT_PathFindingState::ptr)(7, xPosition, yPosition);
            return ~-(uint)replaced & destroyed;
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL(OpenSHC::Map::Version_Func::UpdateDestroyedBuildingCountData)(1);
        }
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if (aiBuildDelayRelated == TRUE && DAT_GameState::instance.playerDataArray[owner].resourceRebuildDelay == 0) {
            DAT_GameState::instance.playerDataArray[owner].resourceRebuildDelay = 1;
        }
        int destroyedType = (short)DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        if (destroyedType != OpenSHC::Map::Buildings::BT_TOWER5_RUIN && (destroyedType < 0x56 || destroyedType > 0x59)) {
            DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedByPlayer[playerID]
                = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedByPlayer[playerID] + 1;
            DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID]
                = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID]
                + DAT_BuildingDefinedData::instance.destroyedScorePerType[destroyedType];
            DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[owner]
                = DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[owner] + 1;
            /* a per-attacker tally inside the owner's player data, 0x20 apart */
            int* tally = (int*)((char*)&DAT_GameState::instance.playerDataArray[owner].field889_0x2be0 + playerID * 0x20);
            *tally = *tally + 1;
        }
        switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
        case OpenSHC::Map::Buildings::BT_OILSMELTER:
        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
        case OpenSHC::Map::Buildings::BT_TOWER1:
        case OpenSHC::Map::Buildings::BT_TOWER2:
        case OpenSHC::Map::Buildings::BT_TOWER3:
        case OpenSHC::Map::Buildings::BT_TOWER4:
        case OpenSHC::Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playAnger2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                owner, playerID);
            break;
        default:
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playVictory2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                owner, playerID);
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_GameState::instance.mapAndTime.playerTeams[owner] != DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_TOWER4 || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_TOWER5
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_CHURCH
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_CATHEDRAL)
            && MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                   DAT_SoundSystemState::ptr)()
                == FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                /* "Watch it crumble" */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_36.wav");
            }
        }

        bool destroyNormally = false;
        int towerX = 0;
        int towerY = 0;
        int towerOwner = 0;
        int towerSize = 0;
        MappersEnum towerCommand = OpenSHC::Commands::M_MAPPER_NULL;
        switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
        case OpenSHC::Map::Buildings::BT_OILSMELTER:
            if (DAT_BuildingsState::instance.buildings[buildingID].resources[7] == 0) {
                destroyNormally = true;
                break;
            }
            {
                /* a smelter with oil in it goes up, and a full one throws burning oil about */
                int oilAmount = DAT_BuildingsState::instance.buildings[buildingID].resources[7];
                int smelterX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                int smelterOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                uint smelterTile = DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted;
                DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
                int smelterY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
                if (oilAmount < 5) {
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
                destroyed = TRUE;
            }
            break;
        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            {
                int bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                if (bridge != 0) {
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[bridge].buildingType] == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(bridge);
                    int second = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].owner, (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, bridge);
                    if (second != 0) {
                        this->showNoRubbleWhenDestroyingBuilding
                            = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[second].buildingType] == 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(second);
                    }
                }
                ushort gateY = DAT_BuildingsState::instance.buildings[buildingID].y;
                ushort gateX = DAT_BuildingsState::instance.buildings[buildingID].x;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(buildingID, 50);
                this->showNoRubbleWhenDestroyingBuilding = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType] == 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (short)gateX, (short)gateY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                destroyed = TRUE;
            }
            break;
        case OpenSHC::Map::Buildings::BT_TUNNEL:
            {
                /* the tunneller inside is buried where he stands */
                uint tunneller = DAT_BuildingsState::instance.buildings[buildingID].unitRefID;
                if (DAT_UnitsState::instance.units[tunneller].state.generic
                    != (OpenSHC::Map::Units::States::US_STAND_UPUnk
                        | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                    DAT_UnitsState::instance.units[tunneller].totalSizeOfPathPlan = DAT_UnitsState::instance.units[tunneller].currentIndexInPathPlan;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::applyTunnelDamageAlongPathPlan,
                        DAT_UnitsState::ptr)(tunneller);
                }
                DAT_UnitsState::instance.units[tunneller].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[tunneller].fadeLevel = 0x20;
                DAT_UnitsState::instance.units[tunneller].updateTickTracker = 0x20;
            }
            destroyNormally = true;
            break;
        default:
            destroyNormally = true;
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
                destroyed = TRUE;
            }
            break;
        case OpenSHC::Map::Buildings::BT_TOWER1:
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                buildingID, 0x19);
            towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
            towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            towerSize = 3;
            towerCommand = OpenSHC::Commands::M_MAPPER_TOWER1_DESTROYED;
            replaced = 1;
            break;
        case OpenSHC::Map::Buildings::BT_TOWER2:
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                buildingID, 0x32);
            towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
            towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            towerSize = 4;
            towerCommand = OpenSHC::Commands::M_MAPPER_TOWER2_DESTROYED;
            replaced = 1;
            break;
        case OpenSHC::Map::Buildings::BT_TOWER3:
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                buildingID, 0x32);
            towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
            towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            towerSize = 5;
            towerCommand = OpenSHC::Commands::M_MAPPER_TOWER3_DESTROYED;
            replaced = 1;
            break;
        case OpenSHC::Map::Buildings::BT_TOWER4:
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                buildingID, 0x32);
            towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
            towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            towerSize = 6;
            towerCommand = OpenSHC::Commands::M_MAPPER_TOWER4_DESTROYED;
            replaced = 1;
            break;
        case OpenSHC::Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding, DAT_BuildingsState::ptr)(
                buildingID, 0x32);
            towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            DAT_BuildingsState::instance.buildings[buildingID].leavesRubble = 0;
            towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            towerSize = 6;
            towerCommand = OpenSHC::Commands::M_MAPPER_TOWER5_DESTROYED;
            replaced = 1;
            break;
        }

        if (replaced != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                towerOwner, towerX, towerY, towerCommand, towerSize, 0xf);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
            destroyed = TRUE;
        } else if (destroyNormally) {
            short rubbleOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            this->showNoRubbleWhenDestroyingBuilding = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[destroyedType] == 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (short)DAT_BuildingsState::instance.buildings[buildingID].x, (short)DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BUILDING_SMASH);
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_GameState::instance.mapAndTime.playerTeams[rubbleOwner] != DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
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
            destroyed = TRUE;
        }
    finish:
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(7, xPosition, yPosition);
        return ~-(uint)replaced & destroyed;
    }

}
}
