#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Tile coordinates: signed micro / 8 compared unsigned (orig ja 0x405331/0x405338). Gatehouses and towers
    // 1..5 are immune (jump table 0x4054AC, index bytes 0x4054B4). Existing fire level compared signed (jle
    // 0x4053CE), fireLevel > 2 signed (jl 0x405452).
    // FUNCTION: STRONGHOLDCRUSADER 0x004052E0
    uint Entities::IgniteFireAtMiniTile(
        int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity)
    {
        int randomValue = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        randomValue &= 0x3f;
        miniTileX += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomValue][0];
        miniTileY += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomValue][1];
        uint tileX = miniTileX / 8;
        uint tileY = miniTileY / 8;
        if ((tileX > 399) || (tileY > 399)) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
            return 0;
        }
        int tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX;
        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10300131) != 0) {
            return 0;
        }
        short buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
        if (buildingID != 0) {
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                return 0;
            }
        }
        int existingFireID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile);
        if (existingFireID != 0) {
            short existingFireLevel = DAT_EntityState::instance.entityArray[existingFireID].fireLevel;
            DAT_EntityState::instance.entityArray[existingFireID].animState = 0;
            if (two > existingFireLevel) {
                DAT_EntityState::instance.entityArray[existingFireID].fireLevel = two;
            }
            DAT_EntityState::instance.entityArray[existingFireID].animFrameCounter = 0;
            return 0;
        }
        if (buildingID != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::lightUpBuilding, DAT_BuildingsState::ptr)(
                DAT_TileMapState::instance.BuildingLayer[tile], playerID, fireIntensity);
        }
        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x1000) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(tile, playerID);
        }
        uint newFireID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity,
            DAT_EntityState::ptr)(
            0, playerID, 0, miniTileX, miniTileY, tileHeightMin8, 0, 0, 0, OpenSHC::Map::Entities::ET_FIRE, 0);
        if ((two >= 3) && ((DAT_TileMapState::instance.RandomLayer[tile] & 3) == 0)) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0,
                playerID, 0, miniTileX, miniTileY, tileHeightMin8, 0, 0, 0, OpenSHC::Map::Entities::ET_EXPLOSION, 0);
        }
        if (newFireID != 0) {
            DAT_EntityState::instance.entityArray[newFireID].fireLevel = two;
            DAT_EntityState::instance.entityArray[newFireID].fireIntensity = fireIntensity;
        }
        return newFireID;
    }

}
}
