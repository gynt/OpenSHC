#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_CreditsAfterCampaignEnd.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A5E0
        void SoundSystem::playDarMehqOrGlory()
        {
            if (*DAT_CreditsAfterCampaignEnd::ptr == 1) {
                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(DAT_SFXDefinedData::ptr->Pointers[0x26].musicFile);
                return;
            }
            if (this->playingMusicId != 0xf) {
                MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_OFF);
                return;
            }
            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(DAT_SFXDefinedData::ptr->Pointers[0x10].musicFile);
            this->playingMusicId = 0;
        }

    }
}
}
