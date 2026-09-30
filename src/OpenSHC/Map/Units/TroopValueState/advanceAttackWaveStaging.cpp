#include "../../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0051D690
        void TroopValueState::advanceAttackWaveStaging(int param_1)
        {
            this->attackInfo.field86987_0x20f9c = 0;
            this->attackInfo.value3Array01[param_1] = 2;
            this->attackInfo.attackWaveTicker[param_1] = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::nof_fpoints_locationFinder, DAT_GameState::ptr)();
            this->attackInfo.someCounter1 = this->attackInfo.someCounter1 + 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                param_1, 2, 100000, (SomeTribeBehaviorType)((int)(1019)));
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                (OpenSHC::Map::Units::SomeTribeBehaviorType)1022, OpenSHC::Map::Units::STBT_5, 0, 0x32);
            if (DAT_AttackInfoDefinedData::instance.field0_0x0[this->attackInfo.attacker] <= this->attackInfo.casDis) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, OpenSHC::Map::Units::STBT_5);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    OpenSHC::Map::Units::STBT_5, OpenSHC::Map::Units::STBT_1, 0, 0x28);
            }
        }

    }
}
}
