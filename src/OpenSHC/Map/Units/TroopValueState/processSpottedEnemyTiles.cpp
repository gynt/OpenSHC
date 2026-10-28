#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // A tile >= 80400 has its slot zeroed, but the old tile value is still used for the rest of the pass
        // (the original keeps it in edi).
        // FUNCTION: STRONGHOLDCRUSADER 0x0051F950
        void TroopValueState::processSpottedEnemyTiles()
        {
            for (int i = 0; i < 100; ++i) {
                int const tile = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile;
                if (tile <= 0) {
                    continue;
                }
                if (tile >= 80400) {
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                }
                if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value == 100) {
                    if (MACRO_CALL_MEMBER(TroopValueState_Func::shouldLightPitchBasedOnTroopValue, this)(tile,
                            DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID,
                            DAT_TroopValueState::instance.attackInfo.playerID_0x2c850)
                        != FALSE) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::giveLightPitchInstructionToUnitClosestToPitch, this)(
                            tile);
                    }
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = 99;
                }
                else {
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value--;
                    if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value <= 0) {
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                    }
                }
            }
        }

    }
}
}
