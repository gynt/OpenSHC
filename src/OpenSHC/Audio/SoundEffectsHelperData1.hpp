/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SoundEffectsHelperData1.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MusicControl.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "mmsystem.h"

namespace OpenSHC {
namespace Audio {

    using OpenSHC::Audio::MusicControl;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
    // SIZE: 0x00000088
    typedef struct SoundEffectsHelperData1 {

        // [036 0x0047A340] set to random 0..3 when an oud track is chosen, decremented per follow-up oud track
        int oudFollowUpTracksLeft; // 0x00000000 length: 4
        // [036 0x0047AB10] sum of playerTotalTroopValueArray over all slots except the local player
        int enemyTotalTroopValue; // 0x00000004 length: 4
        // current player's total troop value, refreshed every 30 s during battle music
        int musicOwnTroopValue; // 0x00000008 length: 4
        MusicControl SEC_Section1079; // 0x0000000C length: 32
        // sum of other players' troop values, refreshed every 30 s during battle music; DAT_Music_TotalTroopValue
        // holds the battle-start value
        int musicEnemyTroopValue; // 0x0000002C length: 4
        undefined4 SND_SomeTimerResolution; // 0x00000030 length: 4
        // 0 = even, 1 = player winning (own% - enemy% >= 21, percentages relative to battle start), 2 = player
        // losing (<= -21); recomputed every 30 s in Solitary mode; reset to 0 when battle music starts; drives
        // battle music segment choice
        undefined4 battleMoodTrend; // 0x00000034 length: 4
        int DAT_NumberOfUsedSoundSamplePlaces; // 0x00000038 length: 4
        // number of mood-based music tracks chosen since map load; when 0, MUSIC_TUNE_AVG2 is skipped
        int moodMusicPlayCount; // 0x0000003C length: 4
        int DAT_RandomVariationCurrentPlayingMusic_01; // 0x00000040 length: 4
        int DAT_SomeSoundTime2; // 0x00000044 length: 4
        int DAT_RandomVariationCurrentPlayingMusic_02; // 0x00000048 length: 4
        // player's troop value when battle music started (min 1); denominator for own-strength percentage
        int musicOwnTroopValueAtBattleStart; // 0x0000004C length: 4
        // random 0..3 count of further MUSIC_FLUTE variations to chain (decremented in playMusicUnk); counterpart
        // of DAT_NegativeCountdownMin1ToMin4Becomes0 for oud tracks
        int fluteFollowUpTracksRemaining; // 0x00000050 length: 4
        // TRUE while main thread opens/closes/ends the music file; SndSystemTimeCallback skips streaming while set
        BOOLEnum musicStreamBusyMainThread; // 0x00000054 length: 4
        // re-entrancy guard set TRUE while SndSystemTimeCallback is servicing the music stream
        BOOLEnum musicTimerCallbackActive; // 0x00000058 length: 4
        // 0..5 cyclic index into SFXDefinedData.musicSilenceIntervalsMs for the gap before the next track
        int musicSilenceIntervalIndex; // 0x0000005C length: 4
        int DAT_WinMusicVariation; // 0x00000060 length: 4
        // 0..2 cycles MUSIC_TUNE_HAPPY/HAPPY2/HAPPY3 for large populations
        int happyTuneRotationIndex; // 0x00000064 length: 4
        int DAT_LossMusicVariation; // 0x00000068 length: 4
        DWORD DAT_enemyInsideCastleSoundWarningCooldownTimer; // 0x0000006C length: 4
        // music id (0x22..0x29) of the last battle-music segment opened; used as 'from' index for segment
        // transitions
        undefined4 currentBattleMusicId; // 0x00000070 length: 4
        WAVEFORMATEX SND_Waveformat; // 0x00000074 length: 18
        undefined1 padding_0x86[2]; // 0x00000086 length: 2

    } SoundEffectsHelperData1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(SoundEffectsHelperData1) == 136, SoundEffectsHelperData1);
} // namespace Audio
} // namespace OpenSHC
