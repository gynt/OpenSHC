#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // g_tribeScanIndex is declared undefined4 but compared signed (jg at 0x522755 / 0x5227B2).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522720
        int TribesState::getAvailableTribeID(int playerID)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                g_tribeScanIndex::instance = 0x4E1;
                while (this->tribes[g_tribeScanIndex::instance].tribeState != 0
                    || this->tribes[g_tribeScanIndex::instance].emptyKeepAliveUntilTick != 0) {
                    --g_tribeScanIndex::instance;
                    if ((int)g_tribeScanIndex::instance <= 0) {
                        return 0;
                    }
                }
                int const tribeID = g_tribeScanIndex::instance;
                if (tribeID > 0) {
                    this->tribes[tribeID].emptyKeepAliveUntilTick = 1;
                    return tribeID;
                }
            } else {
                g_tribeScanIndex::instance = 0x4E2 - playerID;
                if ((int)g_tribeScanIndex::instance > 0) {
                    while (this->tribes[g_tribeScanIndex::instance].tribeState != 0
                        || this->tribes[g_tribeScanIndex::instance].emptyKeepAliveUntilTick != 0) {
                        g_tribeScanIndex::instance -= 8;
                        if ((int)g_tribeScanIndex::instance <= 0) {
                            return 0;
                        }
                    }
                    int const tribeID = g_tribeScanIndex::instance;
                    if (tribeID > 0) {
                        this->tribes[tribeID].emptyKeepAliveUntilTick
                            = (short)(DAT_GameCore::instance.mapTimeInTicks + 400);
                        return tribeID;
                    }
                }
            }
            return 0;
        }

    }
}
}
