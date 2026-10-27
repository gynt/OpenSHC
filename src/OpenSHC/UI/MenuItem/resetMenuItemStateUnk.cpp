#include "OpenSHC/UI/MenuItem.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuItemTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::UI::Enums::MenuItemTypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4C30
    void MenuItem::resetMenuItemState()
    {
        this->hovering = 0;
        this->clicked = 0;
        this->secondItemTypeData.buttonState.lastRepeatTimeOrMinValue = 0;
        this->secondItemTypeData.buttonState.clickTimeOrMaxValue = 0;
        this->secondItemTypeData.buttonState.repeatCountOrValue = 0;
        MenuItemTypeInt const itemType = this->menuItemType & Enums::MIT_TYPE_ID_MASK;
        if (itemType == OpenSHC::UI::Enums::MIT_HORIZONTAL_SLIDER || itemType == OpenSHC::UI::Enums::MIT_VERTICAL_SCROLLBAR) {
            this->secondItemTypeData.buttonState.pictureOrDragOffset = -1000;
        }
    }

}
}
