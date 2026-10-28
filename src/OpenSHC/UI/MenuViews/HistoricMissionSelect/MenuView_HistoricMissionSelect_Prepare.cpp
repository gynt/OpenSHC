#include "../HistoricMissionSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/g_historicMissionSelectPage.hpp"
#include "OpenSHC/Globals/g_historicMissionSelectFirstMission.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00426830
        void HistoricMissionSelect::MenuView_HistoricMissionSelect_Prepare()
        {
            DAT_GameCore::instance.inGameViewActive_0xa4 = FALSE;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.section1066 = 0;
            DAT_MenuTextInputState::instance.lastListClickTime = 0;
            DAT_MenuTextInputState::instance.lastClickedListIndex = 0xffffffff;
            if (DAT_GameCore::instance.missionNumber < 6) {
                g_historicMissionSelectPage::instance = 0;
                g_historicMissionSelectFirstMission::instance = 1;
                return;
            }
            if (DAT_GameCore::instance.missionNumber < 0xb) {
                g_historicMissionSelectPage::instance = 1;
                g_historicMissionSelectFirstMission::instance = 6;
                return;
            }
            g_historicMissionSelectPage::instance = (0xf < DAT_GameCore::instance.missionNumber) + 2;
            g_historicMissionSelectFirstMission::instance = g_historicMissionSelectPage::instance * 5 + 1;
        }

    }
}
}
