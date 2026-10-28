#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A15B0
        BOOLEnum PathFindingState::isEnemyUnitWithinDistance(int playerID, uint x, uint y, int requiredDistance)
        {
            if (399 < x || 399 < y) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            int _requiredDistanceSq = requiredDistance * requiredDistance;
            int* _enemyUIDs = (int*)(playerID * 10000 + 0x11a66f0);
            int _enemies = DAT_GameState::instance.playerDataArray[playerID].enemyListCount;
            for (int _enemyLoopCounter = 0; _enemyLoopCounter < _enemies; _enemyLoopCounter++) {
                int _enemyID = DAT_GameState::instance.playerDataArray[playerID].enemyIDArray[_enemyLoopCounter];
                if (DAT_UnitsState::instance.units[_enemyID].dying == 0
                    && DAT_UnitsState::instance.units[_enemyID].uid == _enemyUIDs[_enemyLoopCounter]) {
                    int _xEnemyDistance = x - (int)DAT_UnitsState::instance.units[_enemyID].x;
                    int _yEnemyDistance = y - (int)DAT_UnitsState::instance.units[_enemyID].y;
                    if (_yEnemyDistance * _yEnemyDistance + _xEnemyDistance * _xEnemyDistance < _requiredDistanceSq
                        && DAT_UnitsState::instance.units[_enemyID].isHiddenInBuilding == 0
                        && DAT_UnitsState::instance.units[_enemyID].moveRelatedFlag != 1
                        && DAT_UnitsState::instance.units[_enemyID].isAnimalOrAmbient == 0
                        && DAT_UnitsState::instance.units[_enemyID].owner != 0) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
