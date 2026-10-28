/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MusicControl.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct MusicControl {

        // music state: 1 = normal/peaceful, 5 = battle music sequence active (set by playRandomMusic02, reset to 1
        // on battle end / leaving game)
        int musicMode; // 0x00000000 length: 4
        // rand & 0x80000003 (signed mod 4, -3..3) rolled in mapLoadingAndLaunchGameRelated1; no reader seen
        int randomRollOnMapLoad; // 0x00000004 length: 4
        // [036 0x0047A580] values 1..5 select which battle track is played, not a volume
        int battleMusicVariant; // 0x00000008 length: 4
        // [037 0x0047BF20] counts segments played in the current battle sequence to pick intro/loop tracks
        int battleSegmentCounter; // 0x0000000C length: 4
        int troopValueLevel; // 0x00000010 length: 4
        int incrementorUpTo4; // 0x00000014 length: 4
        // 0 while battle music runs; set 1 once handleBattleEndMusicTransition fired, blocks glory music and battle
        // loop continuation
        int battleEndTransitionDone; // 0x00000018 length: 4
        // set 1 by switchToMenuView when entering build menu on a siege map as attacker (tab forced to stocks), 0
        // otherwise; selects playRandomMusic02(2) and suppresses glory music/battle-end checks
        int siegeAttackerMusicMode; // 0x0000001C length: 4

    } MusicControl;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MusicControl) == 32, MusicControl);
} // namespace Audio
} // namespace OpenSHC
