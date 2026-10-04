#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Thin wrapper around calculateOrientation. Converts two tile indices (param_1, param_2) to (x, y)   coordinate
          pairs using the viewport translation matrix and DAT_TileTranslationMatrix_YComponent,   then delegates to
          calculateOrientation on DAT_DirectionAlgorithmState.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046C9A0
        void DirectionAlgorithmState::calculateOrientationFromTiles(int param_1, int param_2)
        {
            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation, this)(
                param_1
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1]]
                        .addXgetTile,
                (int)((int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1])),
                param_2
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_2]]
                        .addXgetTile,
                (int)((int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_2])));
        }

    }
}
}
