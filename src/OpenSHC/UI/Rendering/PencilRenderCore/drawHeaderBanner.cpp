#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00468FE0
        void PencilRenderCore::drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk)
        {
            int iVar3;
            int iVar4;
            int _x = xPos;
            int iVar1 = xPos + 8;
            int iVar2 = width + -0x10;
            for (xPos = 0; xPos < 0x40; xPos += 8) {
                if (xPos == 0) {
                    iVar4 = 0x30;
                } else {
                    iVar4 = (-(uint)(xPos != 0x38) & 0xfffffffa) + 0x3c;
                }
                for (iVar3 = 0; iVar3 < iVar2; iVar3 += 8) {
                    int _imageID = iVar4;
                    if ((iVar3 != 0) && (_imageID = iVar4 + 2, iVar3 != width + -0x18)) {
                        _imageID = iVar4 + 1;
                    }
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, _imageID,
                        iVar3 + iVar1, xPos + yPos + 8, IO::Graphics::GID_INTERFACE_ICONS_3, _imageID + 3, 0);
                }
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b, _x + 0xb,
                yPos + 0x11, IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b,
                (iVar1 - DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x9c] + 0x5a].width) + -3
                    + iVar2,
                yPos + 0x11, IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
        }

    }
}
}
