#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B0AC0
    void DisplayElements::RenderPeopleLeftToPlaceDisplayElement(int posX, int posY, DWORD elementState)
    {
        int xParam;
        int yParam;
        xParam = posX;
        yParam = posY;
        /*
          "People available to place:"   added by script: "People Available to Place:"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x2c),
            xParam, yParam, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0, 0x11, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            2499 - DAT_UnitsState::instance.unitCount,
            DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + 6 + posX, posY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb,
            0, 0x11, FALSE, 0);
    }

}
}
