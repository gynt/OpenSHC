#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424700
        void SoundSystem::endSpeechStreamsAndResetLoopFlags()
        {
            this->streamFlagsAndLoopCount[4] = 0;
            this->streamFlagsAndLoopCount[3] = 0;
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_2);
        }

    }
}
}
