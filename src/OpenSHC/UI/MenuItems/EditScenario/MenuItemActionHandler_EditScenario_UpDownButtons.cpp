#include "../EditScenario.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9020
        void EditScenario::MenuItemActionHandler_EditScenario_UpDownButtons(int param_1, ...)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                if (param_1 == -2) {
                    if (DAT_MapPropertiesState::instance.eventListScrollOffset
                        < DAT_MapPropertiesState::instance.eventsCount + -0x14) {
                        DAT_MapPropertiesState::instance.eventListScrollOffset
                            = DAT_MapPropertiesState::instance.eventListScrollOffset + 1;
                    }
                } else if ((param_1 == -1) && (0 < DAT_MapPropertiesState::instance.eventListScrollOffset)) {
                    DAT_MapPropertiesState::instance.eventListScrollOffset
                        = DAT_MapPropertiesState::instance.eventListScrollOffset + -1;
                }
            }
        }

    }
}
}
