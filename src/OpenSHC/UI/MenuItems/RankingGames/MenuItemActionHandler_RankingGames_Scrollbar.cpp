#include "../RankingGames.func.hpp"

#include "OpenSHC/Globals/g_leaderboardEntryCount.hpp"
#include "OpenSHC/Globals/g_rankingGamesScrollOffset.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D9B30
        void RankingGames::MenuItemActionHandler_RankingGames_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 1;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                if (*currentValue != g_rankingGamesScrollOffset::instance) {
                    g_rankingGamesScrollOffset::instance = *currentValue;
                }
                break;
            case 4:
                *minValue = 0;
                iVar1 = g_leaderboardEntryCount::instance + -8;
                *maxValue = iVar1;
                if (iVar1 < 0) {
                    *maxValue = 0;
                }
                if (*currentValue != g_rankingGamesScrollOffset::instance) {
                    *currentValue = g_rankingGamesScrollOffset::instance;
                }
                break;
            case 5:
                if (0 < g_rankingGamesScrollOffset::instance) {
                    g_rankingGamesScrollOffset::instance = g_rankingGamesScrollOffset::instance + -1;
                    *currentValue = g_rankingGamesScrollOffset::instance;
                }
                goto LAB_004d9be7;
            case 6:
                if (g_rankingGamesScrollOffset::instance < g_leaderboardEntryCount::instance + -8) {
                    g_rankingGamesScrollOffset::instance = g_rankingGamesScrollOffset::instance + 1;
                }
            LAB_004d9be7:
                *currentValue = g_rankingGamesScrollOffset::instance;
                break;
            case 7:
                *currentValue = 6;
            }
        }

    }
}
}
