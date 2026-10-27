/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

    /**
     * Resets transient UI/game state on map load: clears Bink-playing flags, hides ~10 in-game display elements
     * (placement info, win/defeat banners, victory/defeat timers, etc.), closes the AI-lord message modal if open,
     * clears the queued video messages, mapper command, logical pause, selection box, the six hotkey viewport-focus
     * slots and a few misc flags.
     */
    void __cdecl resetTransientGameStateOnMapLoad();

} // namespace Map
} // namespace OpenSHC
