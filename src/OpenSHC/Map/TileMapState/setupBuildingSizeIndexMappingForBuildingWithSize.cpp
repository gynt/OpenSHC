#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9590
    void TileMapState::setupBuildingSizeIndexMappingForBuildingWithSize(int buildingSize)
    {
        int iVar1;
        int _x;
        int iVar2;
        int* _ptrY2;
        int _y;
        int iVar3;
        int iVar4;
        int* _ptrY;
        int iVar5;
        int local_14;
        int local_10;
        int local_c;
        iVar1 = buildingSize;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            4056, '\0', (void*)((int)(DAT_BuildingSizeIndexMapping::instance + buildingSize)));
        if (1 < buildingSize) {
            _y = 0;
            if (0 < buildingSize) {
                _ptrY = DAT_BuildingSizeIndexMapping::instance[buildingSize][0] + 1;
                do {
                    _x = 0;
                    _ptrY2 = _ptrY;
                    do {
                        (*(int (*)[6])(_ptrY2 + -1))[0] = _x;
                        *_ptrY2 = _y;
                        _x = _x + 1;
                        _ptrY2 = _ptrY2 + 6;
                    } while (_x < buildingSize);
                    _y = _y + 1;
                    _ptrY = _ptrY + buildingSize * 6;
                } while (_y < buildingSize);
            }
            iVar3 = buildingSize * buildingSize + -1;
            _x = 0;
            iVar5 = buildingSize * 2 + -1;
            iVar2 = 0;
            local_14 = 0;
            _y = 1;
            if (0 < iVar5) {
                iVar4 = iVar3;
                do {
                    iVar5 = 0;
                    if (0 < _y) {
                        iVar2 = (iVar2 + 169) * buildingSize;
                        do {
                            DAT_BuildingSizeIndexMapping::instance[0][iVar2 + _x][2] = iVar4;
                            iVar4 = iVar4 + -1;
                            if (iVar5 < _y + -1) {
                                _x = _x + -1;
                                iVar2 = iVar2 + buildingSize;
                            }
                            iVar5 = iVar5 + 1;
                        } while (iVar5 < _y);
                    }
                    _x = buildingSize + -1;
                    if (local_14 < _x) {
                        _y = _y + 1;
                        _x = local_14 + 1;
                        iVar2 = 0;
                    } else {
                        _y = _y + -1;
                        iVar2 = (1 - (buildingSize + -1)) + local_14;
                    }
                    local_14 = local_14 + 1;
                    iVar5 = buildingSize * 2 + -1;
                } while (local_14 < iVar5);
            }
            iVar2 = 0;
            _y = buildingSize + -1;
            local_14 = 0;
            _x = 1;
            if (0 < iVar5) {
                local_c = buildingSize * 2 + -3;
                local_10 = iVar3;
                do {
                    iVar5 = 0;
                    if (0 < _x) {
                        iVar2 = (iVar2 + 0xa9) * buildingSize;
                        do {
                            DAT_BuildingSizeIndexMapping::instance[0][iVar2 + _y][3] = local_10;
                            local_10 = local_10 + -1;
                            if (iVar5 < _x + -1) {
                                _y = _y + -1;
                                iVar2 = iVar2 - buildingSize;
                            }
                            iVar5 = iVar5 + 1;
                        } while (iVar5 < _x);
                    }
                    _y = buildingSize + -1;
                    if (local_14 < _y) {
                        _x = _x + 1;
                        iVar2 = local_14 + 1;
                    } else {
                        _x = _x + -1;
                        iVar2 = _y;
                        _y = local_c;
                    }
                    local_c = local_c + -1;
                    local_14 = local_14 + 1;
                    iVar5 = buildingSize * 2 + -1;
                } while (local_14 < iVar5);
            }
            _x = buildingSize + -1;
            local_14 = 0;
            _y = 1;
            if (0 < iVar5) {
                local_c = buildingSize + -2;
                iVar2 = _x;
                local_10 = iVar3;
                do {
                    iVar5 = 0;
                    if (0 < _y) {
                        _x = (_x + 0xa9) * buildingSize;
                        do {
                            DAT_BuildingSizeIndexMapping::instance[0][_x + iVar2][4] = local_10;
                            local_10 = local_10 + -1;
                            if (iVar5 < _y + -1) {
                                iVar2 = iVar2 + 1;
                                _x = _x - buildingSize;
                            }
                            iVar5 = iVar5 + 1;
                        } while (iVar5 < _y);
                    }
                    _x = buildingSize + -1;
                    if (local_14 < _x) {
                        _y = _y + 1;
                        iVar2 = local_c;
                    } else {
                        _y = _y + -1;
                        iVar2 = 0;
                        _x = local_c + _x;
                    }
                    local_c = local_c + -1;
                    local_14 = local_14 + 1;
                    iVar5 = buildingSize * 2 + -1;
                } while (local_14 < iVar5);
            }
            iVar2 = buildingSize + -1;
            _x = 0;
            local_14 = 0;
            _y = 1;
            if (0 < iVar5) {
                buildingSize = buildingSize + -2;
                iVar5 = 1 - iVar2;
                local_10 = iVar3;
                do {
                    iVar3 = 0;
                    if (0 < _y) {
                        iVar2 = (iVar2 + 0xa9) * iVar1;
                        do {
                            DAT_BuildingSizeIndexMapping::instance[0][iVar2 + _x][5] = local_10;
                            local_10 = local_10 + -1;
                            if (iVar3 < _y + -1) {
                                _x = _x + 1;
                                iVar2 = iVar2 + iVar1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < _y);
                    }
                    if (local_14 < iVar1 + -1) {
                        _y = _y + 1;
                        _x = 0;
                        iVar2 = buildingSize;
                    } else {
                        _y = _y + -1;
                        _x = iVar5 + local_14;
                        iVar2 = 0;
                    }
                    buildingSize = buildingSize + -1;
                    local_14 = local_14 + 1;
                } while (local_14 < iVar1 * 2 + -1);
            }
        }
    }

}
}
