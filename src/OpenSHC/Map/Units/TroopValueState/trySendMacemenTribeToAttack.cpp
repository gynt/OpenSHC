#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CF90
        void TroopValueState::trySendMacemenTribeToAttack()
        {
            int const targetPlayerID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            // field_0x2c854 is an int counter (undefined1[4] in the header)
            if (DAT_TroopValueState::instance.attackInfo.macemenTribeCount > 0
                && *(int*)DAT_TroopValueState::instance.attackInfo.field_0x2c854 >= 4
                && (SEC_RNG::instance.currentNumber2 & 7) == 0) {
                int const tribeID
                    = DAT_TroopValueState::instance.attackInfo
                          .macemenTribeArray[--DAT_TroopValueState::instance.attackInfo.macemenTribeCount];
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || DAT_GameCore::instance.missionNumber >= 15) {
                    int const unitID = MACRO_CALL_MEMBER(UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(
                        targetPlayerID);
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 0,
                        Instructions::UMSE_0);
                }
            }
        }

    }
}
}
