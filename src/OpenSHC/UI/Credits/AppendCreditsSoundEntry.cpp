#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA7A0
    void Credits::AppendCreditsSoundEntry(SHC_SoundStreamInt param_1, int param_2)
    {
        if (DAT_UnknownBinkCount::instance < 0x120) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x11;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_2;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
