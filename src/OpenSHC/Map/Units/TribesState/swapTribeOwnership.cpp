#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // the original reads DAT_TribesState::instance instead of this
        // FUNCTION: STRONGHOLDCRUSADER 0x00521240
        void TribesState::swapTribeOwnership(int playerA, int playerB)
        {
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState == 2) {
                    if (DAT_TribesState::instance.tribes[i].owner == playerA) {
                        DAT_TribesState::instance.tribes[i].owner = playerB;
                    } else if (DAT_TribesState::instance.tribes[i].owner == playerB) {
                        DAT_TribesState::instance.tribes[i].owner = playerA;
                    }
                }
            }
        }

    }
}
}
