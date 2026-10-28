// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B490
        void SoundSystem::openSound(char* filePath)
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            strcpy(this->currentMusicFilename, filePath);
            if (!this->musicStreamStopped) {
                DAT_SoundEffectsHelperData1::ptr->musicStreamBusyMainThread = TRUE;
                if (this->queuedMusicFileHandle != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->queuedMusicFileHandle);
                }
                this->queuedMusicFileHandle = MACRO_CALL(OS_Func::_ucrt_open)(filePath, _O_BINARY, 0);
                DAT_SoundEffectsHelperData1::ptr->musicStreamBusyMainThread = FALSE;
                return;
            }

            MACRO_CALL_MEMBER(SoundSystem_Func::playMusicFileByName, this)(filePath);
        }

    }
}
}
