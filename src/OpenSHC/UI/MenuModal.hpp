/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModal.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuModalRenderFunction;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuModalTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00000028
    class MenuModal {
    public:
        MenuModalTypeInt menuModalID; // 0x00000000 length: 4
        int x; // 0x00000004 length: 4
        int y; // 0x00000008 length: 4
        int width; // 0x0000000C length: 4
        int height; // 0x00000010 length: 4
        // [050 0x0059B120] bit set, not a border style: renderMenuModal tests bits 1 (colour fill), 2 (title
        // strip), 8 (dim), 0x10/0x80/0x100 (rounded boxes), 0x20/0x200 (tiled frame), 0x400 (fade);
        // activateModalDialog rounds size to 24 when &0x220 512 is the nice red double border.
        int styleFlags; // 0x00000014 length: 4
        // [050 0x0059B120] init code stores either a raw 16-bit colour (COL_WHITE.shortValue) or a small index (6);
        // renderMenuModal uses it raw for style bit 1 and maps 1..9 to COL_* for bits 0x80/0x100
        int colourValueOrIndex; // 0x00000018 length: 4
        MenuModalRenderFunction* menuModalRenderFunction; // 0x0000001C length: 4
        Menu* pointerToMenu; // 0x00000020 length: 4
        MenuModal* pointerToNextModalMenu; // 0x00000024 length: 4

    private:
        MenuModal(MenuModal const&);
        void operator=(MenuModal const&);

    public:
        MenuModal() {};
        ~MenuModal() {};

        // Constructor
        /**
         * MenuModal constructor: stores id, position, size, border style, background colour index, render function
         * and attached Menu, and pushes the modal onto the global singly-linked modal list
         * (DAT_ModalMenuArrayPointerToStackTop).
         */
        MenuModal* Constructor_MenuModal(MenuModalType menuModalId, int xPos, int yPos, int width, int height,
            int borderStyle, int backgroundColourIndex, MenuModalRenderFunction* renderFunctionPtr, Menu* menuPtr);
    };

    static_assert_cpp98_obj(sizeof(MenuModal) == 40, MenuModal);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
