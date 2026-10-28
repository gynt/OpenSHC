/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/SoundSystem.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "Mss32.h"
#include "WinDef.h"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::DE::SHCDE::eMusicIDs;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0000328C
        class SoundSystem {
        public:
            // [036 0x00479F30] cleared when sound is disabled from the menu; playSound refuses to start samples
            // when 0
            DWORD sfxEnabled; // 0x00000000 length: 4
            HDIGDRIVER digSndDriver_0x4; // 0x00000004 length: 4
            // [036 0x0047A690] cleared after AIL_shutdown; every audio function bails out when it is FALSE
            BOOLEnum soundSystemInitialized; // 0x00000008 length: 4
            // 0 -> music; 2 -> SFX; 3, 4 -> speech
            HSTREAM stream_0xc[5]; // 0x0000000C length: 20
            // [UNK PASS] was streamActiveUnk_0x20
            int streamOpen[5]; // 0x00000020 length: 20
            // The one used by the music stream seems to indicate how tp continue with the stream instead? [UNK
            // PASS] was streamFlagsUnkAndLoopCount_0x34
            SoundFlagsAndLoopCount streamFlagsAndLoopCount[5]; // 0x00000034 length: 20
            // [036 0x00479B70] element 0 is re-applied as the music file volume when speech ends, while
            // streamFileVolumeCurrentUnk_0x5c holds the currently applied value
            int streamUnduckedFileVolume[5]; // 0x00000048 length: 20
            // [UNK PASS] was streamFileVolumeCurrentUnk_0x5c
            int streamAppliedFileVolume[5]; // 0x0000005C length: 20
            int streamVolume[5]; // 0x00000070 length: 20
            // [UNK PASS] was currIdSoundFilenameUnk_0x84
            char currentMusicFilename[200]; // 0x00000084 length: 200
            // [037 0x0047B250] multiplies every music file volume /100; initialised to 100 in initMiles
            int musicVolumeScalePercent; // 0x0000014C length: 4
            // [UNK PASS] was currIdSoundFileVolumeUnk_0x150
            int currentMusicFileVolume; // 0x00000150 length: 4
            // [036 0x0047A2A0] values 1/2 switch between fade phases; set to 2 together with a timeGetTime() start
            // stamp
            dword musicFadeState; // 0x00000154 length: 4
            // [036 0x0047A2A0] timeGetTime() stamp taken when fade state changes
            dword musicFadeStartTime; // 0x00000158 length: 4
            int streamPaused_0x15c[5]; // 0x0000015C length: 20
            // [UNK PASS] was musicSampleUnk_0x170
            HSAMPLE musicSample; // 0x00000170 length: 4
            // [036 0x0047A790] file read to fill the music sample buffers
            int currentMusicFileHandle; // 0x00000174 length: 4
            // [036 0x0047A790] replaces the current handle on EOF and is reset to -1
            int queuedMusicFileHandle; // 0x00000178 length: 4
            // [UNK PASS] was sampleBufferPtrUnk_0x17c
            void* musicSampleBuffers[2]; // 0x0000017C length: 8
            // [UNK PASS] was sampleBufferSizeUnk_0x184
            int musicSampleBufferSize; // 0x00000184 length: 4
            // [037 0x0047B060] set to 0 when the music stream starts and 1 by endSoundStream; openSound queues the
            // next file only while it is 0
            dword musicStreamStopped; // 0x00000188 length: 4
            HSAMPLE sample[32]; // 0x0000018C length: 128
            int sampleSoundIndex_0x20c[32]; // 0x0000020C length: 128
            int soundFileCurrSampleNum_0x28c[1000]; // 0x0000028C length: 4000
            void* soundFileDataPointerArray_0x122c[1000]; // 0x0000122C length: 4000
            int soundFileSizes_0x21cc[1000]; // 0x000021CC length: 4000
            int loadedSoundsCountAndIndex_0x316c; // 0x0000316C length: 4
            int sampleVolume; // 0x00003170 length: 4
            int sampleSndStructVolumePercentage_0x3174[32]; // 0x00003174 length: 128
            int samplePaused_0x31f4[32]; // 0x000031F4 length: 128
            // [036 0x0047A5E0] compared against music ids 0xF/0x32/0x48 and the oud (0x49..0x60) / flute (>=0x61)
            // ranges; zeroed when music ends
            int playingMusicId; // 0x00003274 length: 4
            // [601 0x0047B890] when it differs from playingMusicId and > 0 its musicFile is started and it becomes
            // playingMusicId
            int pendingMusicId; // 0x00003278 length: 4
            // [UNK PASS] was currentSoundIDVolumeUnk_0x327c
            dword pendingMusicVolume; // 0x0000327C length: 4
            // [037 0x0047B890] when 1, starting the pending track sets fade state 1 (fade-in) and clears it
            dword fadeInNextTrack; // 0x00003280 length: 4
            // [UNK PASS] was lastUsedSpeechStreamUnk_0x3284
            int lastUsedSpeechStream; // 0x00003284 length: 4
            // [037 0x0047B890] timeGetTime() when music ended; next peace tune starts after field4_0x4c4[idx] ms
            dword peaceMusicPauseStartTime; // 0x00003288 length: 4

        private:
            SoundSystem(SoundSystem const&);
            void operator=(SoundSystem const&);

        public:
            SoundSystem() {};
            ~SoundSystem() {};

            /**
             * Clears the loop/flag entries of stream slots 3 and 4 and ends both speech sound streams (SPEECH_1,
             * SPEECH_2).
             */
            void endSpeechStreamsAndResetLoopFlags();

            /**
             * Ends the music sound stream and clears two music-related state fields (mbr_0x154,
             * sec_Section1055_0x3274).
             */
            void stopMusicPlayback();

            /**
             * NAME? Ends both speech sound streams (SPEECH_1, SPEECH_2); 'endSpeechStreams' would describe it.
             */
            void endSpeechStreams();

            /**
             * Stops one sound stream. For SND_STR_MUSIC it ends the streamed music sample, closes the current and
             * queued music file handles (resets both to -1) and clears the playing-music id; for other streams it
             * closes the MSS stream unless flag bit 31 is set and the stream is still playing (status 4).
             */
            void endSoundStream(SHC_SoundStream sndStreamIndex);

            /**
             * Returns TRUE if the given stream is active and currently playing (MSS status 4 = SMP_PLAYING). Stream
             * 0 (music) is checked via the music HSAMPLE, others via their HSTREAM.
             */
            BOOLEnum isSampleOrStreamPlaying(SHC_SoundStream streamIndex);

            /**
             * NAME? Returns TRUE when speech stream 1 or 2 is currently playing, FALSE if not or if the local
             * player's playerDeathRelated flag is set. Callers use it to suppress new advisor speech while another
             * is playing (effectively isSpeechPlaying).
             */
            BOOLEnum shouldSoundXNotBePlaying();

            /**
             * Sets a stream's file-relative volume (percent) and applies streamVolume[i]*volumeParam/100 to the MSS
             * sample (music) or stream; remembers volumeParam in streamFileVolumeCurrentUnk_0x5c. No-op if the
             * stream is not active.
             */
            void setStreamFileVolume(SHC_SoundStream sndStreamIndex, int volumeParam);

            /**
             * For speech streams 3 and 4: if the 'music ducked' flag (bit 0x20000000) is set and the speech stream
             * has stopped playing, clears the flag and restores the music sample volume to
             * streamVolume[0]*streamFileVolumeNextUnk_0x48[0]/100.
             */
            void restoreMusicVolumeAfterSpeechEnds();

            /**
             * Loads a WAV file fully into memory via AIL_file_read, stores the data pointer and size in the next
             * slot (loadedSoundsCountAndIndex_0x316c) and returns that slot index, incrementing the counter;
             * returns -1 if the sound system is off or the read failed.
             */
            int loadSoundFileAndGetIndex(char* fileName);

            /**
             * If the sound has no sample slot yet, counts occupied sample slots 1..31 into
             * DAT_NumberOfUsedSoundSamplePlaces, then assigns the first free slot to soundIndex
             * (sampleSoundIndex_0x20c[slot]=soundIndex, soundFileCurrSampleNum_0x28c[soundIndex]=slot). Does
             * nothing if all 31 slots are busy.
             */
            void assignFreeSampleSlotToSound(int soundIndex);

            /**
             * Configures the sample slot assigned to soundIndex: stores the volume percentage in
             * sampleSndStructVolumePercentage_0x3174[slot], sets volume sampleVolume*pct/100, pan = samplePan and
             * loop count 1. (The decompiled call shows soundIndex as the pan argument, but the machine code pushes
             * the 3rd stack argument samplePan - decompiler artefact, not a game bug.)
             */
            void setupSampleForNextSound(int soundIndex, int sampleVolumePercentage, int samplePan);

            /**
             * Returns TRUE if the sample slot of soundIndex is still playing; otherwise frees the slot
             * (sampleSoundIndex_0x20c[slot]=0, soundFileCurrSampleNum_0x28c[soundIndex]=-1) and returns FALSE.
             */
            BOOLEnum getAndUpdateSampleStatus(int soundIndex);

            /**
             * Starts playback of a preloaded WAV: binds the in-memory file data/size of soundIndex to its assigned
             * sample slot (AIL_set_named_sample_file) and starts the sample. Requires sound on and a slot assigned.
             */
            void playSound(int soundIndex);

            /**
             * Volume slider handler. streamIndex -1 sets the master SFX sample volume and re-applies it to all 31
             * sample slots scaled by each slot's volume percentage; otherwise stores streamVolume[streamIndex] and
             * re-applies it to the active stream (music via sample, others via AIL_set_stream_volume scaled by the
             * file volume).
             */
            void setStreamOrSfxVolume(int streamIndex, int volume);

            /**
             * Turns sound off from the options menu: clears bit 31 of every stream flag word and ends all 5
             * streams, ends all 31 SFX samples and frees their slots, resets each loaded sound's slot to -1 and
             * clears soundActiveUnk_0x0.
             */
            void turnSoundOff();

            /**
             * NAME? Pauses all audio (window deactivation): for each of the 5 streams records whether it was
             * playing in streamPaused_0x15c and stops/pauses it; for each loaded sound whose sample is playing
             * marks samplePaused_0x31f4[slot] and stops the sample. Effectively pauseAllAudio.
             */
            void pauseAudioSample();

            /**
             * NAME? Resumes audio paused by pauseAudioSample (window re-activation): resumes streams flagged in
             * streamPaused_0x15c (music sample via AIL_resume_sample, others via AIL_pause_stream(..,1)), then for
             * each loaded sound with an assigned slot resumes its sample. Original-game bug: the paused test reads
             * samplePaused_0x31f4[soundIndex] while pauseAudioSample set samplePaused_0x31f4[slot] (and the clear
             * uses [slot]), so paused SFX are mostly not resumed and soundIndex >= 32 reads past the 32-entry
             * array.
             */
            void resumeAudioSample();

            /**
             * NAME? Resets music/battle-music state when a map is loaded or a game starts: Section1079 mode=1,
             * random 0..3 values for field1_0x4 and incrementorUpTo4 (1..4), clears battle levels, cow-poison
             * tracker, troop-value attack counters and the mood-tune counter; stamps the sound match time.
             * Effectively resetMusicStateForNewGame.
             */
            void mapLoadingAndLaunchGameRelated1();

            /**
             * Selects the next music track: MUSIC_TUNE_NARR1 acts as 'mission music' and maps to the mission-
             * specific tune (missionNumber1to20 + MUSIC_TUNE_LOSE2) or MUSIC_TUNE_OFF. If different from the
             * current id, stores it in currentSoundID_0x3278 (started later by playRandomAmbientMusic), computes
             * its volume as fileVolume*100/127 and clears the fade-in request flag mbr_0x3280.
             */
            void setupVolumeAndSoundID(eMusicIDs soundID);

            /**
             * Same as setupVolumeAndSoundID but the target volume is fileVolume*soundMultiplier/127 instead of
             * *100.
             */
            void setupVolumeAndSoundIDWithMultiplier(eMusicIDs soundID, int soundMultiplier);

            /**
             * NAME? Sets SoundSystem.fadeInNextTrack = 1: when playRandomAmbientMusic next starts the selected track it
             * switches to fade state 1 (20 s fade-in from silence) and clears the flag; setupVolumeAndSoundID also
             * clears it. Effectively requestFadeInForNextTrack.
             */
            void requestFadeInForNextTrack();

            /**
             * Starts the music fade-out (mbr_0x154 = 2, 1 s ramp in playRandomAmbientMusic) and records the start
             * time in someSoundTime_0x158. If a fade-in (state 1, 20 s ramp) was in progress, the start time is
             * back-dated by the fade-in progress percent (p% -> start = now - p*10 ms - 1). No-op if no music is
             * playing or it is already fading out.
             */
            void setSomeSoundTime();

            /**
             * Selects MUSIC_TUNE_HAPPY2 at 100% volume and, if some music other than id 0xF is playing, starts
             * fading it out.
             */
            void setupVolumeAndSoundID0xF0_100();

            /**
             * Chooses the next peace-time music. Rolls 0..4 (in Solitary mode, with population > 49 or in a
             * campaign mission), otherwise 0..3; on non-zero a coin flip picks either a flute chain (odd: random
             * 0..18 + MUSIC_FLUTE1, 0..3 follow-ups) or an oud chain (even: random 0..23 + MUSIC_OUD1, 0..3 follow-
             * ups). On zero: population < 50 picks a random mood tune (MAIN/AVG2-or-GOOD/GOOD/AVG/SAD2), otherwise
             * cycles HAPPY/HAPPY2/HAPPY3 and increments the mood-tune counter.
             */
            void selectAndPlayMoodBasedMusic();

            /**
             * Setter for SoundEffectsHelperData1.SEC_Section1079.field7_0x1c; a non-zero value prevents
             * playBattleGloryMusicIfConditionsMet from switching to the glory battle tune.
             */
            void setSection1079_28_4_(int suppressGloryMusic);

            /**
             * While in battle-music mode (Section1079.field0_0x0 == 5) with a non-zero troop-value level, no glory
             * track started yet, variant != 1 and not suppressed: marks the glory track as started, fades out the
             * current music and selects MUSIC_TUNE_BATTLE_L2_GLORY1.
             */
            void playBattleGloryMusicIfConditionsMet();

            /**
             * Credits music chaining: if DAT_CreditsAfterCampaignEnd == 1 opens track 0x26; else if the playing music is not 0xF
             * selects MUSIC_TUNE_OFF; otherwise opens track 0x10 and clears the playing-music id.
             */
            void playDarMehqOrGlory();

            /**
             * Selects victory music MUSIC_TUNE_WIN1 + DAT_WinMusicVariation at 100% and advances the variation,
             * cycling 0..2.
             */
            void playWinMusicVariation();

            /**
             * Selects defeat music MUSIC_TUNE_LOSE1 + DAT_LossMusicVariation at 100% and toggles the variation
             * between 0 and 1.
             */
            void setupLossMusic();

            /**
             * Shuts down audio: stops Bink playback, kills the multimedia timer, ends all streams, ends and
             * releases all 31 sample handles, frees every loaded WAV buffer and both music stream buffers, releases
             * the music sample, closes the digital driver, calls AIL_shutdown and clears waveOutOpenUnk_0x8.
             */
            void shutdownSoundSystem();

            /**
             * NAME? Music streaming callback (runs on the MSS timer thread): refills the ready double-buffer of the
             * music sample from the current music file. On EOF it picks the next track (oud/flute follow-ups,
             * mission intro tunes, credits), then switches to the queued file handle, loops from file start, or
             * stops music, before loading the buffer with AIL_load_sample_buffer. Effectively
             * refillMusicStreamBuffer.
             */
            void refillMusicStreamBuffer();

            /**
             * NAME? Stops speech and SFX only: clears bit 31 of speech stream flags, ends speech streams 3/4, ends
             * all 31 SFX samples and resets every loaded sound's sample slot to -1. Music and ambient streams keep
             * playing.
             */
            void stopAllActiveSounds();

            /**
             * Same as stopAllActiveSounds but also sets the SFX stream 1/2 flag words to 1 (loop count 1, so they
             * stop after the current pass): ends speech streams and all SFX samples.
             */
            void endSpeechSoundStreams();

            /**
             * NAME? Enters battle-music mode (Section1079 mode 5) unless already in it, storing battleLevel as
             * troopValueLevel. Level != 2: sums the troop value of all players except the local one
             * (DAT_Music_TotalTroopValue): < 100 -> BATTLE1A/2A/3/4/BATTLE by the rotating incrementorUpTo4, >= 250
             * -> BATTLE2B, in between -> BATTLE2A or BATTLE_L1A. Level 2: mostly BATTLE_L2_GLORY1 (ending the
             * current music) or BATTLE_L1A, outside Solitary mode a 0..4 roll may instead pick BATTLE1A/2A. Fades
             * out playing music first. Effectively startBattleMusic.
             */
            void playRandomMusic02(int battleLevel);

            /**
             * Called when a battle is over (no enemies left / battle level dropped). Outside editor and Siege-That,
             * if in battle-music mode (Section1079 mode 5) and not yet ended: marks the battle as ended
             * (field6_0x18 = 1) and transitions music - fade out back to peace mode (mode 1), or in Solitary mode
             * play the battle-end sting MUSIC_TUNE_BATTLE_L1D or a victory tune (WIN1..3), followed by
             * playVictoryMusic678 (which plays a victory speech line, not music).
             */
            void handleBattleEndMusicTransition();

            /**
             * Core stream starter. Flag 0x40000000 first overwrites the stream's flag word with 1 (clearing the
             * bit-31 'protected' flag so endSoundStream will close it even while playing); then ends the stream
             * and, if sound is enabled, input is processed and the window focused, opens the file. Music (stream 0)
             * uses the double-buffered music sample at 22050 Hz (push 0x5622; the decompiler shows it as _Filename
             * - the file actually opened is the filename argument, _O_BINARY) fed by two playMusicUnk calls; other
             * streams use AIL_open_stream. Flag 0x20000000 ducks music to half volume; bits 30/31 force loop count
             * 1, otherwise the low 16 bits are the loop count.
             */
            void startSoundStream(
                SHC_SoundStream sndStreamIndex, char* filename, SoundFlagsAndLoopCount flagsAndLoopCount);

            /**
             * Copies filename into currIdSoundFilenameUnk_0x84, looks up its per-file volume, sets the music target
             * volume to mbr_0x14c*fileVolume/100 (starting at 0 if a fade-in is pending) and starts it on the music
             * stream with loop count 0 (endless).
             */
            void playMusicFileByName(char* filename);

            /**
             * NAME? Like playMusicFileByName but scales the file volume by someVolumeUnk percent; starts the music
             * stream with loop count 0 (loops endlessly). Effectively playMusicLooped(filename, volumePercent).
             */
            void playMusicFileByNameWithVolume(char* filename, int someVolumeUnk);

            /**
             * NAME? Same as playOrSetupMusicUnk but starts the music stream with loop count 1 (plays once, then
             * playMusicUnk picks what follows). Effectively playMusicOnce(filename, volumePercent).
             */
            void playMusicOnceWithVolume(char* filename, int volume);

            /**
             * Switches music to filePath. If the music stream is currently running (mbr_0x188 == 0) it only opens
             * the file as the queued handle musicFileHandle_0x178 so playMusicUnk splices it in at the next buffer
             * boundary (gapless); otherwise starts it via playMusicFileByName. field14_0x54 is held TRUE around the
             * file operations.
             */
            void openSound(char* filePath);

            /**
             * Plays filename once on SFX stream 1 with its per-file volume and flags 0x80000001 (bit 31 = protected
             * while playing, loop count 1).
             */
            void playSoundOnSfxSoundStream1OnceUninterruptible(char* filename);

            /**
             * Plays filename once (flags 1) on SFX stream 2. It stores the per-file volume into
             * streamFileVolumeNextUnk_0x48[1] (stream 1's slot, verified in machine code), so stream 2 starts with
             * the volume its caller playAmbientSoundStream2Unk put into slot [2] (ambient-table volume); the store
             * into [1] is harmless because every stream-1 start rewrites [1] first.
             */
            void playSoundOnSoundStream2(char* filename);

            /**
             * Plays a speech file at volume 100 on alternating speech streams 3/4 (round-robin via
             * lastUsedSpeechStream), ending whatever was on that stream. Skipped if stream 3 is protected (bit 31)
             * and still playing, and in the Crusader tutorial.
             */
            void playSoundOnSpeechStream(char* filename);

            /**
             * Same as playSoundOnSpeechStream but uses the file's own volume and a separate round-robin counter
             * DAT_SFXDefinedData.speechStreamRoundRobin to alternate between speech streams 3 and 4.
             */
            void playSpeechSfx(char* soundFileName);

            /**
             * NAME? Plays tutorial narration: ends the stream DAT_SFXDefinedData.tutorialSpeechStreamIndex, sets speech volume
             * 100 and plays param_1 with flags 0x20000001 (duck music to half, play once), or plain play-once on
             * the unused Extreme-ad view. Not ambient and not looping - effectively playTutorialSpeech.
             */
            void playAmbientStreamWithLoop(char* filename);

            /**
             * Copies filename into currIdSoundFilenameUnk_0x84, computes music volume mbr_0x14c*fileVolume/100 and
             * starts it on the music stream with the given flags/loop count.
             */
            void playMusicFile(char* filename, SoundFlagsAndLoopCount flagsAndLoop);

            /**
             * Plays soundFileName on SFX stream 1 with its per-file volume and the given flags/loop count.
             */
            void playSoundOnSfxSoundStream1(char* soundFileName, SoundFlagsAndLoopCount flagsAndLoopCount);

            /**
             * Plays filename on SFX stream 2 with the given flags/loop count. Like playSoundOnSoundStream2 it
             * writes the per-file volume into stream 1's slot (streamFileVolumeNextUnk_0x48[1]); stream 2 therefore
             * uses the volume the caller set in slot [2].
             */
            void playSoundOnSfxSoundStream2(char* filename, SoundFlagsAndLoopCount flagsAndLoopCount);

            /**
             * Plays filename on speech stream 1 (index 3) with its per-file volume (also copied to stream 4's slot)
             * and the given flags; records stream 3 as last used speech stream. Used for videos, taunts and
             * campaign intro/outro narration.
             */
            void playSoundOnSpeechStream1(char* filename, SoundFlagsAndLoopCount flagsAndLoopCount);

            /**
             * Sound re-enabled from the options menu: sets soundActiveUnk_0x0 = 1 and restarts the last music file
             * (currIdSoundFilenameUnk_0x84) with its saved flags.
             */
            void enableSoundAndRestartMusic();

            /**
             * NAME? Per-frame music manager: plays 'walls breached' / 'enemy inside castle' warnings, samples
             * combat activity every 200 ticks, runs music fade-out (1 s) / fade-in (20 s), starts the pending track
             * (looped or once), detects battle start/end (SP: enemy units + troop values; MP: battle-level
             * thresholds) and switches battle music, and after a pause from a 6-entry table starts the next mood-
             * based peace tune. Effectively updateMusic.
             */
            void updateMusic();

            /**
             * NAME? Called by playMusicUnk when the current music file hits EOF during battle mode: chooses the
             * next battle music segment from SFX table entries 0x17..0x29 depending on troop-value level, variant
             * and segment counter. In intense battles it picks randomly among allowed transitions
             * DAT_SFXDefinedData.battleMusicSegmentTransitions[current][next]: segment 4 gets weight 6, segments whose mood
             * (field3_0x4a4, 1/2) equals the battle balance field6_0x34 are excluded, those with the opposite mood
             * get weight 2, others weight 1. Leaves battle mode when the battle has ended or no game view is
             * active. Effectively queueNextBattleMusicSegment.
             */
            void queueNextBattleMusicSegment();

            /**
             * Initialises Miles: startup, opens waveOut 44.1 kHz/16-bit stereo (success -> waveOutOpenUnk_0x8),
             * hands the driver to Bink, allocates 32 sample handles and the music sample with two >=64 KB stream
             * buffers, resets 1000 sound slot entries to -1, music handles to -1, and installs a 50 ms multimedia
             * timer (SndSystemTimeCallback, 3 ms resolution).
             */
            void initMiles();
        };

        static_assert_cpp98_obj(sizeof(SoundSystem) == 12940, SoundSystem);

#pragma pack(pop)

    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
