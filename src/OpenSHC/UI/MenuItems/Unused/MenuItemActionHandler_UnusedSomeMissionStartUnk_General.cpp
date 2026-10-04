#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00427080
        void Unused::MenuItemActionHandler_UnusedSomeMissionStartUnk_General(int param_1, ...)
        {
            if ((DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
                if (param_1 == 0xd) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                    DAT_GameCore::instance.section1066 = 1;
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xe7;
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMissionMapAndSetLord,
                        DAT_MapPropertiesState::ptr)(DAT_GameCore::instance.missionNumber1to20);
                    MACRO_CALL_MEMBER(
                        UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                } else if (param_1 == 0xe) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_MAIN_MENU, 0);
                }
            }
        }

    }
}
}
