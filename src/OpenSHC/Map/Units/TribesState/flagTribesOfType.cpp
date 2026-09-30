#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00523750
        void TribesState::flagTribesOfType(int param_1)
        {
            Tribe* psVar1;
            int iVar1;
            psVar1 = &this->tribes[1];
            iVar1 = 0x4e1;
            do {
                if ((psVar1->tribeState != 0) && ((short)psVar1->tribeType == param_1)) {
                    psVar1->unknownBool02 = 1;
                }
                psVar1 = psVar1 + 0x19a;
                iVar1 = iVar1 + -1;
            } while (iVar1 != 0);
        }

    }
}
}
