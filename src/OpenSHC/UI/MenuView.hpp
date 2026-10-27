/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuView.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::cdeclVoidFunc;

#pragma pack(push, 1)

    // SIZE: 0x00000018
    class MenuView {
    public:
        dword unknown_0x0; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        MenuViewTypeInt menuID; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        MenuView* nextMenuViewPtr; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        cdeclVoidFunc* prepare; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        cdeclVoidFunc* doInitial; // 0x00000010 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        cdeclVoidFunc* doEveryFrame; // 0x00000014 length: 4

    private:
        MenuView(MenuView const&);
        void operator=(MenuView const&);

    public:
        MenuView() {};
        ~MenuView() {};

        // Constructor
        /**
         * MenuView constructor: stores id and prepare/doInitial/doEveryFrame callbacks and pushes the view onto the
         * global DAT_MenuViewStackTop linked list; returns this.
         */
        MenuView* Constructor_MenuView(
            MenuViewType menuID, cdeclVoidFunc* prepareMenuView, cdeclVoidFunc* doInitial, cdeclVoidFunc* doEveryFrame);

        /**
         * Reduced MenuView constructor: sets the id of the static MenuView_00b974bc and links it onto the menu view
         * list (ignores this, returns the static object).
         */
        MenuView* Constructor_MenuView_Reduced(MenuViewType menuType);
    };

    static_assert_cpp98_obj(sizeof(MenuView) == 24, MenuView);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
