#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Tribes 1..0x4E1 (countdown loop 0x52375C..0x523782); tribeType compared via movsx (signed).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523750
        void TribesState::flagTribesOfType(int tribeType)
        {
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (this->tribes[tribeID].tribeState != 0 && this->tribes[tribeID].tribeType == tribeType) {
                    this->tribes[tribeID].pendingEventFlag = 1;
                }
            }
        }

    }
}
}
