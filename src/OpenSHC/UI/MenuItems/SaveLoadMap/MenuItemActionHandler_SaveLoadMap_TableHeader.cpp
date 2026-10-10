#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492DE0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_TableHeader(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int sortMode;
            if (param_1 < 0) {
                param_1 = -1 - param_1;
                switch (param_1) {
                case 0:
                    DAT_MenuTextInputState::instance.field33_0x78 = 1;
                    break;
                case 1:
                    DAT_MenuTextInputState::instance.field33_0x78 = 0;
                    param_1 = 0;
                    break;
                case 2:
                    DAT_MenuTextInputState::instance.field33_0x78 = 3;
                    param_1 = 1;
                    break;
                case 3:
                    DAT_MenuTextInputState::instance.field33_0x78 = 2;
                    param_1 = 1;
                }
            }
            sortMode = DAT_MenuTextInputState::instance.field33_0x78;
            /*
              the original dispatches the two actions with a `sub eax, K; je` chain
              (0x492e3a), MSVC's sparse switch, and places the `case 1` body first
             */
            switch (param_1) {
            case 1:
                iVar2 = DAT_MenuTextInputState::instance.field32_0x74;
                /*
                  the original tests the mode once (0x492e4c) and writes the `== 2` pass
                  first, returning out of it at 0x492eca; the inner pass is a counted loop
                  whose zero-trip test is the `test eax, eax; jle` at 0x492e67, not the
                  guard Ghidra duplicated into the loop body
                 */
                if (sortMode == 2) {
                    do {
                        iVar4 = 0;
                        for (iVar3 = 0; iVar3 < iVar2 + -1; iVar3 = iVar3 + 1) {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if ((int)DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]
                                < (int)DAT_ResourceManager::instance.mapFileTimes[iVar1]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                                iVar2 = DAT_MenuTextInputState::instance.field32_0x74;
                            }
                        }
                    } while (iVar4 != 0);
                    DAT_MenuTextInputState::instance.field33_0x78 = 3;
                    DAT_MenuTextInputState::instance.field43_0xa0 = 0xffffffff;
                    return;
                }
                do {
                    iVar4 = 0;
                    for (iVar3 = 0; iVar3 < iVar2 + -1; iVar3 = iVar3 + 1) {
                        iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                        if ((int)DAT_ResourceManager::instance.mapFileTimes[iVar1] < (int)DAT_ResourceManager::instance
                                .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                            iVar4 = iVar4 + 1;
                            iVar2 = DAT_MenuTextInputState::instance.field32_0x74;
                        }
                    }
                } while (iVar4 != 0);
                DAT_MenuTextInputState::instance.field33_0x78 = 2;
                DAT_MenuTextInputState::instance.field43_0xa0 = 0xffffffff;
                break;
            case 0:
                if (sortMode == 0) {
                    for (iVar2 = 0; iVar2 < DAT_MenuTextInputState::instance.field32_0x74; iVar2 = iVar2 + 1) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar2 + -1]
                            = (DAT_MenuTextInputState::instance.field32_0x74 - iVar2) + -1;
                    }
                    DAT_MenuTextInputState::instance.field33_0x78 = 1;
                    DAT_MenuTextInputState::instance.field43_0xa0 = 0xffffffff;
                    return;
                }
                for (iVar2 = 0; iVar2 < DAT_MenuTextInputState::instance.field32_0x74; iVar2 = iVar2 + 1) {
                    DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar2 + -1] = iVar2;
                }
                DAT_MenuTextInputState::instance.field33_0x78 = 0;
                DAT_MenuTextInputState::instance.field43_0xa0 = 0xffffffff;
                break;
            }
        }

    }
}
}
