#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe leader test and the tribe target go through this, the 0x3F2 fallback write of the tribe
        // behaviour through DAT_TribesState::instance (0x521394), as in the original.
        // FUNCTION: STRONGHOLDCRUSADER 0x00521280
        undefined4 TribesState::moveUnitToBehaviorTarget(int unitID, int behaviorType)
        {
            int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
            int targetFound = 0;
            uint tile = 0;
            uint x = 0;
            uint y = 0;
            if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                || DAT_UnitsState::instance.units[unitID].dying != 0
                || DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                || DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    != -1) {
                return 0;
            }
            if (behaviorType == 0x3f2) {
                if (MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(unitID) != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x3f5) {
                if (MACRO_CALL_MEMBER(
                        TroopValueState_Func::findEnemyBuildingsClosestToUnit, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x3fb) {
                if (MACRO_CALL_MEMBER(
                        TroopValueState_Func::calculateTile2PeoplValueClosestToUnit, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                } else if (MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    if (this->tribes[tribeID].leaderUnitID == unitID) {
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_0x3f2;
                    }
                    DAT_UnitsState::instance.units[unitID].siegeTargetBehaviorType = 0x3f2;
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x3fd) {
                if (MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyLord, DAT_TroopValueState::ptr)(unitID) != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x3f6) {
                if (MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyTowersOrGates, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x413) {
                if (MACRO_CALL_MEMBER(
                        TroopValueState_Func::findWideTargetClosestToUnitAndCamp, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x414) {
                if (MACRO_CALL_MEMBER(
                        TroopValueState_Func::findWideTargetClosestToUnitAndCamp, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            } else if (behaviorType == 0x3f7) {
                if (MACRO_CALL_MEMBER(
                        TroopValueState_Func::findNearestDiggableMoatPoint, DAT_TroopValueState::ptr)(unitID)
                    != 0) {
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    tile = DAT_TroopValueState::instance.tile;
                    targetFound = 1;
                }
            }
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = 0;
            if (targetFound == 0) {
                return 0;
            }
            DAT_UnitsState::instance.units[unitID].attackAtTileY
                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = tile;
            DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[unitID].attackAtTileX = (short)tile
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_UnitsState::instance.units[unitID].attackAtTileY]
                      .addXgetTile;
            if (DAT_UnitsState::instance.units[unitID].selectionTargetUnitID == unitID) {
                this->tribes[tribeID].targetX = DAT_UnitsState::instance.units[unitID].attackAtTileX;
                this->tribes[tribeID].targetY = DAT_UnitsState::instance.units[unitID].attackAtTileY;
            }
            if (MACRO_CALL_MEMBER(UnitsState_Func::stopUnitIfNextToTarget, DAT_UnitsState::ptr)(unitID) == 0) {
                MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(unitID, x, y, 0);
            }
            return 1;
        }

    }
}
}
