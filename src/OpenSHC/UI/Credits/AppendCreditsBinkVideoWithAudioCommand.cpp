#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAB80
    void Credits::AppendCreditsBinkVideoWithAudioCommand(char* param_1, int param_2, int param_3, int param_4)
    {
        char cVar1;
        int iVar2;
        if (DAT_UnknownBinkCount::instance < 0x120) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0xd;
            iVar2 = (DAT_UnknownBinkCount::instance * 0x5c + 0xeb9ba4) - (int)param_1;
            do {
                cVar1 = *param_1;
                param_1[iVar2] = cVar1;
                param_1 = param_1 + 1;
            } while (cVar1 != '\0');
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkObjIndex = param_2;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].flagLoopCount
                = 1 - param_3;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].volume = param_4;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
