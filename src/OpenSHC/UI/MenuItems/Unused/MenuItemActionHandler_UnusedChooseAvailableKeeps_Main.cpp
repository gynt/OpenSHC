#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00430050
        void Unused::MenuItemActionHandler_UnusedChooseAvailableKeeps_Main(int param_1, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                switch (param_1) {
                case -5:
                case -4:
                case -3:
                case -2:
                case -1:
                    // GameCore + param_1 * -4 + 0x1534 with param_1 in -5..-1 is
                    // mapU2MiddleBytes (0x1538, 5 dwords), the same five flags case 0xb sums
                    DAT_GameCore::instance.mapU2MiddleBytes[-param_1 - 1]
                        = DAT_GameCore::instance.mapU2MiddleBytes[-param_1 - 1] ^ 1;
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 0xb:
                    if (DAT_GameCore::instance.mapU2MiddleBytes[4] + DAT_GameCore::instance.mapU2MiddleBytes[3]
                            + DAT_GameCore::instance.mapU2MiddleBytes[2] + DAT_GameCore::instance.mapU2MiddleBytes[1]
                            + DAT_GameCore::instance.mapU2MiddleBytes[0]
                        != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                        DAT_GameCore::instance.mapLoadedForEditor = 1;
                    }
                    break;
                }
            }
        }

    }
}
}
