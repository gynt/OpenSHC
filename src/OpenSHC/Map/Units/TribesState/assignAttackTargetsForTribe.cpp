#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005244D0
        undefined4 TribesState::assignAttackTargetsForTribe(int tribeID, SomeTribeBehaviorType targetType)
        {
            UnitStateShort UVar1;
            UnitTypeShort UVar2;
            short sVar3;
            BOOLEnum BVar4;
            uint _unitID;
            int _tile2;
            uint _freeTile;
            int iVar5;
            BOOLEnum BVar6;
            int unitSelectionIndex;
            bool bVar7;
            uint _x;
            uint _y;
            short _targetTileY;
            uint _tile1;
            unitSelectionIndex = 0;
            BVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->tribes[tribeID].owner] != -1) {
                return (undefined4)(0);
            }
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((((DAT_UnitsState::instance.units[_unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                             && (DAT_UnitsState::instance.units[_unitID].dying == 0))
                            && (DAT_UnitsState::instance.units[_unitID].usingTeleport == 0))
                        && ((DAT_UnitsState::instance.units[_unitID].field303_0x413 == 0
                            && (DAT_UnitsState::instance.units[_unitID].moveableUnk != 0)))) {
                        /*
                          fixme: this is some interesting data happening all over the unit code
                         */
                        if (targetType == 1021) {
                        LAB_00524621:
                            if (targetType == 1010) {
                                _tile2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::findEnemyWalls,
                                    DAT_TroopValueState::ptr)(_unitID);
                            LAB_00524638:
                                _tile1 = DAT_TroopValueState::instance.tile;
                                _y = DAT_TroopValueState::instance.y;
                                _x = DAT_TroopValueState::instance.x;
                                if (_tile2 != 0) {
                                    DAT_UnitsState::instance.units[_unitID].state.generic
                                        = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                                    if (targetType != OpenSHC::Map::Units::STBT_0x414)
                                        goto LAB_0052471e;
                                    _freeTile
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findFreeTileNearby,
                                            DAT_UnitsState::ptr)(_unitID, _tile1);
                                    if (_freeTile != 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                            DAT_UnitsState::ptr)(_unitID,
                                            (uint)((int)(_freeTile
                                                - DAT_ViewportRenderState::instance
                                                    .translationMatrix[DAT_ViewportRenderState::instance
                                                            .tileTranslationMatrix_YComponent[_freeTile]]
                                                    .addXgetTile)),
                                            (uint)((int)((int)DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[_freeTile])),
                                            0);
                                        sVar3 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[_tile1];
                                        DAT_UnitsState::instance.units[_unitID].attackAtTileY = sVar3;
                                        DAT_UnitsState::instance.units[_unitID].targetID_OR_targetBuildingID
                                            = (short)_tile1;
                                        iVar5 = DAT_ViewportRenderState::instance.translationMatrix[sVar3].addXgetTile;
                                        DAT_UnitsState::instance.units[_unitID].targetingType
                                            = OpenSHC::Map::Units::UIT_ATTACK_WALL;
                                        DAT_UnitsState::instance.units[_unitID].state.generic
                                            = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                                        DAT_UnitsState::instance.units[_unitID].attackAtTileX
                                            = (short)_tile1 - (short)iVar5;
                                    }
                                }
                            } else {
                                if (targetType != OpenSHC::Map::Units::STBT_0x3f4) {
                                    if (targetType == OpenSHC::Map::Units::STBT_0x3f3) {
                                        _tile2 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::findNearestAvailableScalePoint,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else if (targetType == OpenSHC::Map::Units::STBT_0x3f5) {
                                        _tile2 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::findEnemyBuildingsClosestToUnit,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else if (targetType == OpenSHC::Map::Units::STBT_0x3fb) {
                                        _tile2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::
                                                                       calculateTile2PeoplValueClosestToUnit,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else if (targetType == OpenSHC::Map::Units::STBT_0x3fd) {
                                        _tile2 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::findEnemyLord,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else if (targetType == OpenSHC::Map::Units::STBT_0x3f6) {
                                        _tile2 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::findEnemyTowersOrGates,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else if ((targetType == OpenSHC::Map::Units::STBT_0x413)
                                        || (targetType == OpenSHC::Map::Units::STBT_0x414)) {
                                        _tile2 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TroopValueState_Func::getClosestWideValueBasedOnPlayer,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    } else {
                                        if (targetType != OpenSHC::Map::Units::STBT_0x3f7)
                                            continue;
                                        _tile2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::
                                                                       calculateTile2MoatValueClosestToUnit,
                                            DAT_TroopValueState::ptr)(_unitID);
                                    }
                                    goto LAB_00524638;
                                }
                                iVar5 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::TroopValueState_Func::findNearestAvailableScalePoint,
                                    DAT_TroopValueState::ptr)(_unitID);
                                _tile1 = DAT_TroopValueState::instance.tile;
                                _y = DAT_TroopValueState::instance.y;
                                _x = DAT_TroopValueState::instance.x;
                                if (iVar5 == 0)
                                    continue;
                                DAT_UnitsState::instance.units[_unitID].state.generic = ((UnitState)0x67);
                            LAB_0052471e:
                                _targetTileY
                                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile1];
                                DAT_UnitsState::instance.units[_unitID].attackAtTileY = _targetTileY;
                                DAT_UnitsState::instance.units[_unitID].targetedBuildingTile = _tile1;
                                DAT_UnitsState::instance.units[_unitID].attackAtTileX = (short)_tile1
                                    - (short)DAT_ViewportRenderState::instance.translationMatrix[_targetTileY]
                                          .addXgetTile;
                                DAT_UnitsState::instance.units[_unitID].unknownDigMoatOrWallAttackFlag1015
                                    = (undefined2)targetType;
                                iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::stopUnitIfNextToTarget,
                                    DAT_UnitsState::ptr)(_unitID);
                                if (iVar5 == 0) {
                                    if (BVar4 != FALSE) {
                                        DAT_PathFindingState::instance.allAssassinsUnk = 1;
                                    }
                                    BVar6
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                            DAT_UnitsState::ptr)(_unitID, _x, _y, 0);
                                    if (BVar6 == FALSE) {
                                        DAT_UnitsState::instance.units[_unitID].logicalState
                                            = OpenSHC::Map::Units::ULS_REMOVE;
                                    }
                                }
                                if ((int)DAT_UnitsState::instance.units[_unitID].selectionTargetUnitID == _unitID) {
                                    this->tribes[tribeID].targetX = (short)_x;
                                    this->tribes[tribeID].targetY = (short)_y;
                                }
                            }
                        } else {
                            UVar1 = DAT_UnitsState::instance.units[_unitID].state.generic;
                            if (((UVar1 != OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL)
                                    && (UVar1 != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION))
                                && (UVar1 != ((UnitState)0x67))) {
                                UVar2 = DAT_UnitsState::instance.units[_unitID].unitType;
                                if (UVar2 == OpenSHC::Map::Units::UT_E_SPEAR) {
                                    bVar7 = UVar1 == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                                } else if (UVar2 == OpenSHC::Map::Units::UT_E_ENGINEER) {
                                    bVar7 = UVar1 == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                                } else if (UVar2 == OpenSHC::Map::Units::UT_E_LADDER) {
                                    bVar7 = UVar1 == ((UnitState)3);
                                } else {
                                    if (UVar2 != OpenSHC::Map::Units::UT_TUNNELER)
                                        goto LAB_00524621;
                                    if ((((UVar1 == ((UnitState)2)) || (UVar1 == ((UnitState)3)))
                                            || (UVar1 == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk))
                                        || (UVar1 == OpenSHC::Map::Units::States::US_STAND_UPUnk))
                                        continue;
                                    bVar7 = UVar1
                                        == (OpenSHC::Map::Units::States::US_STAND_UPUnk
                                            | OpenSHC::Map::Units::States::US_IDLEUnk);
                                }
                                if (!bVar7)
                                    goto LAB_00524621;
                            }
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
            return (undefined4)(1);
        }

    }
}
}
