#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00525F20
        BOOLEnum TribesState::spawnDeerLionOrRabbit(int tribeID, int param_2, UnitType unitType)
        {
            short* psVar1;
            short sVar2;
            int _finalTargetUnitID;
            int iVar3;
            uint _rng2;
            short _terrainHeight;
            short _unknown;
            short _tribeSize;
            short _unitX;
            short _targetUnitID;
            short _unitY;
            if ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
                && (0 < tribeID)) {
                if (this->tribes[tribeID].field133_0x278 != 0) {
                    return FALSE;
                }
                _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                _finalTargetUnitID = (int)_targetUnitID;
                if (unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                    _finalTargetUnitID
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getNonDyingUnit, this)(tribeID);
                    if (_finalTargetUnitID == 0) {
                        _finalTargetUnitID = (int)_targetUnitID;
                    }
                }
                _rng2 = (uint)(byte)SEC_RNG::instance.currentNumber2;
                _terrainHeight = DAT_UnitsState::instance.units[_finalTargetUnitID].terrainOrClimbHeight;
                _unknown = this->tribes[tribeID].field137_0x280;
                _tribeSize = this->tribes[tribeID].size;
                _unitX = DAT_UnitsState::instance.units[_finalTargetUnitID].x;
                _unitY = DAT_UnitsState::instance.units[_finalTargetUnitID].y;
                if (_tribeSize <= _unknown) {
                    param_2 = (int)(param_2 + (param_2 >> 0x1f & 3U)) >> 2;
                }
                psVar1 = &this->tribes[tribeID].field139_0x284;
                *psVar1 = *psVar1 + 1;
                if ((param_2 <= this->tribes[tribeID].field139_0x284)
                    && (sVar2 = this->tribes[tribeID].field138_0x282, this->tribes[tribeID].field139_0x284 = 0,
                        _tribeSize < sVar2)) {
                    if ((unitType == OpenSHC::Map::Units::UT_RABBIT)
                        && (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation != 0)) {
                        iVar3 = 110;
                    } else {
                        iVar3 = ((_unknown <= _tribeSize) - 1 & 0xffffffb5) + 100;
                    }
                    if (iVar3 <= (int)(_rng2 & 0x7f)) {
                        _rng2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            0, 0, (int)((int)(_unitX * 8)), (int)((int)(_unitY * 8)), (int)((int)(_terrainHeight)),
                            unitType);
                        if (_rng2 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(
                                _rng2, tribeID);
                            DAT_UnitsState::instance.units[_rng2].substate
                                = (byte)DAT_UnitsState::instance.units[_rng2].fixedRng & 3;
                            if (unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                                DAT_UnitsState::instance.units[_rng2].antelopeBasedRngValue = 2;
                            }
                            DAT_UnitsState::instance.units[_rng2].disappearFadeAlphaCountdown = 0x20;
                            if (unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateAnimalHerdBehaviorState,
                                    this)(tribeID);
                            }
                            return TRUE;
                        }
                    }
                }
                return FALSE;
            }
            return FALSE;
        }

    }
}
}
