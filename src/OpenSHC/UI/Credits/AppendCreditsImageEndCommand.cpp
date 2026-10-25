#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA9A0
    void Credits::AppendCreditsImageEndCommand(int param_1, int param_2)
    {
        if (((DAT_UnknownBinkCount::instance < 0x120) && (-1 < param_2)) && ((param_1 == 7 || (param_1 == 0x2a)))) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = param_1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_2;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
