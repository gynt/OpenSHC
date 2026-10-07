#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAC30
    void Credits::AppendCreditsTextCommand(
        int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
    {
        CreditsRelatedStructure2* pCVar1;
        if (((DAT_UnknownBinkCount::instance < 0x120) && (-1 < param_2))
            && (param_2 < DAT_NumberOfStoredMenuStrings::instance)) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = param_1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_2;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field6_0x18 = param_3;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_5;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = param_6;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field4_0x10 = param_7;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field15_0x30 = param_8;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field16_0x34 = param_4;
            if (param_1 == 0xf) {
                pCVar1 = DAT_ARRAY_00eb9b68::instance + DAT_UnknownBinkCount::instance;
                DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
                pCVar1->field_0x1c = 1;
                return;
            }
            if (param_1 == 0x10) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c
                    = 2;
            }
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
