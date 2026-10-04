#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Entities::EntityType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004054E0
    void Entities::AFireSpreadFunction(int playerID, int x, int y, int height, int param_5, int param_6)
    {
        short sVar1;
        uint y_2;
        int _entityID;
        int iVar2;
        BOOLEnum BVar3;
        uint _entityID2;
        uint x_2;
        int microY;
        uint _rng;
        int _tile;
        int microX;
        _rng = (uint)SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        microX = x + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_rng & 0x3f][0];
        microY = y + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_rng & 0x3f][1];
        x_2 = microX / 8;
        y_2 = microY / 8;
        if (((x_2 < 400) && (y_2 < 400)) && (*(char*)(y_2 * 400 + 0x21aec98 + x_2) != '\0')) {
            _tile = DAT_ViewportRenderState::instance.translationMatrix[y_2].addXgetTile + x_2;
            _entityID = MACRO_CALL_MEMBER(
                Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(_tile);
            if (_entityID != 0) {
                sVar1 = DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6;
                DAT_EntityState::instance.entityArray[_entityID].someTracker = 0;
                if (sVar1 < param_5) {
                    DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6 = (short)param_5;
                }
                DAT_EntityState::instance.entityArray[_entityID].unknownAnimationFrameRelated = 0;
            }
            if ((((DAT_TileMapState::instance.LogicLayer[_tile] & 0x1a7001b1U) == 0)
                    && ((DAT_TileMapState::instance.BuildingLayer[_tile] == 0
                        || (iVar2 = MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::lightUpBuilding, DAT_BuildingsState::ptr)(
                                (int)DAT_TileMapState::instance.BuildingLayer[_tile], playerID, param_6),
                            iVar2 != 0))))
                && (((DAT_TileMapState::instance.LogicLayer[_tile] & 0x1000U) == 0
                    || (BVar3 = MACRO_CALL_MEMBER(
                            Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(_tile, playerID),
                        BVar3 != FALSE)))) {
                _entityID2 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, (undefined4)((int)(playerID)), 0, microX, microY, height, 0, 0, 0,
                    Map::Entities::ET_FIRE, 0);
                if (_entityID2 != 0) {
                    DAT_EntityState::instance.entityArray[_entityID2].fireParameter_0xb6 = (short)param_5;
                    DAT_EntityState::instance.entityArray[_entityID2].fireIntensity = (short)param_6;
                }
                if ((2 < param_5) && ((DAT_TileMapState::instance.RandomLayer[_tile] & 3) == 0)) {
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                        DAT_EntityState::ptr)(0, (undefined4)((int)(playerID)), 0, microX, microY, height, 0, 0, 0,
                        Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                }
            }
        }
    }

}
}
