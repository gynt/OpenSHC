#include "../ChooseRandomNumberOfEnemies.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE070
        void ChooseRandomNumberOfEnemies::MenuModalRenderFunction_ChooseRandomNumberOfEnemies(
            int x, int y, int width, int height)
        {
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            iVar5 = 0;
            iVar4 = 0x11;
            iVar2 = y + 100;
            iVar3 = x + 300;
            /*
              added by script: "How many opponents can you handle!"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 1), iVar3, iVar2, OpenSHC::Text::TTA_CENTER, 0xccfaff, iVar4, FALSE, iVar5);
            iVar5 = 0x12;
            iVar4 = 400;
            iVar2 = y + 300;
            iVar3 = x + 100;
            /*
              added by script: "This will create some random opponents for you. You can   still change opponent types
              afterwards."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 2), iVar3, iVar2, iVar4, 0xccfaff, iVar5, 0);
        }

    }
}
}
