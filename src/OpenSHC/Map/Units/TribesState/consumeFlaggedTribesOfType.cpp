#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // maxCount is checked before every tribe (jle at 0x5237A7); the consumed flag pendingEventFlag (+0x28A) is
        // cleared and the next word isProvoked (+0x28C) set to 1.
        // FUNCTION: STRONGHOLDCRUSADER 0x00523790
        void TribesState::consumeFlaggedTribesOfType(int tribeType, int maxCount)
        {
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (maxCount <= 0) {
                    return;
                }
                if (this->tribes[tribeID].tribeState != 0 && this->tribes[tribeID].tribeType == tribeType
                    && this->tribes[tribeID].pendingEventFlag != 0) {
                    this->tribes[tribeID].pendingEventFlag = 0;
                    this->tribes[tribeID].isProvoked = 1;
                    --maxCount;
                }
            }
        }

    }
}
}
