/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS.hpp'
*/

#pragma once

#include "WinDef.h"
#include "basetsd.h"
namespace OpenSHC {
namespace Audio {
    namespace MSS {

        /**
         * winmm timer callback for the Miles sound system: unless disabled (field14_0x54), already running
         * (field15_0x58 reentrancy guard) or waveOut not open, checks the music stream (slot 0, active and not
         * paused); if its sample is no longer playing (status != 4/SMP_PLAYING) stops music playback, else calls
         * playMusicUnk.
         */
        void __stdcall SndSystemTimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

        /**
         * Registers AIL_shutdown with atexit so Miles is shut down on process exit; returns 0.
         */
        int __cdecl RegisterMilesAILShutdown();

    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
