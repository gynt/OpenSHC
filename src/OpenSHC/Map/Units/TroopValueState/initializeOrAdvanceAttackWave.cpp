#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051FF90
        void TroopValueState::initializeOrAdvanceAttackWave(int param_1)
        {
            int* piVar1;
            if (this->attackInfo.attackWaveTicker[param_1] == 0) {
                this->attackInfo.attackWaveTicker[param_1] = 1;
                this->attackInfo.field105440_0x25b00 = this->attackInfo.field105440_0x25b00 + 1;
                this->attackInfo.someCounter1 = 1;
                this->attackInfo.field86987_0x20f9c = 0;
                this->attackInfo.padding_0x21c54[0] /* 0x21C54: start of padding_0x21c54 in the header */ = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(1);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::initializeAttackZoneSearch, this)(param_1);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recountTotalTroopValue, this)();
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 2, 100000, OpenSHC::Map::Units::STBT_0x3fb);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    OpenSHC::Map::Units::STBT_0x3fe, OpenSHC::Map::Units::STBT_1, 0, 0x32);
                this->attackInfo.casDis = MACRO_CALL_MEMBER(
                    OpenSHC::Map::WildlifeState_Func::getDistanceToNearestUnknownNonZero01FromSignpost,
                    DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::applyTribeBehaviorType, DAT_TribesState::ptr)(
                    param_1, OpenSHC::Map::Units::STBT_3);
            }
            if ((char)this->attackInfo.nof_tribes[param_1] + -5
                <= (int)(char)this->attackInfo.unknownByteArray02[param_1]) {
                piVar1 = this->attackInfo.attackWaveTicker + param_1;
                *piVar1 = *piVar1 + 1;
                if (DAT_AttackInfoDefinedData::instance.field1_0x28[this->attackInfo.attacker]
                    <= this->attackInfo.attackWaveTicker[param_1]) {
                    if (this->attackInfo.attacker == 8) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::playAttackAlarmSound, this)();
                        this->attackInfo.attackWaveTicker[param_1] = 10000;
                        this->attackInfo.value3Array01[param_1] = 3;
                        this->attackInfo.value10 = 0;
                    }
                    this->attackInfo.value3Array01[param_1] = 1;
                    this->attackInfo.attackWaveTicker[param_1] = 0;
                }
            }
        }

    }
}
}
