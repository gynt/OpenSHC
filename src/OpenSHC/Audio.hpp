/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {

    /**
     * Resets state used by the Genie advisor speech feedback: player ranking, keep-enclosed flag, unit-loss and
     * destroyed-building histories; the keep-enclosure timer/cooldown and last status message time are all set to
     * the current timeGetTime().
     */
    void __cdecl resetGenieSpeechFeedbackState();

} // namespace Audio
} // namespace OpenSHC
