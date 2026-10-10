#include "../TextEditor.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0045EDF0
        void TextEditor::MenuItemActionHandler_TextEditor_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            int iVar3;
            uint uVar2;
            uVar2
                = DAT_TextEditorState::instance.topVisibleLineIndex - DAT_TextEditorState::instance.dialogContentHeight;
            if ((int)(((int)uVar2 < 1) - 1 & uVar2) / 0x14 <= 1) {
                iVar1 = 1;
            } else {
                iVar1 = (int)(((int)uVar2 < 1) - 1 & uVar2) / 0x14;
            }
            /*
              the jump table at 0x45ef6c sends every value outside 1..7 straight to the
              epilogue (0x45ef68), so `case 5` owns the scroll-up block rather than
              sharing it with a fall-through default, and the arms sit in the order
              1, 2/3, 4, 7, 5, 6
             */
            switch (param_2) {
            case 1:
                *minValue = 0;
                uVar2 = DAT_TextEditorState::instance.topVisibleLineIndex
                    - DAT_TextEditorState::instance.dialogContentHeight;
                *maxValue = (((int)uVar2 < 1) - 1 & uVar2);
                if ((int)(((int)uVar2 < 1) - 1 & uVar2) < 0) {
                    *maxValue = 0;
                }
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                return;
            case 2:
            case 3:
                DAT_TextEditorState::instance.helpContentScrollOffsetY = *currentValue;
                return;
            case 4:
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                uVar2 = DAT_TextEditorState::instance.topVisibleLineIndex
                    - DAT_TextEditorState::instance.dialogContentHeight;
                *maxValue = (((int)uVar2 < 1) - 1 & uVar2);
                return;
            case 7:
                *currentValue = DAT_TextEditorState::instance.dialogContentHeight + -0x14;
                return;
            case 5:
                if (iVar1 <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY - iVar1;
                    *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    return;
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                *currentValue = 0;
                return;
            case 6:
                iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                if (iVar3 < (int)((((int)uVar2 < 1) - 1 & uVar2) - iVar1)) {
                    iVar3 = iVar3 + iVar1;
                    if ((int)(((int)uVar2 < 1) - 1 & uVar2) < iVar3) {
                        iVar3 = (((int)uVar2 < 1) - 1 & uVar2);
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                        *currentValue = iVar3;
                        return;
                    }
                } else {
                    iVar3 = (((int)uVar2 < 1) - 1 & uVar2);
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                *currentValue = iVar3;
                return;
            }
        }

    }
}
}
