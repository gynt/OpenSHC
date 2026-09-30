#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00523E30
    void Version::UpgradeMapTribesStateVersionTo_Unknown1()
    {
        short sVar1;
        short* psVar2;
        int tribeID;
        tribeID = 1;
        psVar2 = &DAT_TribesState::instance.tribes[1].size;
        do {
            if (psVar2[-0xe] != 0) {
                sVar1 = *psVar2;
                if (sVar1 < 0x1f) {
                    psVar2[0x126] = sVar1 / 2;
                    psVar2[0x127] = sVar1 * 2;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::trimTribeToSize, DAT_TribesState::ptr)(
                        tribeID, 0x1e);
                    psVar2[0x126] = 0xf;
                    psVar2[0x127] = 0x3c;
                }
                psVar2[0x128] = 0;
            }
            psVar2 = psVar2 + 0x19a;
            tribeID = tribeID + 1;
        } while ((int)psVar2 < 0x17623bc);
    }

}
}
