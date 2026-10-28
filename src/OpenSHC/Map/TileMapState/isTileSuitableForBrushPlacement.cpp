#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /* inlined copy of ViewportRenderState::xyAreValid (the original inlines it here except for the last check) */
    static inline BOOLEnum tileXYAreValid(uint x, uint y)
    {
        if (x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
            return TRUE;
        }
        return FALSE;
    }

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FBE70
    BOOLEnum TileMapState::isTileHigherThanAnyNeighbour(int tile, uint x, uint y)
    {
        byte height = this->HeightLayer[tile];
        /* the tile suits a brush as soon as it stands above any one of its eight neighbours */
        if (tileXYAreValid(x, y - 1)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x + 1, y - 1)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x + 1, y)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x + 1, y + 1)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x, y + 1)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x - 1, y + 1)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x - 1]) > 0) {
            return TRUE;
        }
        if (tileXYAreValid(x - 1, y)
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x - 1]) > 0) {
            return TRUE;
        }

        if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                x - 1, y - 1)
                != FALSE
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x - 1]) > 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
