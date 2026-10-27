/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CrusadeMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CrusadeMap {

            /**
             * Prepare handler of the Crusader Trail map view: loads the trail map image for the current trail type
             * (shcx_map / skirmish_trail2 / skirmish_trail), clamps the trail progress values (49/29/19), and
             * computes DAT_TrailMissionSkipsLeft = 3 minus the number of skipped missions (monthsTakenOrChicken ==
             * -1200) among the first furthest*TrailMission entries, clamped at 0. Original bug: the extreme-
             * progress clamp writes 19 into warchestTrailProgress instead of extremeTrailProgress.
             */
            void __cdecl MenuView_CrusadeMap_Prepare();

            /**
             * Per-frame handler of the Crusader Trail map: plays the 'Afraid?' taunt (ri_kick_player_01.wav) 1 s
             * after a mission was skipped (DWORD_00ed311c set by the skip handler); for the current trail type
             * draws, for every reached mission, its icon (variant from trailIconFrameOffset) at the trail's map
             * position, or the chicken sprite from trailChickenSprite for skipped missions (months == -1200), the
             * animated lord marker at the current mission (intro animation while g_trailLordIntroAnimActive > 0,
             * then the frame table trailLordMarkerAnimFrames) and an animated marker at the next/furthest mission;
             * then prints mission number, trail name, start year and the reached month/year, plus 'Crusader Trail
             * Completed!' when furthest mission == 50/30/30. Original bug: the Extreme branch compares
             * furthestExtremeTrailMission with 30 although that trail has 20 missions (progress capped at 19,
             * furthest = progress+1), so the caption never appears there (machine code: 0x4DF28C cmp dword
             * [0x1FE9E54],0x1E; furthestExtremeTrailMission is only written as progress+1 at 0x4DC789 and
             * incremented while < 0x13 at 0x4D8FF9, so it never exceeds 20 unless loaded from a modified file).
             */
            void __cdecl MenuView_CrusadeMap_DoEveryFrame();

        } // namespace CrusadeMap
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
