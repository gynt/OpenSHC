#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/INT_00b960b8.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0042C540
    void Helpers::SomeSiegeRelatedCopying(int param_1)
    {
        DAT_SiegeInformationArray::instance[0] = DAT_SiegeInformationArray_2::instance[param_1][0][0];
        DAT_SiegeInformationArray::instance[1] = DAT_SiegeInformationArray_2::instance[param_1][0][1];
        DAT_SiegeInformationArray::instance[2] = DAT_SiegeInformationArray_2::instance[param_1][0][2];
        DAT_SiegeInformationArray::instance[3] = DAT_SiegeInformationArray_2::instance[param_1][1][0];
        DAT_SiegeInformationArray::instance[4] = DAT_SiegeInformationArray_2::instance[param_1][1][1];
        DAT_SiegeInformationArray::instance[5] = DAT_SiegeInformationArray_2::instance[param_1][1][2];
        DAT_SiegeInformationArray::instance[6] = DAT_SiegeInformationArray_2::instance[param_1][2][0];
        DAT_SiegeInformationArray::instance[7] = DAT_SiegeInformationArray_2::instance[param_1][2][1];
        DAT_SiegeInformationArray::instance[8] = DAT_SiegeInformationArray_2::instance[param_1][2][2];
        DAT_SiegeInformationArray::instance[9] = DAT_SiegeInformationArray_2::instance[param_1][3][0];
        DAT_SiegeInformationArray::instance[10] = DAT_SiegeInformationArray_2::instance[param_1][3][1];
        DAT_SiegeInformationArray::instance[0xb] = DAT_SiegeInformationArray_2::instance[param_1][3][2];
        DAT_SiegeInformationArray::instance[0xc] = DAT_SiegeInformationArray_2::instance[param_1][4][0];
        DAT_SiegeInformationArray::instance[0xd] = DAT_SiegeInformationArray_2::instance[param_1][4][1];
        DAT_SiegeInformationArray::instance[0xe] = DAT_SiegeInformationArray_2::instance[param_1][4][2];
        DAT_SiegeInformationArray::instance[0xf] = DAT_SiegeInformationArray_2::instance[param_1][5][0];
        DAT_SiegeInformationArray::instance[0x10] = DAT_SiegeInformationArray_2::instance[param_1][5][1];
        DAT_SiegeInformationArray::instance[0x11] = DAT_SiegeInformationArray_2::instance[param_1][5][2];
        DAT_SiegeInformationArray::instance[0x12] = DAT_SiegeInformationArray_2::instance[param_1][6][0];
        DAT_SiegeInformationArray::instance[0x13] = DAT_SiegeInformationArray_2::instance[param_1][6][1];
        DAT_SiegeInformationArray::instance[0x14] = DAT_SiegeInformationArray_2::instance[param_1][6][2];
        DAT_SiegeRemainingPoints::instance = (INT_00b960b8::ptr)[param_1];
    }

}
}
