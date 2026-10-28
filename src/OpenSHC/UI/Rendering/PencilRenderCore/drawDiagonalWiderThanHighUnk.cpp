#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00471280
        void PencilRenderCore::drawShallowLine()
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int _negativeHeightX2;
            iVar1 = this->deltaY * 2;
            _negativeHeightX2 = this->deltaX * -2;
            iVar3 = iVar1 - this->deltaX;
            for (; -1 < this->deltaX; this->deltaX = this->deltaX + -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                iVar2 = iVar1;
                if (0 < iVar3) {
                    this->currentY = this->currentY + this->stepY;
                    iVar2 = iVar1 + _negativeHeightX2;
                }
                this->currentX = this->currentX + this->stepX;
                iVar3 = iVar3 + iVar2;
            }
        }

    }
}
}
