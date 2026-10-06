#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

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
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                    break;
                case 1:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                    param_1 = 0;
                    break;
                case 2:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                    param_1 = 1;
                    break;
                case 3:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                    param_1 = 1;
                }
            }
            if (!param_1) {
                iVar2 = 0;
                if (!DAT_MenuTextInputState::instance.fileListSortOrder) {
                    if (0 < DAT_MenuTextInputState::instance.fileListEntryCount) {
                        do {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar2 + -1]
                                = (DAT_MenuTextInputState::instance.fileListEntryCount - iVar2) + -1;
                            iVar2 = iVar2 + 1;
                        } while (iVar2 < DAT_MenuTextInputState::instance.fileListEntryCount);
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                    DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
                }
                if (0 < DAT_MenuTextInputState::instance.fileListEntryCount) {
                    do {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar2 + -1] = iVar2;
                        iVar2 = iVar2 + 1;
                    } while (iVar2 < DAT_MenuTextInputState::instance.fileListEntryCount);
                }
                DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
            } else if (param_1 == 1) {
                iVar2 = DAT_MenuTextInputState::instance.fileListEntryCount;
                if (DAT_MenuTextInputState::instance.fileListSortOrder != 2) {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar2 == 1 || iVar2 + -1 < 0) {
                            DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                            DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
                        }
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_ResourceManager::instance.mapFileTimes[iVar1] < (int)DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                                iVar2 = DAT_MenuTextInputState::instance.fileListEntryCount;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar2 + -1);
                    } while (iVar4);
                    DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                    DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
                }
                do {
                    iVar4 = 0;
                    iVar3 = 0;
                    if (iVar2 == 1 || iVar2 + -1 < 0) {
                        DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                        DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
                    }
                    do {
                        iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                        if ((int)DAT_ResourceManager::instance
                                .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]
                            < DAT_ResourceManager::instance.mapFileTimes[iVar1]) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                            iVar4 = iVar4 + 1;
                            iVar2 = DAT_MenuTextInputState::instance.fileListEntryCount;
                        }
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < iVar2 + -1);
                } while (iVar4);
                DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                DAT_MenuTextInputState::instance.previewedListIndex = 0xffffffff;
            }
        }

    }
}
}
