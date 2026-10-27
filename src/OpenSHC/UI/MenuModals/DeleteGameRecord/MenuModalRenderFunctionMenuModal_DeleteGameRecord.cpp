#include "../DeleteGameRecord.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::GameLanguage;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9CC0
        void DeleteGameRecord::MenuModalRenderFunctionMenuModal_DeleteGameRecord(int x, int y, int width, int height)
        {
            int yParam;
            if ((DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_FRENCH)
                && (DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_SPANISH)) {
                /*
                  added by script: "Delete Game Record?"
                 */
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0xff, 0xd, x, y, width, height);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                DAT_PencilRenderCore::ptr)(x, y, width, height);
            yParam = y + 0x1b;
            int xParam = width / 2 + x;
            /*
              added by script: "Delete Game Record?"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0xd),
                xParam, yParam, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x11, FALSE, 0);
        }

    }
}
}
