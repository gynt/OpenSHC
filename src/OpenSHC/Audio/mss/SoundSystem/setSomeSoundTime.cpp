#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A2A0
        void SoundSystem::setSomeSoundTime()
        {
            if (!(0 < this->playingMusicId && this->musicFadeState != 2)) {
                return;
            }

            if (this->musicFadeState == 1) {
                DWORD _currentTime = timeGetTime();
                // This logic seems to smooth out a time difference by not having the timestamp jump directly on
                //   bigger delays. Instead, it settles slightly behind the real time, basically pushing the current
                //   timestamp back a small bit, but in such a way that is gets closer and closer to the real time.
                this->musicFadeStartTime
                    = (_currentTime + ((_currentTime - this->musicFadeStartTime) / 200) * -10) - 1;
                this->musicFadeState = 2;
            } else {
                this->musicFadeState = 2;
                this->musicFadeStartTime = timeGetTime();
            }
        }
    }

}
}
