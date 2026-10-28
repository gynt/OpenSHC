#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00491680
    MenuTextInputState* MenuTextInputState::Constructor_MenuTextInputState()
    {
        this->currentModalDialog = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_2 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_3 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_4 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_5 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_6 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->fileListMode = 3;
        this->loadGameSavedScrollOffset = 0;
        this->loadGameSavedSelection = 0;
        this->loadGameSavedSortMode = 2;
        this->saveGameSavedScrollOffset = 0;
        this->saveGameSavedSelection = 0;
        this->saveGameSavedSortMode = 2;
        this->mapListSavedScrollOffset = 0;
        this->mapListSavedSelection = 0;
        this->mapListSavedSortMode = 2;
        return this;
    }

}
}
