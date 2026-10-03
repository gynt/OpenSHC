#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAE90
    void Credits::InsertElementIntoArrayAt_ec0348_2(
        int param_1, int xSpace, int param_3, int param_4, int ySpace, int someX, int param_7, int someY, int param_9)
    {
        int _index;
        CreditsRelatedStructure* pCVar1;
        if (param_1 == 2) {
            _index = 0;
            pCVar1 = DAT_ARRAY_00ec0348::instance;
            while (pCVar1->isValid != 0) {
                pCVar1 = pCVar1 + 1;
                _index = _index + 1;
                if (0xec0827 < (int)pCVar1) {
                    return;
                }
            }
            if (_index != -1) {
                DAT_ARRAY_00ec0348::instance[_index].xSpace = xSpace;
                DAT_ARRAY_00ec0348::instance[_index].flag = 0;
                DAT_ARRAY_00ec0348::instance[_index].field8_0x20 = param_3;
                DAT_ARRAY_00ec0348::instance[_index].ySpace = ySpace;
                DAT_ARRAY_00ec0348::instance[_index].someX = someX;
                DAT_ARRAY_00ec0348::instance[_index].someY = someY;
                DAT_ARRAY_00ec0348::instance[_index].field9_0x24 = param_9;
                DAT_ARRAY_00ec0348::instance[_index].field10_0x28 = param_4;
                DAT_ARRAY_00ec0348::instance[_index].isValid = 2;
                DAT_ARRAY_00ec0348::instance[_index].field6_0x18 = param_7;
                DAT_ARRAY_00ec0348::instance[_index].field7_0x1c = 7;
                if (param_7 == 1) {
                    DAT_ARRAY_00ec0348::instance[_index].flag = 0x41f80000;
                    return;
                }
                if (param_7 == 2) {
                    DAT_ARRAY_00ec0348::instance[_index].flag = 0x3f800000;
                }
            }
        }
        return;
    }

}
}
