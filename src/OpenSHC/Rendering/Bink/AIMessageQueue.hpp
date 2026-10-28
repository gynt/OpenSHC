/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/AIMessageQueue.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000930
        class AIMessageQueue {
        public:
            // Unsigned Double-Word (ddw, 4-bytes)
            BOOLEnum messagePlaying_0x0; // 0x00000000 length: 4
            // [177 0x004B7C90] 0 selects wide-string (LPWSTR) text rendering, otherwise char text rendering; set to
            // 1 by playEventVideoBik/prepareSFXandVFX Unsigned Double-Word (ddw, 4-bytes)
            dword textIsNarrow; // 0x00000004 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            char* currentMessageText_0x8; // 0x00000008 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            char currentMessageVfxFile_0xc[100]; // 0x0000000C length: 100
            // Unsigned Double-Word (ddw, 4-bytes)
            char currentMessageSfxFile_0x70[100]; // 0x00000070 length: 100
            // [177 0x004B7C90] indexes DAT_PlayerNames/currentAIArray and portrait icon 0x222+index when > 0
            // Unsigned Double-Word (ddw, 4-bytes)
            dword senderPlayerIndex; // 0x000000D4 length: 4
            // [177 0x004B7C90] timeGetTime at message start, compared with 10000 ms timeout Unsigned Double-Word
            // (ddw, 4-bytes)
            dword messageStartTime; // 0x000000D8 length: 4
            char* savedMessageTextPtr_0xdc[10]; // 0x000000DC length: 40
            // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was savedMessageUnknownValue_0x104
            int savedMessageTextIsNarrow_0x104[10]; // 0x00000104 length: 40
            // Unsigned Double-Word (ddw, 4-bytes)
            char savedMessageVfxFile_0x12c[10][100]; // 0x0000012C length: 1000
            // Created by retype action
            char savedMessageSfxFile_0x514[10][100]; // 0x00000514 length: 1000
            // Created by retype action [UNK PASS] was savedMessageUnknownValue2_0x8fc
            int savedMessageSenderPlayerIndex_0x8fc[10]; // 0x000008FC length: 40
            // Unsigned Double-Word (ddw, 4-bytes)
            int storedMessages_0x924; // 0x00000924 length: 4
            // [177 0x004B7AF0] set to currentMessageUnknownValue2_0xd4 (sender player) when a message is shown,
            // cleared when it closes Unsigned Double-Word (ddw, 4-bytes)
            dword displayedSenderPlayer; // 0x00000928 length: 4
            // [177 0x004B7C90] set to 1 when SND_STR_SPEECH_1 is no longer playing; blocks closing of a video-less
            // message while 0 Unsigned Double-Word (ddw, 4-bytes)
            dword speechFinished; // 0x0000092C length: 4

        private:
            AIMessageQueue(AIMessageQueue const&);
            void operator=(AIMessageQueue const&);

        public:
            AIMessageQueue() {};
            ~AIMessageQueue() {};

            /**
             * Starts displaying the current AI/event message: copies the VFX and SFX file names into
             * currentMessageVfxFile_0xc / currentMessageSfxFile_0x70, opens the AI-lord-message modal, and if a VFX
             * name is set marks isBinkVideoPlaying and plays it in Bink slot 1 at a fixed offset inside the menu
             * (switching away from siege-tent build tabs first). If a speech file is set it resolves it
             * (FRT_GFX_SPEECH), stops both speech streams, plays it and, when a video is running and SPEECH_1
             * plays, links the video to that stream. Sets messagePlaying_0x0 and records the start time.
             */
            void playVideoOverMap(char* binkFileName, char* sfxFileName);

            /**
             * NAME? it does not play anything: modal render callback for the AI lord message (only while in game
             * view). Draws the message text (wide or narrow string) and, for a positive sender player index, the
             * sender's name plus portrait and human/AI personality icon, right/bottom-aligned at (anchorX, anchorY)
             * with Y offsets for open menu tabs / display element 0x14. It only polls the speech stream (sets
             * speechFinished when SND_STR_SPEECH_1 is no longer playing). Once 10 s have passed or the text
             * measures zero width it closes the modal (displayedSenderPlayer=0, countdown=2, unless paused) as soon
             * as the video (if any) has closed, or - without video - the speech has finished (or sound is off).
             */
            void renderAiLordMessageModal(int anchorX, int anchorY);

            /**
             * Shows an event message with optional video and speech: plays it immediately via playVideoOverMap
             * (sender index 0) if no message is active, otherwise appends it to the 10-entry stored message queue
             * (dropped when full).
             */
            void playEventVideoBik(char* messageText, char* vfxFileName, char* sfxFileName);

            /**
             * Same as playEventVideoBik but with a sender player index: plays the message now if none is active,
             * otherwise queues text, VFX/SFX names and sender index in the next of 10 stored slots. NAME? it queues
             * or plays a message, not just prepares SFX/VFX.
             */
            void prepareSFXandVFX(char* messageText, char* messageVfxFile, char* messageSfxFile, int senderPlayerIndex);

            /**
             * Ends the current message (stops Bink slot 1 if it had a video, clears current message fields,
             * countdown=2) and, if messages are queued, plays the first stored one and shifts the remaining queue
             * entries (text ptr, flags, VFX/SFX names, sender) down by one. Returns TRUE if a stored message was
             * started.
             */
            BOOLEnum playNextStoredAIMessage();

            /**
             * Queues an AI lord speech message: for aiType 1..16 and messageType 1..33 first queues an empty-text
             * entry with an AI-specific sound file (field92_0x170[aiType-17]) and the sender player (name/portrait
             * shown), then the message text (text group entry (aiType-1)*34+messageType) with VFX/SFX names from
             * DAT_MissionAestheticsDefinedData tables and the negated player index (no name/portrait).
             */
            void playBikVideoFromPlayer(int playerIndex, int aiType, int messageType);

            /**
             * Flushes the AI message queue: if a message is playing ends it (which may start the first stored one)
             * and then clears the stored message count. Called on map load/launch and load/save.
             */
            void playNextStoredBinkVideo();
        };

        static_assert_cpp98_obj(sizeof(AIMessageQueue) == 2352, AIMessageQueue);

#pragma pack(pop)

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
