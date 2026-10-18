#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EED0
    void GameSynchronyState::renderDebugDataSplitInfo(int x, int y, int width, int height)
    {
        int iVar1;
        int* piVar3;
        char* textAddress;
        x = x + 2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Splinter_box_005a725c, x, y, Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        if (!this->splinterType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Chimps_005a7250, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        } else if (this->splinterType == 1) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Structures_005a7240, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        } else if (this->splinterType == 2) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Vegetation_005a7230, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        } else if (this->splinterType == 3) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Tribes_005a7224, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        } else if (this->splinterType == 4) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Players_005a7218, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        } else if (this->splinterType == 5) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s___Game_elements_005a7204, x + 10, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Total_split_data_items__005a71e8, x, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        int xParam = x + 0xa;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->totalSplitDataItems, xParam, y + 0x1c, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        if (!this->splinterType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_chimps__005a71d0, x, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitChimps, xParam, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_chimp__005a71b8, x + 0xc8, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitChimps, x + 0xd2, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            for (piVar3 = this->HASH_Units[2] + 1, x = 10; x; xParam = xParam + 0x28, piVar3 = piVar3 + 1, x = x + -1) {
                uint color = 0xffffff;
                if (piVar3[-0x9c4] != *piVar3) {
                    color = 0xff;
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    piVar3[-0x9c4], xParam, y + 0x46, Text::TTA_LEFT, color, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *piVar3, xParam, y + 0x54, Text::TTA_LEFT, color, 0x12, FALSE, 0);
            }
            return;
        }
        if (this->splinterType == 1) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_structures__005a719c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitStructures, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_structure__005a7180, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitStructures, x + 0xd2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            return;
        }
        if (this->splinterType == 2) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_veg__005a716c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitVeg, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_veg__005a7158, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitVeg, x + 0xd2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            return;
        }
        if (this->splinterType == 3) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_tribes__005a7140, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitTribes, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_tribe__005a7128, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitTribe, x + 0xd2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            return;
        }
        if (this->splinterType == 4) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_players__005a7110, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitPlayers, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_player__005a70f8, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitPlayer;
        } else if (this->splinterType == 5) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_elements__005a70e0, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitElements, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_element__005a70c8, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitElement;
        } else if (this->splinterType == 6) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_layers__005a70b0, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitLayers, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_layer__005a7098, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitLayer;
        } else if (this->splinterType == 7) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_flies__005a7080, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitFlies, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_fly__005a706c, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitFly;
        } else if (this->splinterType == 8) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_moats__005a7054, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitMoats, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_moat__005a7040, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitMoat;
        } else if (this->splinterType == 9) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_teleports__005a7024, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitTeleports, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_teleport__005a700c, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitTeleports;
        } else if (this->splinterType == 10) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_pitch_ditchs__005a6ff0, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitPitchDitches, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_pitch_ditch__005a6fd4, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitPitchDitch;
        } else if (this->splinterType == 0xb) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Total_split_zones__005a6fbc, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                this->totalSplitZones, xParam, iVar1, 0x80ff, 0x12, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_First_split_zone__005a6fa8, x + 0xc8, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            x = this->firstSplitZone;
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
            x, x + 0xd2, y + 0x2a, 0x80ff, 0x12, 1);
    }

}
}
