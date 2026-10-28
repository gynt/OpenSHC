#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/g_rankingGamesScrollOffset.hpp"
#include "OpenSHC/Globals/g_leaderboardFilterMode.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9270
        void __cdecl SetRankingGamesListMode(undefined4 sequenceIndex)
        {
            g_leaderboardFilterMode::instance = sequenceIndex;
            g_rankingGamesScrollOffset::instance = 0;
        }

    }
}
}
