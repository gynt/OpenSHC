#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA9F0
    void Credits::AppendCreditsShowImageCommand(
        int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, undefined4 param_7, int param_8)
    {
        if (((DAT_UnknownBinkCount::instance < 0x120) && (-1 < param_2)) && (param_1 == 0x29)) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x29;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_2;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field17_0x38 = 0;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_3;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = param_4;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field13_0x28 = param_8;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field4_0x10 = param_5;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field5_0x14 = param_6;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
