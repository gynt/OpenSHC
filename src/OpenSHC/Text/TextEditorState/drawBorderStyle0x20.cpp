#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/g_textDialogPaddingX.hpp"
#include "OpenSHC/Globals/g_textDialogPaddingY.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/g_textDialogMarginWidth.hpp"
#include "OpenSHC/Globals/g_textDialogMarginHeight.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D6C0
    void TextEditorState::setDialogRectAndContentArea(int dialogX, int dialogY, int dialogWidth, int dialogHeight)
    {
        this->dialogX = dialogX;
        this->dialogY = dialogY;
        this->dialogWidth = dialogWidth;
        this->dialogHeight = dialogHeight;

        // NOTE: dialogWidth is used to compute the content height and vice versa, no idea if something was switched;
        //   also, the required order feels strange, maybe they used a RECT struct or macro
        // FIXME: ContentHeight and ContentWidth or the dialogWidth and dialogHeight are swapped
        int const contentX = this->dialogX + g_textDialogPaddingX::instance;
        int const contentY = this->dialogY + g_textDialogPaddingY::instance;
        int const contentHeight = this->dialogHeight - g_textDialogMarginHeight::instance;
        int const contentWidth = this->dialogWidth - g_textDialogMarginWidth::instance;
        this->dialogContentX = contentX;
        this->dialogContentY = contentY;
        this->dialogContentWidth = contentWidth;
        this->dialogContentHeight = contentHeight;

        this->helpContentScrollX = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
        this->helpContentScrollY = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
    }

}
}
