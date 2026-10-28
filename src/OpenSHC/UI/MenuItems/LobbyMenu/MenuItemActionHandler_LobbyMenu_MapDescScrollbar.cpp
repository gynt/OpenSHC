#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/g_mapDescriptionTextHeight.hpp"
#include "OpenSHC/Globals/DAT_MenuFadeState.hpp"
#include "OpenSHC/Globals/mapDescScrollOffset.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00428980
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            if ((((DAT_MenuFadeState::instance == 0)
                     && (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE))
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                        != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                && (DAT_MenuModalComposition1::instance.activeModalDialogID
                    != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {
                iVar1 = 0;
                if (param_1 == 0) {
                    iVar1 = 0xcc;
                } else if (param_1 == 1) {
                    iVar1 = 0x6e;
                }
                switch (param_2) {
                case 1:
                    *minValue = -0x13;
                    *maxValue = g_mapDescriptionTextHeight::instance - iVar1;
                    *currentValue = 0;
                    return;
                case 2:
                case 3:
                    mapDescScrollOffset::instance = *currentValue;
                    return;
                case 4:
                    *minValue = -0x13;
                    *maxValue = g_mapDescriptionTextHeight::instance - iVar1;
                    *currentValue = mapDescScrollOffset::instance;
                    return;
                case 7:
                    *currentValue = iVar1 + -0xe;
                }
            }
        }

    }
}
}
