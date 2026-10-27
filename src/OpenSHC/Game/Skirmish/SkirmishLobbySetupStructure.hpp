/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)

        // SIZE: 0x00000108
        class SkirmishLobbySetupStructure {
        public:
            // [045 0x00486C40] stores DAT_GameSynchronyState.skirmishAutoSaveEveryMinutes Unsigned Double-Word
            // (ddw, 4-bytes)
            dword autoSaveEveryMinutes; // 0x00000000 length: 4
            // [045 0x00486C40] stores DAT_GameState.mapAndTime.skirmishFogOfWar Unsigned Double-Word (ddw, 4-bytes)
            dword fogOfWar; // 0x00000004 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            char mapName[80]; // 0x00000008 length: 80
            byte roundTableOrderArray[9]; // 0x00000058 length: 9
            byte playerGroupArray[9]; // 0x00000061 length: 9
            byte slot1Position; // 0x0000006A length: 1
            byte slot2Position; // 0x0000006B length: 1
            byte slot3Position; // 0x0000006C length: 1
            byte slot4Position; // 0x0000006D length: 1
            byte slot5Position; // 0x0000006E length: 1
            byte slot6Position; // 0x0000006F length: 1
            byte slot7Position; // 0x00000070 length: 1
            byte slot8Position; // 0x00000071 length: 1
            undefined1 padding_0x72[2]; // 0x00000072 length: 2
            int currentPlayerSlotID; // 0x00000074 length: 4
            int currentAdvantageBalance; // 0x00000078 length: 4
            // [045 0x00486C40] stores DAT_GameSynchronyState.skirmishGameIntensityType
            int gameIntensityType; // 0x0000007C length: 4
            // [045 0x00486C40] stores DAT_GameSynchronyState.skirmishTechLevel Unsigned Double-Word (ddw, 4-bytes)
            dword techLevel; // 0x00000080 length: 4
            int currentAIArray[9]; // 0x00000084 length: 36
            int aiVariationArray[9]; // 0x000000A8 length: 36
            int playerLordTypeArray[9]; // 0x000000CC length: 36
            // Unsigned Double-Word (ddw, 4-bytes)
            dword mbr_0xf0; // 0x000000F0 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword selectedLordType; // 0x000000F4 length: 4
            dword popularity; // 0x000000F8 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword mbr_0xfc; // 0x000000FC length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword mapSelectionScrollOffset; // 0x00000100 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword mapSelectionRelativeSelected; // 0x00000104 length: 4

        private:
            SkirmishLobbySetupStructure(SkirmishLobbySetupStructure const&);
            void operator=(SkirmishLobbySetupStructure const&);

        public:
            SkirmishLobbySetupStructure() {};
            ~SkirmishLobbySetupStructure() {};

            /**
             * Saves the current skirmish lobby setup into SEC_SkirmishLobbySetupStructure (used to restore it after
             * the game): autosave interval, fog-of-war, map name, per-slot round-table order/team/AI type/AI
             * variation, start positions, local slot, advantage balance, intensity, tech level, lord types,
             * popularity and map-list selection/scroll.
             */
            void commitSkirmishSettings();

            /**
             * Restores the skirmish lobby setup from SEC_SkirmishLobbySetupStructure back into
             * GameSynchronyState/GameCore (inverse of commitSkirmishSettings), recomputes the absolute selected map
             * index (g_lobbyLastAllocatedMapSelection = scroll + relative) and calls reorderTeamsAndPositions. Note: fog-of-war is
             * written into the struct again rather than restored (as decompiled).
             */
            void restoreSkirmishLobbySetup();
        };

        static_assert_cpp98_obj(sizeof(SkirmishLobbySetupStructure) == 264, SkirmishLobbySetupStructure);

#pragma pack(pop)

    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
