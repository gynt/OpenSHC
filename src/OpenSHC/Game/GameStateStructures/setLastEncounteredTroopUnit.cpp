#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004565A0
    uint GameStateStructures::setLastEncounteredTroopUnit(int playerID, int unitID)
    {
        uint result = playerID - 1;
        int enemyUnitID = DAT_UnitsState::instance.units[unitID].lastAttackerUnitID;
        if ((result <= 7) && (enemyUnitID > 0)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)) {
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01
                = DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 + 1;
            DAT_GameState::instance.playerDataArray[playerID].someXPosition
                = DAT_UnitsState::instance.units[unitID].x;
            DAT_GameState::instance.playerDataArray[playerID].someYPosition
                = DAT_UnitsState::instance.units[unitID].y;
            if ((DAT_UnitsState::instance.units[enemyUnitID].isSelectable_OR_matchTime == 0)
                || (DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_UnitsState::instance.units[enemyUnitID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID])) {
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = 0;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = enemyUnitID;
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitUID
                    = DAT_UnitsState::instance.units[enemyUnitID].uid;
            }
            // 0x456654: add [edx*32 + player + 0x115e9e0] = PlayerData+0x2BE8 + p*32 = [p][1] (array starts at +0x2BE4)
            DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][1]
                = DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                      [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][1]
                + 1;
            result = (uint)&DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                          [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][1];
        }
        return result;
    }
}
}
