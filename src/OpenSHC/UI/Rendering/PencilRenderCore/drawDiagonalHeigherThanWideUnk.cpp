#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00471220
        void PencilRenderCore::drawSteepLine()
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int _negativeHeightX2;
            iVar1 = this->deltaX * 2;
            _negativeHeightX2 = this->deltaY * -2;
            iVar3 = iVar1 - this->deltaY;
            for (; -1 < this->deltaY; this->deltaY = this->deltaY + -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                iVar2 = iVar1;
                if (0 < iVar3) {
                    this->currentX = this->currentX + this->stepX;
                    iVar2 = iVar1 + _negativeHeightX2;
                }
                this->currentY = this->currentY + this->stepY;
                iVar3 = iVar3 + iVar2;
            }
        }

    }
}
}
