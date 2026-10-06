#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042B7B0
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            if ((DAT_00b960dc::instance) && (param_2 != 1)) {}
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -8;
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 2:
            case 3:
                iVar1 = *currentValue;
                if ((iVar1 != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset)
                    && (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar1,
                        DAT_GameSynchronyState::instance.isHost != FALSE)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_MAP_SELECTION);
                }
                break;
            case 4:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -8;
                if ((*currentValue != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset)
                    && (*currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset,
                        DAT_GameSynchronyState::instance.isHost != FALSE)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_MAP_SELECTION);
                }
                break;
            case 5:
                if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1;
                LAB_0042b8a4:
                    if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                goto LAB_0042b8b9;
            case 6:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -8) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                    goto LAB_0042b8a4;
                }
            LAB_0042b8b9:
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                break;
            case 7:
                *currentValue = 6;
            }
        }

    }
}
}
