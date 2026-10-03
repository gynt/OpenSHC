#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAA80
    void Credits::AppendCreditsBinkVideoCommand(
        undefined4 param_1, char* param_2, int param_3, int param_4, int param_5, SoundFlagsAndLoopCount param_6)
    {
        char cVar1;
        int iVar2;
        if (DAT_UnknownBinkCount::instance < 0x120) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0xc;
            iVar2 = (DAT_UnknownBinkCount::instance * 0x5c + 0xeb9ba4) - (int)param_2;
            do {
                cVar1 = *param_2;
                param_2[iVar2] = cVar1;
                param_2 = param_2 + 1;
            } while (cVar1 != '\0');
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_3;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = param_4;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkObjIndex = param_5;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].flagLoopCount = param_6;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field13_0x28 = 0;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
