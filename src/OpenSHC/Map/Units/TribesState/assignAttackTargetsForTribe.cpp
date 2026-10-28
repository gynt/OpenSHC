#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // State 0x67 (scale-point approach) has no enum name. The 0x414 branch ignores setDestinationForUnit's
        // result and stores US_MOVE_TO_DESTINATION a second time after the call (0x5246CF); the common branch
        // removes the unit (ULS_REMOVE) when setDestinationForUnit fails (0x52478A).
        // FUNCTION: STRONGHOLDCRUSADER 0x005244D0
        undefined4 TribesState::assignAttackTargetsForTribe(int tribeID, SomeTribeBehaviorType targetType)
        {
            int unitSelectionIndex = 0;
            BOOLEnum const allAssassins
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->tribes[tribeID].owner] != -1) {
                return 0;
            }
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                    || DAT_UnitsState::instance.units[unitID].dying != 0
                    || DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                    || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                    || DAT_UnitsState::instance.units[unitID].isMovable == 0) {
                    continue;
                }
                if (targetType != STBT_0x3fd) {
                    UnitStateShort const state = DAT_UnitsState::instance.units[unitID].state.generic;
                    if (state == States::US_MELEE_ATTACK_WALL || state == States::US_MOVE_TO_DESTINATION
                        || state == 0x67) {
                        continue;
                    }
                    UnitTypeShort const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (unitType == UT_E_SPEAR) {
                        if (state == States::US_AIM_WEAPONUnk) {
                            continue;
                        }
                    } else if (unitType == UT_E_ENGINEER) {
                        if (state == States::US_RELOAD_WEAPONUnk) {
                            continue;
                        }
                    } else if (unitType == UT_E_LADDER) {
                        if (state == States::US_STATE_3Unk) {
                            continue;
                        }
                    } else if (unitType == UT_TUNNELER) {
                        if (state == States::US_STATE_2Unk || state == States::US_STATE_3Unk
                            || state == States::US_RELOAD_WEAPONUnk || state == States::US_STAND_UPUnk
                            || state == States::US_STATE_9Unk) {
                            continue;
                        }
                    }
                }
                int found;
                uint x;
                uint y;
                uint tile;
                if (targetType == STBT_0x3f2) {
                    found = MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(unitID);
                foundTarget:
                    if (found == 0) {
                        continue;
                    }
                    tile = DAT_TroopValueState::instance.tile;
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
                    if (targetType != STBT_0x414) {
                        goto setTarget;
                    }
                    uint const freeTile
                        = MACRO_CALL_MEMBER(UnitsState_Func::findFreeTileNearby, DAT_UnitsState::ptr)(unitID, tile);
                    if (freeTile != 0) {
                        int const freeTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[freeTile];
                        MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(unitID,
                            freeTile - DAT_ViewportRenderState::instance.translationMatrix[freeTileY].addXgetTile,
                            freeTileY, 0);
                        DAT_UnitsState::instance.units[unitID].attackAtTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)tile;
                        DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep = UIT_ATTACK_WALL;
                        DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
                        DAT_UnitsState::instance.units[unitID].attackAtTileX = (short)tile
                            - (short)DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_UnitsState::instance.units[unitID].attackAtTileY]
                                  .addXgetTile;
                    }
                } else if (targetType == STBT_0x3f4) {
                    found = MACRO_CALL_MEMBER(
                        TroopValueState_Func::findNearestAvailableScalePoint, DAT_TroopValueState::ptr)(unitID);
                    if (found == 0) {
                        continue;
                    }
                    tile = DAT_TroopValueState::instance.tile;
                    y = DAT_TroopValueState::instance.y;
                    x = DAT_TroopValueState::instance.x;
                    DAT_UnitsState::instance.units[unitID].state.generic = 0x67;
                setTarget:
                    DAT_UnitsState::instance.units[unitID].attackAtTileY
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    DAT_UnitsState::instance.units[unitID].targetedBuildingTile = tile;
                    DAT_UnitsState::instance.units[unitID].attackAtTileX = (short)tile
                        - (short)DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_UnitsState::instance.units[unitID].attackAtTileY]
                              .addXgetTile;
                    DAT_UnitsState::instance.units[unitID].siegeTargetBehaviorType = (short)targetType;
                    if (MACRO_CALL_MEMBER(UnitsState_Func::stopUnitIfNextToTarget, DAT_UnitsState::ptr)(unitID) == 0) {
                        if (allAssassins != FALSE) {
                            DAT_PathFindingState::instance.pathForAssassins = 1;
                        }
                        if (MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                                unitID, x, y, 0)
                            == FALSE) {
                            DAT_UnitsState::instance.units[unitID].logicalState = ULS_REMOVE;
                        }
                    }
                    if (DAT_UnitsState::instance.units[unitID].selectionTargetUnitID == unitID) {
                        this->tribes[tribeID].targetX = (short)x;
                        this->tribes[tribeID].targetY = (short)y;
                    }
                } else {
                    if (targetType == STBT_0x3f3) {
                        found = MACRO_CALL_MEMBER(
                            TroopValueState_Func::findNearestAvailableScalePoint, DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x3f5) {
                        found = MACRO_CALL_MEMBER(
                            TroopValueState_Func::findEnemyBuildingsClosestToUnit, DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x3fb) {
                        found = MACRO_CALL_MEMBER(TroopValueState_Func::calculateTile2PeoplValueClosestToUnit,
                            DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x3fd) {
                        found
                            = MACRO_CALL_MEMBER(TroopValueState_Func::findEnemyLord, DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x3f6) {
                        found = MACRO_CALL_MEMBER(
                            TroopValueState_Func::findEnemyTowersOrGates, DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x413 || targetType == STBT_0x414) {
                        found = MACRO_CALL_MEMBER(
                            TroopValueState_Func::findWideTargetClosestToUnitAndCamp, DAT_TroopValueState::ptr)(unitID);
                    } else if (targetType == STBT_0x3f7) {
                        found = MACRO_CALL_MEMBER(TroopValueState_Func::calculateTile2MoatValueClosestToUnit,
                            DAT_TroopValueState::ptr)(unitID);
                    } else {
                        continue;
                    }
                    goto foundTarget;
                }
            }
            return 1;
        }

    }
}
}
