#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/g_statusMenuArmyPage.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043FC80
            void MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton()
            {
                g_statusMenuArmyPage::instance += 1;
                if ((int)g_statusMenuArmyPage::instance > 2) {
                    g_statusMenuArmyPage::instance = 0;
                }
            }

        }
    }
}
}
