#include "../UnusedExtremeAd.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/g_extremeAdFrameCounter.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandCount.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed3140.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004E1AA0
        void UnusedExtremeAd::MenuView_UnusedExtremeAd_DoEveryFrame()
        {
            int iVar1;
            iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1 != 0) {
                if (DAT_MouseState::instance.rightClickStop != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::StopCreditsPlaybackAndSounds)();
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::FindCampaignMapHotspotAtMouse)();
                    if (iVar1 == 1) {
                        MACRO_CALL(OpenSHC::UI::Credits_Func::EndCreditsSegmentAndAdvanceToNext)();
                        g_extremeAdFrameCounter::instance = g_extremeAdFrameCounter::instance + 1;
                        if (g_extremeAdFrameCounter::instance == 3) {
                            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                        }
                    }
                }
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if (DAT_CreditsScriptCommandIndex::instance < DAT_CreditsScriptCommandCount::instance) {
                    MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
                }
                INT_00ed3140::instance = INT_00ed3140::instance + 1;
                if (DAT_CreditsScriptCommandCount::instance <= DAT_CreditsScriptCommandIndex::instance) {
                    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                }
            }
        }

    }
}
}
