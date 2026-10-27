#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // buildingType > 0x5A ends (signed jge 0x4660F8). Snoozed -> wake up ("other_warning7.wav" for the local
    // player), else snooze ("other_warning12.wav" = SFX_WorkHaltedMyLord).
    // FUNCTION: STRONGHOLDCRUSADER 0x004660F0
    void Actions::ProcessBuildingSleepUpdate(int playerID, int buildingType)
    {
        if (buildingType >= 0x5B) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType]) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = false;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning7_wav_005a58b0);
            }
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = true;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    SFX_WorkHaltedMyLord);
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateAllBuildingsSnoozedState,
            DAT_BuildingsState::ptr)(playerID, buildingType);
    }

}
}
