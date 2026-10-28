#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D730
        void TroopValueState::updateActiveAttackWaveState(int attackWave)
        {
            int playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                playerID = 2;
            }
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave]++ > 0) {
                if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] > 100) {
                    MACRO_CALL_MEMBER(TribesState_Func::applyTribeBehaviorType, DAT_TribesState::ptr)(
                        attackWave, STBT_0x400);
                }
                if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] > 1000) {
                    DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 0;
                }
            }
            else {
                DAT_TroopValueState::instance.attackInfo.someCounter1++;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
                    attackWave, playerID);
                MACRO_CALL_MEMBER(TroopValueState_Func::exitSiegeEquipmentForWave, this)(attackWave);
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackWave, 1000, 10000, STBT_0x3ff);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3ff, STBT_1, 0, 10);
            }
        }

    }
}
}
