/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CrusadeMissionIntro.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CrusadeMissionIntro {

            /**
             * Prepare handler of the Crusader Trail mission intro view: loads skirmish_background.tgx and shc_back,
             * clears INT_00eb9ae8 (so the map header is re-read on the next frame) and enables drawing via
             * MissionDefinedData.crusadeMissionIntroActive.
             */
            void __cdecl MenuView_CrusadeMissionIntro_Prepare();

            /**
             * Per-frame handler of the Crusader Trail mission intro / briefing: returns unless
             * DAT_MissionDefinedData.crusadeMissionIntroActive; shows 'Crusader Trail Completed!' when the progress
             * of the current trail (Extreme > 19, Warchest > 29, First Edition > 49) is past the last mission.
             * Otherwise (pre-mission, briefingOpenedFromInGame == 0) loads the trail mission data, reads the map
             * header once, draws the minimap preview with keep markers (keepPositions[i] x/y offset into the
             * preview box), the human/computer starting gold from the advantage/intensity table (x3 on Extreme),
             * the mission number and name (font 0x10 instead of 0xf if the name is wider than 445 px), then
             * collects the participating players (pre-mission: humans + active AI; in-game: finalResults.active,
             * players without a living lord flagged dead), selection-sorts them by team and draws team separators,
             * avatars (skull + dimmed avatar for dead lords once 200 ticks have passed), names in player colour and
             * colour icons. Mission number shown: Extreme progress+1, First Edition progress+1, Warchest
             * progress+0x33 (51..80, same value as its text index, i.e. numbering continues after the 50 First
             * Edition missions).
             */
            void __cdecl MenuView_CrusadeMissionIntro_DoEveryFrame();

        } // namespace CrusadeMissionIntro
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
