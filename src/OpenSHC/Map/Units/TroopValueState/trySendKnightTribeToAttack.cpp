#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D020
        void TroopValueState::trySendKnightTribeToAttack()
        {
            int const targetPlayerID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            // field_0x2c854 is an int counter (undefined1[4] in the header)
            if (DAT_TroopValueState::instance.attackInfo.knightTribeCount > 0
                && *(int*)DAT_TroopValueState::instance.attackInfo.field_0x2c854 >= 10
                && (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x2c854 >= 100
                    || DAT_GameState::instance.playerDataArray[targetPlayerID].previousSiegeWeaponsCount > 0)
                && (SEC_RNG::instance.currentNumber2 & 7) == 0) {
                int const tribeID = DAT_TroopValueState::instance.attackInfo
                                        .knightTribeArray[--DAT_TroopValueState::instance.attackInfo.knightTribeCount];
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                int unitID;
                if (DAT_GameState::instance.playerDataArray[targetPlayerID].previousSiegeWeaponsCount != 0) {
                    unitID = MACRO_CALL_MEMBER(UnitsState_Func::findActiveSiegeEngineOfPlayer, DAT_UnitsState::ptr)(
                        targetPlayerID);
                } else {
                    unitID = MACRO_CALL_MEMBER(UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(
                        targetPlayerID);
                }
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 0,
                    Instructions::UMSE_0);
            }
        }

    }
}
}
