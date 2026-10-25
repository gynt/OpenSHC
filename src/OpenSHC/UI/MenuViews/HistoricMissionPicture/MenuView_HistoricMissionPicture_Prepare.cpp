#include "../HistoricMissionPicture.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB4F0
        void HistoricMissionPicture::MenuView_HistoricMissionPicture_Prepare()
        {
            char* pcVar1;
            char local_14[16];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_14;
            MACRO_CALL(OS_Func::_sprintf)(
                local_14, "m%dpic.tgx", (DAT_GameCore::instance.missionNumber1to20 + -1) / 5 + 1);
            MACRO_CALL(UI::Helpers_Func::PrepareHistoryBook)();
            DAT_00eb0b20::instance = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(local_14);
            DAT_NumberOfStoredMenuStrings::instance = 0;
            pcVar1 = MACRO_CALL_MEMBER(
                Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                (DE::SHCDE::eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                    + DE::SHCDE::TEXT_TUTORIAL),
                0);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            pcVar1 = MACRO_CALL_MEMBER(
                Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                (DE::SHCDE::eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                    + DE::SHCDE::TEXT_TUTORIAL),
                1);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            ;
        }

    }
}
}
