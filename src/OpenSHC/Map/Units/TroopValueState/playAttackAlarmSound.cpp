#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B6C0
        void TroopValueState::playAttackAlarmSound()
        {
            char* filename;
            MACRO_CALL_MEMBER(
                Audio::MSS::SoundSystem_Func::playBattleGloryMusicIfConditionsMet, DAT_SoundSystemState::ptr)();
            switch (this->attackInfo.attacker) {
            case 2:
            case 3:
            case 4:
                filename = S_BATTLEHORN_WAV_005A77D8;
                break;
            case 5:
                filename = S_DRUMHORN_WAV_005ABB58;
                break;
            default:
                goto switchD_0051b6d7_caseD_4;
            }
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(filename);
        switchD_0051b6d7_caseD_4:
            this->attackInfo.attackAlarmPlayed = 1;
        }

    }
}
}
