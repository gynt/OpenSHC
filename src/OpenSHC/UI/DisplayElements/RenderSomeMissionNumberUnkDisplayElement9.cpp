#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AFA80
    void DisplayElements::RenderSomeMissionNumberUnkDisplayElement9(int posX, int posY, DWORD MissionNumPlus1Unk)
    {
        if (MissionNumPlus1Unk - 1 == 0) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Mission : Defaults", posX, posY, Text::TTA_LEFT, 0x80ff, 0, 0xf, FALSE, 0);
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            "Mission :", posX, posY, Text::TTA_LEFT, 0x80ff, 0, 0xf, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            MissionNumPlus1Unk - 1, posX + 3, posY, Text::TTA_LEFT, 0x80ff, 0, 0xf, TRUE, 0);
    }

}
}
