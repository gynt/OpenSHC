#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed27f0.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2be0.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D9290
    void Skirmish::Skirmish_SortAIOpponentOrder(int reverseOrder)
    {
        int iVar1;
        int iVar2;
        int iVar3;
        uint* puVar4;
        int iVar5;
        uint* puVar6;
        uint visitedBitMap[251];
        MACRO_CALL(OpenSHC::OS_Func::_memset)(visitedBitMap + 1, 0, 1000);
        iVar2 = DAT_00eb9b60::instance;
        iVar5 = 0;
        /*
          sort by score
         */
        if (0 < DAT_00eb9b60::instance) {
            do {
                iVar3 = -1;
                iVar1 = 0;
                do {
                    if ((visitedBitMap[iVar1 + 1] == 0)
                        && ((iVar3 == -1 || (visitedBitMap[0] < (uint)INT_ARRAY_00ed2be0::instance[iVar1])))) {
                        visitedBitMap[0] = INT_ARRAY_00ed2be0::instance[iVar1];
                        iVar3 = iVar1;
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < iVar2);
                if (iVar3 < 0) {
                    iVar3 = 0;
                }
                INT_ARRAY_00eb96d8::instance[iVar5] = INT_ARRAY_00ed27f0::instance[iVar3];
                iVar5 = iVar5 + 1;
                visitedBitMap[iVar3 + 1] = 1;
            } while (iVar5 < iVar2);
        }
        /*
          bubble sort
         */
        if (((DAT_MissionDefinedData::instance.sortColumn == 2) && (1 < iVar2)) && (DAT_00ed3124::instance != 1)) {
            iVar5 = 0;
            while (true) {
                iVar1 = 0;
                iVar3 = 1;
                if (iVar2 < 2)
                    break;
                do {
                    iVar2 = MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                        DAT_SkMasters2DataArray::instance[*(int*)(DAT_ArrayOfStoredMenuStrings::instance[0x20]
                                                              + iVar3 * 4 + 0x3fc)]
                            .mapName,
                        (char const*)((
                            int)(DAT_SkMasters2DataArray::instance[INT_ARRAY_00eb96d8::instance[iVar3]].mapName)));
                    if (0 < iVar2) {
                        iVar2 = INT_ARRAY_00eb96d8::instance[iVar3];
                        INT_ARRAY_00eb96d8::instance[iVar3]
                            = *(int*)(DAT_ArrayOfStoredMenuStrings::instance[0x20] + iVar3 * 4 + 0x3fc);
                        *(int*)(DAT_ArrayOfStoredMenuStrings::instance[0x20] + iVar3 * 4 + 0x3fc) = iVar2;
                        iVar1 = iVar1 + 1;
                    }
                    iVar3 = iVar3 + 1;
                } while (iVar3 < DAT_00eb9b60::instance);
                iVar2 = DAT_00eb9b60::instance;
                if ((iVar1 == 0) || (iVar5 = iVar5 + 1, 0x9c3 < iVar5))
                    break;
            }
        }
        /*
          reverse order
         */
        if (reverseOrder == 0) {
            puVar4 = visitedBitMap;
            iVar5 = 0;
            puVar6 = (uint*)INT_ARRAY_00eb96d8::instance;
            for (iVar3 = 0xfa; puVar4 = (uint*)((int)puVar4 + 4), iVar3 != 0; iVar3 = iVar3 + -1) {
                *puVar4 = *puVar6;
                puVar6 = puVar6 + 1;
            }
            if (0 < iVar2) {
                puVar4 = visitedBitMap + iVar2;
                do {
                    INT_ARRAY_00eb96d8::instance[iVar5] = *puVar4;
                    iVar5 = iVar5 + 1;
                    puVar4 = puVar4 + -1;
                } while (iVar5 < iVar2);
            }
        }
    }

}
}
