#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00475CC0
        void PencilRenderCore::drawHeaderTextBanner(
            int textGroupIndex, int textNumInGroup, int xPos, int yPos, int width, int param_6)
        {
            char* _textAddress;
            int _textY;
            int _width;
            int iVar2;
            int iVar3;
            int iVar4;
            int _blendStrength;
            int _textX;
            int _fontSize;
            TextAlignment _alignment;
            BGR24 _color;
            BOOLEnum _keepOffsetX;
            int iVar1 = xPos;
            iVar2 = xPos + 8;
            _width = width + -0x10;
            for (xPos = 0; xPos < 0x40; xPos += 8) {
                if (xPos == 0) {
                    iVar4 = 0x30;
                } else {
                    iVar4 = (-(uint)(xPos != 0x38) & 0xfffffffa) + 0x3c;
                }
                for (iVar3 = 0; iVar3 < _width; iVar3 += 8) {
                    int imageID = iVar4;
                    if ((iVar3 != 0) && (imageID = iVar4 + 2, iVar3 != width + -0x18)) {
                        imageID = iVar4 + 1;
                    }
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, imageID,
                        iVar3 + iVar2, xPos + yPos + 8, IO::Graphics::GID_INTERFACE_ICONS_3, imageID + 3, 0);
                }
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b, iVar1 + 0xb,
                yPos + 0x11, IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b,
                (iVar2 - DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x9c] + 0x5a].width) + -3
                    + _width,
                yPos + 0x11, IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
            _blendStrength = 0;
            _keepOffsetX = FALSE;
            _fontSize = 0xf;
            _color = 0xc2f0eb;
            _alignment = Text::TTA_CENTER;
            _textY = yPos + 0x16;
            _textX = _width / 2 + iVar2;
            _textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)textGroupIndex, textNumInGroup);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                _textAddress, _textX, _textY, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
        }

    }
}
}
