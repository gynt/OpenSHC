#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00442F40
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -0xd;
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 2:
            case 3:
                if (*currentValue != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = *currentValue;
                return;
            case 4:
                if (*currentValue != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -0xd;
                return;
            case 5:
                if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1;
                    MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 6:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -0xd) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                    MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                break;
            case 7:
                *currentValue = 0xc;
            }
        }

    }
}
}
