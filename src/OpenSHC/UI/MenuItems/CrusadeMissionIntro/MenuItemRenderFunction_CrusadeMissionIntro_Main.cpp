#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::TrailType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8BB0
        void CrusadeMissionIntro::MenuItemRenderFunction_CrusadeMissionIntro_Main(int param_1, ...)
        {
            /*
              the original compares the trail's progress against its own length inside each
              arm and shares only the `jl` (0x4d8be7); a trail type outside the three never
              reaches it, so the flag stays clear
             */
            bool trailComplete = false;
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                trailComplete = 0x14 <= (int)DAT_GameCore::instance.extremeTrailProgress;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                trailComplete = 0x1e <= (int)DAT_GameCore::instance.warchestTrailProgress;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                trailComplete = 0x32 <= (int)DAT_GameCore::instance.skirmishTrailProgress;
            }
            if ((param_1 == 10) && (trailComplete)) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }
    }
}
}
