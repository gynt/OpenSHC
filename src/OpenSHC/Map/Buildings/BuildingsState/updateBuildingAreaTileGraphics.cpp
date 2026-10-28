#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EFD0
        ushort* BuildingsState::updateBuildingAreaTileGraphics(int param_1)
        {
            // The original returns whatever is left in eax: the last frame or the last updated display entry
            ushort* result;
            for (int i = 0; i < 23; ++i) {
                int tile = this->buildings[param_1].tileRefs[4 + i];
                int stage = (char)DAT_TileMapState::instance.DamageOrCropStageLayer[tile];
                int frame = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getViewRelativeDirectionFrame,
                    DAT_TileMapState::ptr)(stage);
                int gfx = GMFirstPictureIndex::instance[14] + frame + 55;
                result = (ushort*)gfx;
                if (gfx != DAT_TileMapState::instance.GfxLayer[tile]) {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] &= ~0xc;
                    result = (ushort*)&DAT_TileMapState::instance.MiscDisplayLayer[tile];
                }
            }
            return result;
        }

    }
}
}
