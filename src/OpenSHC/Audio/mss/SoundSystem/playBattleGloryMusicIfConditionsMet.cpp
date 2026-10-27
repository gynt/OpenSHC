#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A580
        void SoundSystem::playBattleGloryMusicIfConditionsMet()
        {
            if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.musicMode == 5
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleEndTransitionDone == 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel != 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter == 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant != 1
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.siegeAttackerMusicMode == 0) {
                DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter = 1;
                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
                MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                    DE::SHCDE::MUSIC_TUNE_BATTLE_L2_GLORY1, 100);
            }
        }

    }
}
}
