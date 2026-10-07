#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00491680
    MenuTextInputState* MenuTextInputState::Constructor_MenuTextInputState()
    {
        this->currentModalDialog = UI::Enums::MMT_NO_MENU;
        this->modalDialog_2 = UI::Enums::MMT_NO_MENU;
        this->modalDialog_3 = UI::Enums::MMT_NO_MENU;
        this->modalDialog_4 = UI::Enums::MMT_NO_MENU;
        this->modalDialog_5 = UI::Enums::MMT_NO_MENU;
        this->modalDialog_6 = UI::Enums::MMT_NO_MENU;
        this->fileListContext = 3;
        this->savedListOffset1 = 0;
        this->savedListSelection1 = 0;
        this->savedListSortOrder1 = 2;
        this->savedListOffset2 = 0;
        this->savedListSelection2 = 0;
        this->savedListSortOrder2 = 2;
        this->savedListOffset3 = 0;
        this->savedListSelection3 = 0;
        this->savedListSortOrder3 = 2;
        return this;
    }

}
}
