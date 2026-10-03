#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00b960bc.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/INT_00b960b8.hpp"
#include "OpenSHC/Globals/INT_00b960c0.hpp"
#include "OpenSHC/Globals/INT_00b960c4.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C190
    void Helpers::ClearSiegeInformationArray2()
    {
        int (*paaiVar1)[7][3];
        paaiVar1 = DAT_SiegeInformationArray_2::instance;
        INT_00b960b8::instance = 0;
        DAT_00b960bc::instance = 0;
        INT_00b960c0::instance = 0;
        INT_00b960c4::instance = 0;
        do {
            (*paaiVar1)[0][0] = 0;
            (*paaiVar1)[0][1] = 0;
            (*paaiVar1)[0][2] = 0;
            (*paaiVar1)[1][0] = 0;
            (*paaiVar1)[1][1] = 0;
            (*paaiVar1)[1][2] = 0;
            (*paaiVar1)[2][0] = 0;
            (*paaiVar1)[2][1] = 0;
            (*paaiVar1)[2][2] = 0;
            (*paaiVar1)[3][0] = 0;
            (*paaiVar1)[3][1] = 0;
            paaiVar1 = paaiVar1 + 1;
        } while ((int)paaiVar1 < 0xb95ab8);
    }

}
}
