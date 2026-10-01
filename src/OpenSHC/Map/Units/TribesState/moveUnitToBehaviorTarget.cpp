#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00521280
        undefined4 TribesState::moveUnitToBehaviorTarget(int unitID, int param_2)
        {
            short sVar1;
            short sVar2;
            bool bVar3;
            int iVar4;
            uint x;
            short sVar5;
            uint uVar6;
            uint local_c;
            sVar1 = DAT_UnitsState::instance.units[unitID].tribeID;
            bVar3 = false;
            x = 0;
            uVar6 = 0;
            local_c = 0;
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].dying != 0) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].field303_0x413 != 0) {
                return (undefined4)(0);
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                != -1) {
                return (undefined4)(0);
            }
            if (param_2 == 0x3f2) {
                iVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(unitID);
            LAB_0052130b:
                if (iVar4 == 0)
                    goto LAB_0052143b;
                local_c = DAT_TroopValueState::instance.y;
            } else if (param_2 == 0x3f5) {
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::findEnemyBuildingsClosestToUnit,
                    DAT_TroopValueState::ptr)(unitID);
            LAB_00521333:
                if (iVar4 == 0)
                    goto LAB_0052143b;
                local_c = DAT_TroopValueState::instance.y;
            } else {
                if (param_2 == 0x3fb) {
                    iVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TroopValueState_Func::calculateTile2PeoplValueClosestToUnit,
                        DAT_TroopValueState::ptr)(unitID);
                    if (iVar4 == 0) {
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::findEnemyWalls,
                            DAT_TroopValueState::ptr)(unitID);
                        if (iVar4 == 0)
                            goto LAB_0052143b;
                        if (DAT_TribesState::instance.tribes[sVar1].selectionTargetUnitID == unitID) {
                            DAT_TribesState::instance.tribes[sVar1].tribeBehaviorType = OpenSHC::Map::Units::STBT_0x3f2;
                        }
                        local_c = DAT_TroopValueState::instance.y;
                        DAT_UnitsState::instance.units[unitID].unknownDigMoatOrWallAttackFlag1015 = 0x3f2;
                        goto LAB_0052142a;
                    }
                } else {
                    if (param_2 == 0x3fd) {
                        iVar4 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::findEnemyLord, DAT_TroopValueState::ptr)(unitID);
                        goto LAB_00521333;
                    }
                    if (param_2 == 0x3f6) {
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::findEnemyTowersOrGates,
                            DAT_TroopValueState::ptr)(unitID);
                    } else {
                        if (param_2 == 0x413) {
                            iVar4 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TroopValueState_Func::getClosestWideValueBasedOnPlayer,
                                DAT_TroopValueState::ptr)(unitID);
                            goto LAB_0052130b;
                        }
                        if (param_2 == 0x414) {
                            iVar4 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TroopValueState_Func::getClosestWideValueBasedOnPlayer,
                                DAT_TroopValueState::ptr)(unitID);
                            goto LAB_00521333;
                        }
                        if (param_2 != 0x3f7)
                            goto LAB_0052143b;
                        iVar4
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::findNearestDiggableMoatPoint,
                                DAT_TroopValueState::ptr)(unitID);
                    }
                    if (iVar4 == 0)
                        goto LAB_0052143b;
                }
                local_c = DAT_TroopValueState::instance.y;
            }
        LAB_0052142a:
            bVar3 = true;
            x = DAT_TroopValueState::instance.x;
            uVar6 = DAT_TroopValueState::instance.tile;
        LAB_0052143b:
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = 0;
            if (!bVar3) {
                return (undefined4)(0);
            }
            sVar5 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[uVar6];
            sVar2 = DAT_UnitsState::instance.units[unitID].selectionTargetUnitID;
            DAT_UnitsState::instance.units[unitID].attackAtTileY = sVar5;
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = uVar6;
            sVar5 = (short)uVar6 - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar5].addXgetTile;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[unitID].attackAtTileX = sVar5;
            if (sVar2 == unitID) {
                DAT_TribesState::instance.tribes[sVar1].targetX = sVar5;
                DAT_TribesState::instance.tribes[sVar1].targetY = DAT_UnitsState::instance.units[unitID].attackAtTileY;
            }
            iVar4 = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::stopUnitIfNextToTarget, DAT_UnitsState::ptr)(unitID);
            if (iVar4 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, x, local_c, 0);
            }
            return (undefined4)(1);
        }

    }
}
}
