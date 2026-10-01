#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047FB50
    void GameSynchronyState::renderChatMessageList(int xPos, int yPos, int param_3)
    {
        int iVar1;
        int iVar2;
        this->field204_0x105670 = this->DAT_ChatMessageArrayIndex - param_3;
        if (this->field204_0x105670 < 0) {
            this->field204_0x105670 = this->field204_0x105670 + 0x14;
        }
        iVar2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(yPos + -0x48, yPos + 0x12);
        DAT_TextManagerObject::instance.field13_0x34 = 0x11;
        param_3 = 0;
        do {
            if (this->DAT_ChatEventArray[this->field204_0x105670].flag == 1) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(this->DAT_ChatMessageSubjectPlayerNameArray[this->field204_0x105670],
                    xPos, yPos, OpenSHC::Text::TTA_LEFT,
                    (uint)((int)(DAT_RenderingDefinedData::instance.ColorTable1[DAT_BlendingDefinedData::instance
                            .PlayerSlotUnitColor[this->DAT_ChatEventArray[this->field204_0x105670].subjectPlayer]])),
                    0, 0x13, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(
                    this->DAT_ChatMessageArray[this->field204_0x105670], 0, 0,
                    0x1ee - DAT_TextManagerObject::instance.currentXOffset_0x0, 0, 0, 1);
                if (0x18 < iVar1) {
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    yPos = yPos + -0x12;
                    iVar2 = iVar2 + 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[this->field204_0x105670], xPos, yPos,
                        OpenSHC::Text::TTA_LEFT,
                        (uint)((int)(DAT_RenderingDefinedData::instance
                                .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                        [this->DAT_ChatEventArray[this->field204_0x105670].subjectPlayer]])),
                        0, 0x13, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    this->DAT_ChatMessageArray[this->field204_0x105670],
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 6 + xPos, yPos,
                    0x1ee - DAT_TextManagerObject::instance.currentXOffset_0x0, 0xa2ff, 0x3e66, 0x13,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            this->field204_0x105670 = this->field204_0x105670 + -1;
            if (this->field204_0x105670 < 0) {
                this->field204_0x105670 = 0x13;
            }
            iVar2 = iVar2 + 1;
            yPos = yPos + -0x11;
        } while ((iVar2 < 5) && (param_3 = param_3 + 1, param_3 < 5));
        DAT_TextManagerObject::instance.field13_0x34 = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
            DAT_TextureRenderCoreObject::ptr)();
    }

}
}
