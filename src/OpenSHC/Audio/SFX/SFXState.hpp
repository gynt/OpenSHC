/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/SFXState.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/AmbientSFXType.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Audio/SFX/SoundStructure1.hpp"
#include "OpenSHC/Audio/SFX/SoundStructure2.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using OpenSHC::Audio::SFX::AmbientSFXType;
        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Audio::SFX::SoundStructure1;
        using OpenSHC::Audio::SFX::SoundStructure2;
        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Units::UnitType;

#pragma pack(push, 1)

        // SIZE: 0x00008E90
        class SFXState {
        public:
            int DAT_SFXCounter1; // 0x00000000 length: 4
            int highestSFXCounter; // 0x00000004 length: 4
            // [039 0x0044AE90] holds the raw malloc'd contents of fx\volume.txt, parsed in place; filename pointers
            // into it are stored elsewhere
            char* volumeFileBuffer; // 0x00000008 length: 4
            char* DAT_SoundFileNamePointersArray[1000]; // 0x0000000C length: 4000
            int DAT_SoundVolumeArray[1000]; // 0x00000FAC length: 4000
            int DAT_SoundTotalCount; // 0x00001F4C length: 4
            SoundStructure1 DAT_SoundStructures[1000]; // 0x00001F50 length: 24000
            SoundStructure2 DAT_SoundStructures2[270]; // 0x00007D10 length: 4320
            int ambientEventCounters[10][4]; // 0x00008DF0 length: 160

        private:
            SFXState(SFXState const&);
            void operator=(SFXState const&);

        public:
            SFXState() {};
            ~SFXState() {};

            // Constructor
            /**
             * SFXState constructor (thiscall, returns this): resets all 1000 sound request entries (counter 0,
             * volume 100, pan 0x40), clears DAT_SFXCounter1 and the ambient counters, sets highestSFXCounter = 0
             * (EDX was zeroed before the loop and the resetAmbientEventCounters callee does not touch it; Ghidra's
             * extraout_EDX is an artefact) and resets the Genie speech feedback state.
             */
            SFXState* Constructor_SFXState();

            /**
             * Frees the sound filename array buffer (DAT_SoundFileNameArrayMemoryPointer) if allocated; used by the
             * SFXState destructor.
             */
            void freeMemoryAt();

            /**
             * Loads all SFX WAVs from a table of 270 groups x 8 variant names (1000 chars each). For each group:
             * counts names until 'Null.wav', loads each variant with loadSoundFileAndGetIndex, sets variationCount,
             * soundID (index of first variant) and each sound's filename pointer, then advances the loading bar.
             */
            void loadWavSounds(char* wavNameTable);

            /**
             * NAME? Schedules the next round-robin variant of SFX group sfxOffsetInArray for playback at its base
             * volume, centre pan (0x40); increments the per-sound request counter and the frame SFX counter
             * (tracking its maximum). Effectively scheduleSFX.
             */
            void scheduleSFX(SoundEffectID sfxOffsetInArray);

            /**
             * Like setUpSFXToPlayUnk but with an explicit volume: schedules the next round-robin variant of group
             * unknownSfxID at volumePercentage clamped to 0..127, centre pan.
             */
            void setSoundWithVariation(int unknownSfxID, int volumePercentage);

            /**
             * Schedules a specific variant (variationIndex, range-checked) of SFX group sfxGroupID at its base
             * volume with centre pan.
             */
            void scheduleSFXVariation(int sfxGroupID, int variationIndex);

            /**
             * Positional SFX: takes the tile offset from the viewport centre, rotates it by map orientation and,
             * only if inside the audible diamond, schedules the next variant with pan = 2*(x-y)+62 clamped 0..127
             * and volume reduced by 2% per tile of distance (max 70% reduction).
             */
            void playSFXAtLocation(int xPosition, int yPosition, eSFX sfxOffsetInArray);

            /**
             * Like playSFXAtLocation but without range check or distance attenuation: schedules the next variant at
             * base volume with stereo pan from the rotated offset to the viewport centre.
             */
            void playSFXAtLocationFullVolume(int xPosition, int yPosition, int sfxOffsetInArray);

            /**
             * Clears all pending SFX play requests after a playback tick: for every loaded sound resets
             * scheduledPlayCounter=0, volume=100, pan=0x40, and zeroes DAT_SFXCounter1.
             */
            void resetScheduledSoundRequests();

            /**
             * Zeroes both entries of the 10 ambientEventCounters pairs (part of the SFXState constructor).
             */
            void Constructor_SFXState_resetAmbientEventCounters();

            /**
             * Increments ambientEventCounters[ambientSoundType][0] (called from map rendering for visible ambient
             * sources) unless the game is paused.
             */
            void notifyAmbientSoundEvent(int ambientSoundType);

            /**
             * If SFX stream 1 is idle, plays the current variant of ambient set ambientSoundIndexUnk on it, then
             * advances the set's cyclic variant index. Battle/heavy ambience is started with loop count 50
             * (playOnSfx1SoundStreamUnk); other types play once with flag 0x80000001. It writes the variant's table
             * volume (or 0x7f in historic intro/picture views) to streamFileVolumeNextUnk_0x48[1], but both callees
             * overwrite that slot with getSoundVolumeForFilename before starting, so the table volume and the 0x7f
             * override are dead stores in the original.
             */
            void playNextAmbientSoundIfStreamIdle(AmbientSFXType ambientSoundIndexUnk);

            /**
             * Stream-2 counterpart: if SFX stream 2 is idle, sets its volume from the current variant of ambient
             * set ambientSoundIndexUnk and plays it (set 5 with loop count 50, others once), then advances the
             * variant index.
             */
            void playNextAmbientSoundIfStream2Idle(int ambientSoundIndexUnk);

            /**
             * Looks up soundFileName (case-insensitive) in the sound filename table and returns its configured
             * volume; 100 if not found.
             */
            int getSoundVolumeForFilename(char* soundFileName);

            /**
             * Plays a unit acknowledgement speech (id < 40): picks the next round-robin variant (consecutive
             * entries of SpeechEffectPathArray), the Arabian or European file depending on historic campaign 2,
             * builds 'fx\speech\<file>' and plays it on a speech stream unless the same file is still playing;
             * remembers it in DAT_LastSpeechSFXFilename.
             */
            void playUnitSpeechEffect(uint speechEffectID);

            /**
             * Plays advisor speech speechID from the 1000-char filename table at 0xA38AF0 via
             * playSoundOnSpeechStream, unless the id is out of range, ids 4..37 in a builder-mode siege map, or the
             * same file is still playing on a speech stream.
             */
            void playSpeechSFX(SpeechEffectID speechID);

            /**
             * Plays fx\speech\<wav_filename> on a speech stream; if it is the same file as last time and still
             * playing it is skipped, except 'buildingwreck_01.wav' which may restart. Records the name in
             * DAT_LastSpeechSFXFilename.
             */
            void playWAVSFX(char const* wav_filename);

            /**
             * Same as playWAVSFX but plays through SoundSystem::playSpeechSfx (per-file volume, separate speech-
             * stream round-robin). Used for attack alarms.
             */
            void playOnSpeechSfxStream(char* filename);

            /**
             * Plays fx\speech\<filename> on a speech stream only if neither speech stream is currently playing;
             * records the name as last speech file.
             */
            void playSpeechSFXFile(char* filename);

            /**
             * NAME? Plays a victory speech line, not music: in single-player (not editor/Siege-That) cycles
             * general_victory6/7/8 ('survived the onslaught' / 'enemy vanquished' / 'castle held firm'), using
             * victory7 when the player has no campground or lord. Effectively playBattleWonSpeech.
             */
            void playVictoryMusic678();

            /**
             * Multiplayer only: says 'We are under attack' (General_Warning10) if 60 s passed since the last call;
             * the cooldown timestamp is refreshed on every call, so the warning only repeats after 60 s without
             * attacks.
             */
            void playSFXWeAreUnderAttack();

            /**
             * NAME? Drives the looping ambience on SFX stream 2: outside game views stops it; otherwise ramps the
             * current ambience (type 7 -> set 5, type 8 -> set 6) in or out by 2*deltaTime per call. When the
             * requested type changes it fades the old loop out to 1% and stops it, then starts the requested one:
             * type 7 fades in from 1%, type 8 starts at its table volume and only after >= 900 accumulated idle
             * time. The third stack parameter currentStreamID is unused (ret 0xc). Effectively
             * updateAmbientLoopStream.
             */
            void tweakVolume(int requestedAmbientType, float deltaTime, int currentStreamID);

            /**
             * Loads fx\volume.txt into a malloc'd buffer (freeing the previous one) and parses it in place: each
             * '"name" N' line stores a lowercased, NUL-terminated filename pointer (in the array 1000 ints before
             * DAT_SoundVolumeArray) and volume N plus the current group offset, clamped to 0..127; a line starting
             * with '-' carries two numbers, the second (negated if directly preceded by '-') becoming the new group
             * volume offset. Then stores the entry count in DAT_SoundTotalCount and sets the volume of all 1000 SFX
             * sound structures and of every ambient/speech variation filename (8 per entry) via
             * getSoundVolumeForFilename.
             */
            void readVolumeFileAndSetupSoundVolumes();

            /**
             * Plays a speech line for a unit type and action ID. Siege engines play playUnitSpeechEffect directly
             * for their select/special actions (e.g. 0, 6, 0xf..0x13); trebuchet/mangonel/ballista with action 6
             * and unhandled unit types play nothing; other units map to a voice column 0..17 (10 = engineer/generic
             * siege). Uses the pre-increment round-robin variation counter of the action entry (the variation index
             * is added to actionID when selecting the filename), builds fx\speech\<file> and plays it on the speech
             * stream unless it equals the last speech file while a speech stream is still playing.
             */
            void playUnitSpeech(UnitType unitType, int actionID);

            /**
             * Loads all WAV sound effects from WavFileGroups[0] (or WavFileGroups[1] when
             * DAT_TextureRenderCoreObject.gmAllowRelativeAliasing is set), then reads fx\volume.txt to assign
             * per-sound volumes. The int parameter is unused.
             */
            void loadSFX(int unusedArg);

            /**
             * Per-tick ambient soundscape state machine: computes a wall-clock fade delta ((now-last)/16 ms, max
             * 20) and accumulates idle time while no ambient stream plays. Outside the in-game views (isInGameView
             * FALSE) it zeroes the 10 ambient event counters and ends the ambient stream; otherwise it
             * copies/rescales and clears them. Calls tweakVolume, advances the fade-in/fade-out of ambient types
             * 5/6, then insertion-sorts ambient types 0..6 by intensity (descending) and, after enough idle time,
             * switches the stream: types 2 and 4 (wind variant by landscape wind) start immediately, 5/6 start with
             * a fade-in; if 5/6 is currently playing it instead starts a fade-out remembering the next type (or -1
             * when its counter dropped to 0).
             */
            void updateAmbientSoundStream();

            /**
             * Multiplayer advisor voice tick (only in the build-menu view, player not dead/lord not killed, not a
             * campaign mission; DAT_GenieFeedbackActive tracks eligibility). At most once per second checks whether the
             * current player's keep became enclosed and plays Genie_45 once. Every 5 minutes (not paused) computes
             * the player's ranking: unchanged rank 1 plays Genie_40, rank improved by more than 2 plays Genie_25
             * (both without storing the new rank), otherwise plays Genie_15..22 for rank 1..8, stores the rank and
             * triggers AI teammate bink messages (team winning / no help) depending on the teams of the top- and
             * lowest-ranked players.
             */
            void updateMultiplayerAdvisorVoices();

            /**
             * Per-tick SFX update: plays multiplayer advisor voices (non-solitary games), restores music volume
             * after speech, updates the ambient stream; every other tick iterates all loaded sounds (0..peasantsArrivingAtCampfire
             * inclusive) and starts those with a pending request that are not playing in a free sample with their
             * volume/pan, then resets scheduled sound requests.
             */
            void updateSoundPlaybackTick();
        };

        static_assert_cpp98_obj(sizeof(SFXState) == 36496, SFXState);

#pragma pack(pop)

    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
