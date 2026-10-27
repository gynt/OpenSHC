/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/SettingsFileState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {

#pragma pack(push, 1)

    // SIZE: 0x00000002
    class SettingsFileState {
    public:
        undefined1 padding_0x0[2]; // 0x00000000 length: 2

    private:
        SettingsFileState(SettingsFileState const&);
        void operator=(SettingsFileState const&);

    public:
        SettingsFileState() {};
        ~SettingsFileState() {};

        /**
         * Loads <Documents>\Stronghold Crusader\crusader.cfg: sets defaults first (difficulties, trail
         * progress/years, months -1), uses default settings if the file is missing; otherwise reads user text slots
         * 5/6/7/0 (ANSI if file < 1000 bytes, else UTF-16), game speed, bubble help, a discarded resolution value,
         * zoom, scroll speed, sound on/volumes, scenario progress, furthest mission, autosave interval,
         * difficulties, cursor type, 4 recent IP strings, skirmish/warchest/extreme trail progress, tactical/unused
         * flags and finally the resolution. Afterwards resets zoom, unusedOption1, text slot 9 and the start date.
         */
        void readUserConfig();

        /**
         * Writes <Documents>\Stronghold Crusader\crusader.cfg in the UTF-16 format: user text slots 5/6/7/0, game
         * speed, bubble help, resolution (ignored when read back), zoom, scroll speed, sound settings, scenario
         * progress, difficulties, cursor type, 4 IP strings, all trail progress data, tactical/unused flag bytes
         * and the resolution again.
         */
        void writeUserConfig();
    };

    static_assert_cpp98_obj(sizeof(SettingsFileState) == 2, SettingsFileState);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
