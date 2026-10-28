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
            if (param_1 < 0) {
                param_1 = -1 - param_1;
                switch (param_1) {
                case 0:
                    DAT_MenuTextInputState::instance.fileListSortMode = 1;
                    break;
                case 1:
                    DAT_MenuTextInputState::instance.fileListSortMode = 0;
                    param_1 = 0;
                    break;
                case 2:
                    DAT_MenuTextInputState::instance.fileListSortMode = 3;
                    param_1 = 1;
                    break;
                case 3:
                    DAT_MenuTextInputState::instance.fileListSortMode = 2;
                    param_1 = 1;
                }
            }
            if (param_1 == 0) {
                iVar2 = 0;
                if (DAT_MenuTextInputState::instance.fileListSortMode == 0) {
                    if (0 < DAT_MenuTextInputState::instance.fileListTotalCount) {
                        do {
                            DAT_MenuTextInputState::instance.mapIndexList[iVar2]
                                = (DAT_MenuTextInputState::instance.fileListTotalCount - iVar2) + -1;
                            iVar2 = iVar2 + 1;
                        } while (iVar2 < DAT_MenuTextInputState::instance.fileListTotalCount);
                    }
                    DAT_MenuTextInputState::instance.fileListSortMode = 1;
                    DAT_MenuTextInputState::instance.previewMinimapListIndex = 0xffffffff;
                    return;
                }
                if (0 < DAT_MenuTextInputState::instance.fileListTotalCount) {
                    do {
                        DAT_MenuTextInputState::instance.mapIndexList[iVar2] = iVar2;
                        iVar2 = iVar2 + 1;
                    } while (iVar2 < DAT_MenuTextInputState::instance.fileListTotalCount);
                }
                DAT_MenuTextInputState::instance.fileListSortMode = 0;
                DAT_MenuTextInputState::instance.previewMinimapListIndex = 0xffffffff;
            } else if (param_1 == 1) {
                iVar2 = DAT_MenuTextInputState::instance.fileListTotalCount;
                if (DAT_MenuTextInputState::instance.fileListSortMode != 2) {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar2 + -1 <= 0) break;
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.mapIndexList[iVar3];
                            if ((int)DAT_ResourceManager::instance.mapFileTimes[iVar1]
                                < (int)DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1]]) {
                                DAT_MenuTextInputState::instance.mapIndexList[iVar3]
                                    = DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1];
                                DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1] = iVar1;
                                iVar4 = iVar4 + 1;
                                iVar2 = DAT_MenuTextInputState::instance.fileListTotalCount;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar2 + -1);
                    } while (iVar4 != 0);
                    DAT_MenuTextInputState::instance.fileListSortMode = 2;
                    DAT_MenuTextInputState::instance.previewMinimapListIndex = 0xffffffff;
                    return;
                }
                do {
                    iVar4 = 0;
                    iVar3 = 0;
                    if (iVar2 + -1 <= 0) break;
                    do {
                        iVar1 = DAT_MenuTextInputState::instance.mapIndexList[iVar3];
                        if ((int)DAT_ResourceManager::instance
                                .mapFileTimes[DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1]]
                            < (int)DAT_ResourceManager::instance.mapFileTimes[iVar1]) {
                            DAT_MenuTextInputState::instance.mapIndexList[iVar3]
                                = DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1];
                            DAT_MenuTextInputState::instance.mapIndexList[iVar3 + 1] = iVar1;
                            iVar4 = iVar4 + 1;
                            iVar2 = DAT_MenuTextInputState::instance.fileListTotalCount;
                        }
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < iVar2 + -1);
                } while (iVar4 != 0);
                DAT_MenuTextInputState::instance.fileListSortMode = 3;
                DAT_MenuTextInputState::instance.previewMinimapListIndex = 0xffffffff;
            }
        }

    }
}
}
