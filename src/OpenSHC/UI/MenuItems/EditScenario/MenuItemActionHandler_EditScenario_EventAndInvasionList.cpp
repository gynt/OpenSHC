#include "../EditScenario.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B8B10
        void EditScenario::MenuItemActionHandler_EditScenario_EventAndInvasionList(int param_1, ...)
        {
            int iVar1;
            char local_10[12];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_10;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                iVar1 = DAT_MapPropertiesState::instance.field47_0x1355c + param_1;
                if (iVar1 < DAT_MapPropertiesState::instance.eventsCount) {
                    DAT_MapPropertiesState::instance.field48_0x13560 = param_1;
                    DAT_MapPropertiesState::instance.field50_0x13568
                        = DAT_MapPropertiesState::instance.scenarioEvents[iVar1].header.tl_type;
                    DAT_MapPropertiesState::instance.currentEventID = iVar1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xb);
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_10, "%d",
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.year);
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray,
                        DAT_UserTextHandlerState::ptr)(local_10);
                    /*
                      the original dispatches with a `sub eax, K; je` chain (0x4b8ba3),
                      MSVC's sparse switch, and pushes the modal id inside each arm
                      (0x4b8bae, 0x4b8bd0) before the one shared `call activateModalDialog`
                     */
                    switch (DAT_MapPropertiesState::instance.field50_0x13568) {
                    case 3:
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_EVENT, FALSE);
                        break;
                    case 1:
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xb);
                        DAT_MapPropertiesState::instance.field_0x1356c = 0;
                        DAT_MapPropertiesState::instance.offset = 0;
                        DAT_MapPropertiesState::instance.indexStored = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_INVASION, FALSE);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

    }
}
}
