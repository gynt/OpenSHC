#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6A20
    void MenuHandlerState::initializeUI(
        MenuIDMenuElementAddressPair* menuIDMenuElementAddressPair, UC* ucPtr, char* ptrStrongholdUCString)
    {
        MenuViewTypeInt _menuID;
        /*
          end of array sentinel is menuID of -1
         */
        _menuID = menuIDMenuElementAddressPair->menuID;
        this->ucPtrStruct.ucArrayPointer = ucPtr;
        this->pointerToMenuIDMenuElementAddressMap = menuIDMenuElementAddressPair;
        while (_menuID != UI::Enums::MVT_MENUVIEWID_MENU_PAIR_ENDMARKER) {
            /*
              param_1[1] is the menu pointer
             */
MACRO_CALL_MEMBER(UI::Menu_Func::loadMenuElements, menuIDMenuElementAddressPair)()->menuAddress,0);
/*
  next element
 */
menuIDMenuElementAddressPair = menuIDMenuElementAddressPair + 1;
_menuID = menuIDMenuElementAddressPair->menuID;
        }
        MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::prepareButtonAndAlphaSurface,
            AlphaAndButtonSurfaceObj::ptr)();
        MACRO_CALL_MEMBER(
            UI::MenuModalComposition_Func::loadAllMenuElementsOfMenuModals, DAT_MenuModalComposition1::ptr)();
    }

}
}
