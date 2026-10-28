/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        /**
         * NAME? Not credits-related: stores the given mode in g_leaderboardSortMode and resets
         * g_rankingGamesScrollOffset to 0. switchToMenuView calls it when switching to MVT_RANKING_GAMES, with 2
         * when coming from the lobby and 1 when coming from the crusade map; a better name would be
         * SetRankingGamesListMode.
         */
        void __cdecl SetRankingGamesListMode(undefined4 rankingListMode);

        /**
         * Aborts the running credits/intro script: ends the SFX and both speech sound streams, clears two stream
         * flag/loop entries (streamFlagsUnkAndLoopCount_0x34[3],[4]), stops both Bink players unless DAT_CreditsBackgroundMode
         * == 2, and sets the script command index to the command count so no further commands execute.
         */
        void __cdecl StopCreditsPlaybackAndSounds();

        /**
         * Skips the rest of the current credits/intro segment: stops sound streams and Bink playback (Bink unless
         * DAT_CreditsBackgroundMode == 2), zeroes four segment state globals, invalidates all active credits elements, then
         * increments the command index and advances it until it points at the next segment-end command (0x1F) or
         * the end; for every opcode 0x27 command passed it (re)starts that command's sound stream via
         * setSomeSoundTime/setupVolumeAndSoundID.
         */
        void __cdecl EndCreditsSegmentAndAdvanceToNext();

        /**
         * Clears the whole credits/intro script system: invalidates all active credits elements, zeroes the command
         * count and index, the stored menu-string count and the related state globals.
         */
        void __cdecl ResetCredits();

        /**
         * NAME? Appends credits-script opcode 0x11 (if fewer than 0x120 commands) = set credits background.
         * ProcessCreditsScriptCommands stores arg in DAT_CreditsBackgroundMode (background mode: 0 = screen filled black every
         * frame, 1 = full-screen loaded gfx DAT_CreditsBackgroundGfx drawn at 0,0 via RenderGfxHelperUnk, 2 = no background,
         * used behind a Bink video which is then not stopped) and, only for mode 1, copies the x field
         * (backgroundGfxIndex) into DAT_CreditsBackgroundGfx. Nothing sound-related; the SHC_SoundStreamInt type of the first
         * param is wrong (values 0..2). Better: AppendCreditsBackgroundCommand.
         */
        void __cdecl AppendCreditsBackgroundCommand(undefined4 soundStream, undefined4 backgroundGfxIndex);

        /**
         * Appends a parameterless credits script command with the given opcode (bounded to 0x120 entries).
         */
        void __cdecl AppendCreditsCommand(int opcode);

        /**
         * Appends credits script opcode 0x20 (list terminator).
         */
        void __cdecl AppendCreditsListTerminator();

        /**
         * Appends credits script opcode 0x1C (pause/wait, per the function name).
         */
        void __cdecl AppendCreditsPauseCommand();

        /**
         * Appends credits script opcode 0x1F (segment end; EndCreditsSegmentAndAdvanceToNext skips to it).
         */
        void __cdecl AppendCreditsSegmentEndCommand();

        /**
         * Appends credits script opcode 0x28 (clear image, per the function name).
         */
        void __cdecl AppendCreditsClearImageCommand();

        /**
         * Appends an image command (opcode 5, 6 or 7 only; rejects a negative gfx index) for loaded gfx gfxIndex at
         * (x,y) with drawLayer and hoverGfxIndex = -1, copying width/height from loadedGfxArray; fadeMode is 0 for
         * opcode 5, 1 for 6 and 2 for 7. When executed, 5/6 add an image element (type 1) without / with fade-in,
         * while 7 only uses the id to fade out existing image elements with that gfx index. All callers pass
         * drawLayer 4.
         */
        void __cdecl AppendCreditsImageTransitionCommand(
            int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);

        /**
         * Appends an image-end command (opcode 7 or 0x2A only, non-negative index) referencing loaded gfx index
         * gfxIndex.
         */
        void __cdecl AppendCreditsImageEndCommand(int opcode, int gfxIndex);

        /**
         * NAME? Appends opcode 0x29 (rejected for any other opcode or a negative id) with element id, (x,y),
         * explicit width/height, hoverGfxIndex 0, fadeMode 0 and drawLayer; the 7th argument is ignored. Executed,
         * 0x29 adds a credits element of type 4, which RenderActiveCreditsElements draws as a translucent bordered
         * box (drawBorderedBoxWithBlendedBackground) - not an image; the 'gfxIndex' is only the element id (opcode
         * 0x2A fades it out by id). Only caller: crusade end screen panel behind the victory text (id 0, layer 1).
         */
        void __cdecl AppendCreditsPanelBoxCommand(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        /**
         * Appends credits opcode 0x0C (play Bink video): copies the file name string into the entry (offset 0x3C of
         * the 0x5C-byte command), stores position, Bink player slot and loop flags, field13_0x28 = 0. The first
         * argument is unused.
         */
        void __cdecl AppendCreditsBinkVideoCommand(undefined4 param_1, char* param_2, undefined4 param_3,
            undefined4 param_4, undefined4 param_5, undefined4 param_6);

        /**
         * Appends credits opcode 0x15 (static image) for loaded gfx index at (x,y), width/height from
         * loadedGfxArray, field13_0x28 = 7, transition mode 0.
         */
        void __cdecl AppendCreditsFixedImageCommand(int gfxIndex, undefined4 x, undefined4 y);

        /**
         * Appends credits opcode 0x0D (Bink video with audio): copies the file name into the entry, stores the Bink
         * player slot, flagLoopCount = 1 - param_3, and the volume.
         */
        void __cdecl AppendCreditsBinkVideoWithAudioCommand(
            char* param_1, undefined4 param_2, int param_3, undefined4 param_4);

        /**
         * Appends a credits command with the given opcode and a sound-stream argument.
         */
        void __cdecl AppendCreditsCommandWithArg(int opcode, SHC_SoundStream soundStream);

        /**
         * Appends a text command referencing stored menu string stringIndex (must be
         * 0..DAT_NumberOfStoredMenuStrings-1) at (x,y) with wrap width, font size, black-colour flag (callers draw
         * a black copy offset by +2,+2 as a shadow) and single-line flag; opcode 0xF sets fadeMode 1 (fade-in),
         * 0x10 sets fadeMode 2, others 0.
         */
        void __cdecl AppendCreditsTextCommand(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        /**
         * Appends a text-end command (opcode must be 0x10) for a valid stored string index.
         */
        void __cdecl AppendCreditsTextEndCommand(int opcode, int stringIndex);

        /**
         * NAME? Does not insert at an index: for element type 1 (image: gfx id, hover gfx shown while the mouse is
         * inside unless -1) or 4 (translucent bordered panel box) it takes the first free slot (elementType==0) of
         * CreditsRelatedStructure_ARRAY_00ec0348 and fills elementType, id, hoverGfxIndex, x/y/width/height,
         * fadeState and drawLayer; fadeMode 1 (fade-in) starts fadeLevel at 31.0f, fadeMode 2 at 1.0f, otherwise 0.
         * SIGNATURE: existing param names are wrong - xSpace is the element id, ySpace is x, someX is y, someY is
         * width. Better: addCreditsImageOrPanelElementToFreeSlot.
         */
        void __cdecl addCreditsImageOrPanelElementToFreeSlot(int state, undefined4 xSpace, undefined4 param_3,
            undefined4 ySpace, undefined4 someX, undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9);

        /**
         * For elementType 3 only (credits button: rendered as gfx id, or id+1 while hovered; opcode 0x16 waits for
         * a click on it): fills the first free slot of the active credits element array (elementType=3, fadeLevel
         * 0) with id, x/y/width/height, fadeState and drawLayer. Called for opcode 0x15 with fadeState 0.
         * SIGNATURE: existing param names are wrong - xSpace is the element id, ySpace is x, someX is y, someY is
         * width.
         */
        void __cdecl addCreditsButtonElementToFreeSlot(int param_1, undefined4 param_2, undefined4 param_3,
            undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        /**
         * For elementType 2 (text) only: fills the first free slot of the active credits element array
         * (elementType=2, string id, font size, black-colour flag, x/y/width, single-line flag, drawLayer fixed at
         * 7) and sets fadeLevel to 31.0f (fadeMode 1), 1.0f (fadeMode 2) or 0. SIGNATURE: existing param names are
         * wrong - xSpace is the string id, ySpace is x, someX is y, someY is width.
         */
        void __cdecl addCreditsElementType2ToFreeSlot(int param_1, undefined4 xSpace, undefined4 param_3,
            undefined4 param_4, undefined4 ySpace, undefined4 someX, int param_7, undefined4 someY, undefined4 param_9);

        /**
         * NAME? Used by the historic mission intro, and it reveals text rather than scrolling it: a countdown is
         * decreased by frameTimeScale*timeStep; when it reaches <= 0 the revealed line count is incremented and
         * the countdown gets +100, and once the count exceeds (int)g_textRevealTotalLines the done flag is set. While not
         * done it draws the partially revealed stored text with a blend value taken from the countdown; when done
         * it draws the full stored string g_storedTextFrameStringIndex as multi-line text.
         */
        void __cdecl RenderScrollingCreditsTextFrame(float timeStep);

    } // namespace Credits
} // namespace UI
} // namespace OpenSHC
