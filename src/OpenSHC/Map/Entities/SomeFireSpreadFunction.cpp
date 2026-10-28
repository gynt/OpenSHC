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

    // Tile coordinates: signed micro / 8 (orig cdq; and 7; sar 3) compared unsigned (ja 0x405181/0x405188).
    // The existing fire's level is compared signed (movsx; cmp; jle 0x405234), fireLevel > 2 signed (jl 0x405290).
    // FUNCTION: STRONGHOLDCRUSADER 0x00405130
    uint Entities::SomeFireSpreadFunction(int playerID, int x, int y, int height, int fireLevel)
    {
        int randomValue = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        randomValue &= 0x3f;
        x += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomValue][0];
        y += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomValue][1];
        uint tileX = x / 8;
        uint tileY = y / 8;
        if ((tileX > 399) || (tileY > 399)) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
            return 0;
        }
        int tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX;
        int logicFlags = DAT_TileMapState::instance.LogicLayer[tile];
        if ((logicFlags & 0x10300131) != 0) {
            return 0;
        }
        short buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
        if (buildingID != 0) {
            int buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            if ((buildingType != OpenSHC::Map::Buildings::BT_TUNNEL)
                && (buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT)
                && (buildingType != OpenSHC::Map::Buildings::BT_TUNNEL_CONSTRUCTION)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::lightUpBuilding,
                    DAT_BuildingsState::ptr)(buildingID, playerID, 0);
                return 0;
            }
        }
        int existingFireID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile);
        if (existingFireID != 0) {
            short existingFireLevel = DAT_EntityState::instance.entityArray[existingFireID].fireLevel;
            DAT_EntityState::instance.entityArray[existingFireID].animState = 0;
            if (fireLevel > existingFireLevel) {
                DAT_EntityState::instance.entityArray[existingFireID].fireLevel = fireLevel;
            }
            DAT_EntityState::instance.entityArray[existingFireID].animFrameCounter = 0;
            return 0;
        }
        if ((logicFlags & 0x1000) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(tile, playerID);
        }
        uint newFireID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity,
            DAT_EntityState::ptr)(0, playerID, 0, x, y, height, 0, 0, 0, OpenSHC::Map::Entities::ET_FIRE, 0);
        if ((fireLevel >= 3) && ((DAT_TileMapState::instance.RandomLayer[tile] & 3) == 0)) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0,
                playerID, 0, x, y, height, 0, 0, 0, OpenSHC::Map::Entities::ET_EXPLOSION, 0);
        }
        if (newFireID != 0) {
            DAT_EntityState::instance.entityArray[newFireID].fireLevel = fireLevel;
        }
        return newFireID;
    }

}
}
