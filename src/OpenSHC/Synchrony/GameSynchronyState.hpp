/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/GameSynchronyState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/GameCommand.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandSchedulingInt.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishStatistics.hpp"
#include "OpenSHC/Synchrony/HashContainer.hpp"
#include "OpenSHC/Synchrony/HashDataContainer.hpp"
#include "OpenSHC/Synchrony/Networking/ChatEvent.hpp"
#include "OpenSHC/Synchrony/Networking/ConnectionLagInfo.hpp"
#include "OpenSHC/Synchrony/Networking/PacketUnion.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "WinSock.h"
#include "basetsd.h"
#include "crtdefs.h"
#include "dplay.h"
#include "dplobby.h"
#include "guiddef.h"
#include "mbstring.h"
#include "winnt.h"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommand;
    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandSchedulingInt;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Game::GameModeInt;
    using OpenSHC::Game::Skirmish::SkirmishStatistics;
    using OpenSHC::Synchrony::HashContainer;
    using OpenSHC::Synchrony::HashDataContainer;
    using OpenSHC::Synchrony::Networking::ChatEvent;
    using OpenSHC::Synchrony::Networking::ConnectionLagInfo;
    using OpenSHC::Synchrony::Networking::PacketUnion;
    using OpenSHC::UI::Enums::MenuModalTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0010A218
    class GameSynchronyState {
    public:
        // [183 0x0047D5B0] used as the next free index into providerNames/guids for non-standard DirectPlay
        // providers
        int serviceProviderCount; // 0x00000000 length: 4
        int scrollBarItemOffset; // 0x00000004 length: 4
        int selectedProviderIndex; // 0x00000008 length: 4
        GUID* guids[10]; // 0x0000000C length: 40
        LPCWSTR providerNames[10]; // 0x00000034 length: 40
        int modemScrollbarCount; // 0x0000005C length: 4
        int modemScrollBarOffset; // 0x00000060 length: 4
        // [215 0x0047D0E0] set to the clicked visible row and compared with the row to highlight it
        int selectedModemRow; // 0x00000064 length: 4
        // [183 0x0047E160] filled with modem names from DPAID_Modem, indexed by modemScrollbarCount
        char* modemNames[29]; // 0x00000068 length: 116
        undefined1 padding_0xdc[4]; // 0x000000DC length: 4
        int DPLAY_SessionsCount; // 0x000000E0 length: 4
        int scrollBarIndex; // 0x000000E4 length: 4
        GUID* DPLAY_SessionGUIDs[50]; // 0x000000E8 length: 200
        WCHAR* DPLAY_SessionNames[50]; // 0x000001B0 length: 200
        bool unkEnumerationRelatedBool; // 0x00000278 length: 1
        undefined1 padding_0x279[3]; // 0x00000279 length: 3
        IDirectPlay4A* DPLAYX_4A; // 0x0000027C length: 4
        IDirectPlayLobby3** DPLAYX_LOBBY; // 0x00000280 length: 4
        MenuModalTypeInt nextModalDialog; // 0x00000284 length: 4
        int multiplayerJoinStep; // 0x00000288 length: 4
        BOOLEnum useTCPIP; // 0x0000028C length: 4
        char connectTarget[30]; // 0x00000290 length: 30
        undefined1 padding_0x2ae[2]; // 0x000002AE length: 2
        int connectPort; // 0x000002B0 length: 4
        int willHost; // 0x000002B4 length: 4
        char shellExecuteTarget[600]; // 0x000002B8 length: 600
        // 1 when the GameSpy Arcade install dir with aphex.exe was found in the registry; enables the GameSpy
        // button.
        int gameSpyArcadeInstalled; // 0x00000510 length: 4
        BOOLEnum openOnClose; // 0x00000514 length: 4
        byte connectName[256]; // 0x00000518 length: 256
        GameModeInt currentGameMode; // 0x00000618 length: 4
        GameModeInt currentGameModeCopy_SEC_Section1106; // 0x0000061C length: 4
        byte unused02[104]; // 0x00000620 length: 104
        DPNAME DPLAY_PlayerNameStructure; // 0x00000688 length: 16
        undefined4 DPLAYX_Connection; // 0x00000698 length: 4
        undefined4 DPLAYX_ReceivedPlayerID; // 0x0000069C length: 4
        dword DPLAY_ToID; // 0x000006A0 length: 4
        undefined4 DPLAYX_PlayerHandle; // 0x000006A4 length: 4
        int currentPlayerFullIDArray[9]; // 0x000006A8 length: 36
        int DAT_CurrentPlayerFullIDArray2[9]; // 0x000006CC length: 36
        int somePlayerRelatedArray[9]; // 0x000006F0 length: 36
        int currentAIArray[9]; // 0x00000714 length: 36
        int aiVariationArray[9]; // 0x00000738 length: 36
        // 9 bytes (one per player slot) shared by the host in HostShareLobbyState.
        byte lobbyPerPlayerBytes[9]; // 0x0000075C length: 9
        byte field49_0x765[3][9]; // 0x00000765 length: 27
        BOOLEnum displayYourIP; // 0x00000780 length: 4
        BOOLEnum lanOrWan; // 0x00000784 length: 4
        IN_ADDR lanIP; // 0x00000788 length: 4
        IN_ADDR wanIP; // 0x0000078C length: 4
        BOOLEnum isHost; // 0x00000790 length: 4
        int DAT_HostPlayerSlotID; // 0x00000794 length: 4
        int DAT_HostAnnounced; // 0x00000798 length: 4
        // 254-byte text buffer whose first bytes are cleared by the constructor and setupSkirmishLobby.
        byte lobbyTextBuffer[254]; // 0x0000079C length: 254
        WCHAR DPLAYX_SessionName[250]; // 0x0000089A length: 500
        WCHAR DPLAY_PlayerShortName[125]; // 0x00000A8E length: 250
        int packetsReceived; // 0x00000B88 length: 4
        // [UNK PASS] was transmissionCounterUnk
        int packetsSent; // 0x00000B8C length: 4
        // Increased by 2 whenever a received command is scheduled for a tick that already passed; reset in lobby
        // setup.
        undefined4 lateCommandPenalty; // 0x00000B90 length: 4
        undefined4 DAT_GameHalted; // 0x00000B94 length: 4
        int syncStatus; // 0x00000B98 length: 4
        // Zeroed at the start of broadcastDesyncResyncCommands; no reader found.
        undefined4 resyncCounterB9c; // 0x00000B9C length: 4
        // Zeroed at the start of broadcastDesyncResyncCommands; no reader found.
        undefined4 resyncCounterBa0; // 0x00000BA0 length: 4
        // Set to 1 by broadcastDesyncResyncCommands and sent in SyncPacketSizeAnnouncement.
        undefined4 resyncInProgressFlag; // 0x00000BA4 length: 4
        // Bytes of resync data sent per chunk (40000, less on laggy connections); sendPendingResyncCommandsInBudget
        // suspends when exceeded.
        undefined4 resyncByteBudget; // 0x00000BA8 length: 4
        // Switch case 0..15 saved when resync byte budget runs out; reset to 0. Not a packet subtype
        undefined4 resyncResumeStage; // 0x00000BAC length: 4
        // Outer index where the chunked resync sender resumes.
        undefined4 resyncResumeIndex; // 0x00000BB0 length: 4
        // Inner index where the chunked resync sender resumes.
        undefined4 resyncResumeSubIndex; // 0x00000BB4 length: 4
        int syncRelatedStatusArray[9]; // 0x00000BB8 length: 36
        // Total size of resync data to transfer (sum computed in broadcastDesyncResyncCommands); shared in sync
        // packets and shown in the resync progress display.
        undefined4 resyncTotalBytes; // 0x00000BDC length: 4
        undefined4 currentPacketTotalSize; // 0x00000BE0 length: 4
        // timeGetTime() when the save command executes; shown as 'Last saved: N minutes'; not autosave-only
        // timeGetTime() of the last synchronized autosave; 0 after lobby setup.
        undefined4 lastSaveTimeMs; // 0x00000BE4 length: 4
        // Copy of resyncStartTime (field259_0x109290) taken when a desync is detected (checkLagAndSyncStatus) or a
        // resync starts; the resync dialog shows "Last saved" as (this - lastAutosaveTimeMs)/60000 minutes
        undefined4 desyncDetectedTimeMs; // 0x00000BE8 length: 4
        // [194 0x0048CB00] set to 1 when a hash mismatch queues GCT_GAME_DESYNC; blocks further checks; cleared on
        // lobby setup
        undefined4 desyncDetected; // 0x00000BEC length: 4
        // Zeroed by setupSkirmishLobby/initMultiplayerLobbyState; no reader found.
        undefined4 lobbyResetBf0; // 0x00000BF0 length: 4
        undefined4 splinterType; // 0x00000BF4 length: 4
        undefined4 totalSplitDataItems; // 0x00000BF8 length: 4
        undefined4 totalSplitChimps; // 0x00000BFC length: 4
        undefined4 totalSplitStructures; // 0x00000C00 length: 4
        undefined4 totalSplitVeg; // 0x00000C04 length: 4
        undefined4 totalSplitTribes; // 0x00000C08 length: 4
        undefined4 totalSplitPlayers; // 0x00000C0C length: 4
        undefined4 totalSplitElements; // 0x00000C10 length: 4
        undefined4 totalSplitLayers; // 0x00000C14 length: 4
        undefined4 totalSplitFlies; // 0x00000C18 length: 4
        undefined4 totalSplitMoats; // 0x00000C1C length: 4
        undefined4 totalSplitTeleports; // 0x00000C20 length: 4
        undefined4 totalSplitPitchDitches; // 0x00000C24 length: 4
        undefined4 totalSplitZones; // 0x00000C28 length: 4
        undefined1 padding_0xc2c[8]; // 0x00000C2C length: 8
        undefined4 firstSplitChimps; // 0x00000C34 length: 4
        undefined4 firstSplitStructures; // 0x00000C38 length: 4
        undefined4 firstSplitVeg; // 0x00000C3C length: 4
        undefined4 firstSplitTribe; // 0x00000C40 length: 4
        undefined4 firstSplitPlayer; // 0x00000C44 length: 4
        undefined4 firstSplitElement; // 0x00000C48 length: 4
        undefined4 firstSplitLayer; // 0x00000C4C length: 4
        undefined4 firstSplitFly; // 0x00000C50 length: 4
        undefined4 firstSplitMoat; // 0x00000C54 length: 4
        undefined4 firstSplitTeleports; // 0x00000C58 length: 4
        undefined4 firstSplitPitchDitch; // 0x00000C5C length: 4
        undefined4 firstSplitZone; // 0x00000C60 length: 4
        undefined1 padding_0xc64[8]; // 0x00000C64 length: 8
        // [190 0x0048B330] 1 = vote question received, 2 = collecting votes (initiator), reset to 0 on no/close
        undefined4 quitVoteState; // 0x00000C6C length: 4
        // Per player slot (9): 1 when that player voted to quit (ShareQuitGameVote); all set ends the game.
        int quitVoteByPlayer[9]; // 0x00000C70 length: 36
        int quitGameVoteRequestTime; // 0x00000C94 length: 4
        int announcementReceivedByPlayer[9]; // 0x00000C98 length: 36
        undefined4 saveRelated; // 0x00000CBC length: 4
        // only set by non-host after executing the save command; sync tick queues 0x5D ShareAnnouncementWithHost
        // (review 361 verified)
        undefined4 shouldSendSaveAck; // 0x00000CC0 length: 4
        BOOLEnum announcementReceivedBool; // 0x00000CC4 length: 4
        undefined4 announcementReceiveTime; // 0x00000CC8 length: 4
        // [196 0x00490480] set (host only, when 0) to the slot of the first remote player whose last packet time is
        // >15 s old, together with the NotifyLaggingPlayer command
        undefined4 laggingPlayerSlot; // 0x00000CCC length: 4
        // [208 0x004B2530] set to timeGetTime() when a result (timed out / ejected / back in game) is decided; box
        // closes 2000 ms later and it is reset to 0
        undefined4 notRespondingResultTimeMs; // 0x00000CD0 length: 4
        // Message ID (0x41/0x42/0x43) about the lagging player chosen by the host and broadcast via
        // SomeKindOfMultiplayerPingUnk.
        undefined4 laggingPlayerMessageID; // 0x00000CD4 length: 4
        PacketUnion DPLAY_ReceiveData; // 0x00000CD8 length: 61000
        byte DAT_PacketDecodingDestination[61100]; // 0x0000FB20 length: 61100
        PacketUnion DAT_Packet; // 0x0001E9CC length: 61000
        undefined1 syncPacket2Type; // 0x0002D814 length: 1
        undefined3 mapTimeInTicksLower3Bytes; // 0x0002D815 length: 3
        undefined1 syncParamTimeDiff; // 0x0002D818 length: 1
        undefined1 padding_0x2d819[3]; // 0x0002D819 length: 3
        undefined4 DPLAY_ReceiveDataSize; // 0x0002D81C length: 4
        undefined4 DAT_CurrentTransmitCommandPacketSize; // 0x0002D820 length: 4
        undefined4 DAT_CurrentGameCommandID; // 0x0002D824 length: 4
        GameCommandSchedulingInt DAT_CommandActionPlan; // 0x0002D828 length: 4
        undefined4 DAT_PlayerIDReceiver; // 0x0002D82C length: 4
        undefined4 DAT_CommandSize; // 0x0002D830 length: 4
        byte DAT_GameCommandFixedParameterLocation[61000]; // 0x0002D834 length: 61000
        GameCommand DAT_GameCommandArray[200]; // 0x0003C67C length: 254400
        short DAT_LagIndicatorPerPlayer[9]; // 0x0007A83C length: 18
        undefined1 padding_0x7a84e[2]; // 0x0007A84E length: 2
        undefined4 DAT_GameCommandParam0; // 0x0007A850 length: 4
        undefined4 DAT_GameCommandParam1; // 0x0007A854 length: 4
        undefined4 DAT_GameCommandParam2; // 0x0007A858 length: 4
        undefined4 DAT_GameCommandParam3; // 0x0007A85C length: 4
        undefined4 DAT_GameCommandParam4; // 0x0007A860 length: 4
        undefined4 DAT_GameCommandParam5; // 0x0007A864 length: 4
        // [193 0x00487E30] incremented per sent sync message and reset after 7 to adjust commandDelay
        int syncSendCounter; // 0x0007A868 length: 4
        int clTimeDiff; // 0x0007A86C length: 4
        int syncRelatedCountdown; // 0x0007A870 length: 4
        int matchTime; // 0x0007A874 length: 4
        int matchTimesArray[8]; // 0x0007A878 length: 32
        int HASH_HashTotal[9]; // 0x0007A898 length: 36
        // [191 0x0048FCB0] initialized to the identity sequence 0..8 after resync (0x1998024..0x1998044, separate
        // from matchTimesArray at 0x1997FE0)
        int playerSlotOrder[9]; // 0x0007A8BC length: 36
        HashContainer HASH_PartialHashPerPlayer; // 0x0007A8E0 length: 432
        int DAT_MultiplayerGameVersions[9]; // 0x0007AA90 length: 36
        BOOLEnum isIncludedPlayer[9]; // 0x0007AAB4 length: 36
        // [194 0x0048BD40] set FALSE when two occupied slots report different DAT_MultiplayerGameVersions; TRUE
        // otherwise (also while a slot's version flag is not set)
        BOOLEnum allGameVersionsMatch; // 0x0007AAD8 length: 4
        byte sharedDesyncFlags[14]; // 0x0007AADC length: 14
        undefined1 padding_0x7aaea[2]; // 0x0007AAEA length: 2
        ConnectionLagInfo connectionLagInfoArray[9]; // 0x0007AAEC length: 324
        undefined1 syncPacketType; // 0x0007AC30 length: 1
        undefined1 syncRelatedCounter; // 0x0007AC31 length: 1
        undefined1 syncRelated2; // 0x0007AC32 length: 1
        undefined1 padding_0x7ac33[1]; // 0x0007AC33 length: 1
        int historicalLagInfoPerPlayer[9][100][2]; // 0x0007AC34 length: 7200
        // [193 0x004882A0] ring index into historicalLagInfoPerPlayer, -1 = no sample yet, wraps at limit
        undefined4 lagHistoryIndex; // 0x0007C854 length: 4
        // [193 0x004882A0] number of history samples averaged (set to 5)
        undefined4 lagHistoryLength; // 0x0007C858 length: 4
        int HASH_Units[9][2500]; // 0x0007C85C length: 90000
        int HASH_Buildings[9][2000]; // 0x000927EC length: 72000
        int HASH_Trees[9][2000]; // 0x000A412C length: 72000
        int HASH_Tribes[9][1250]; // 0x000B5A6C length: 45000
        int HASH_PlayerDatas[9][9]; // 0x000C0A34 length: 324
        // [195 0x0048CC90] hashes 0x38E6-byte chunks of DAT_GameState.mapAndTime (+0x10 bytes near
        // signpostsMapEdge) and, at index 0x13, AIVState.mapExtraInfo
        int HASH_MapAndTimeSection[9][20]; // 0x000C0B78 length: 720
        int HASH_Entities[9][3000]; // 0x000C0E48 length: 108000
        HashDataContainer HASH_LogicalTileMap[9]; // 0x000DB428 length: 138240
        int HASH_Moats[9][160]; // 0x000FD028 length: 5760
        int HASH_ClimbData[9][200]; // 0x000FE6A8 length: 7200
        int HASH_PitchDitches[9][40]; // 0x001002C8 length: 1440
        int HASH_Unknown2[9][40]; // 0x00100868 length: 1440
        int HASH_AIVS[9][9]; // 0x00100E08 length: 324
        int HASH_HeatMaps[9][80]; // 0x00100F4C length: 2880
        // Per-player resync state 0/1/2, not a received bool
        int resyncStatusByPlayer[9]; // 0x00101A8C length: 36
        // [195 0x0048DA60] per-slot flag set to 1 for the local slot and for kicked slots; all occupied slots must
        // be non-zero before the desync flags are computed
        int hashReportReceivedBySlot[9]; // 0x00101AB0 length: 36
        // Multiplayer latency adjustment in ticks ("Relative time" in the network debug view), computed in
        // determineGameTicksToPerform.
        undefined4 relativeTimeOffset; // 0x00101AD4 length: 4
        char receivedChatMessage[250]; // 0x00101AD8 length: 250
        char DAT_ChatMessageArray[20][250]; // 0x00101BD2 length: 5000
        char DAT_ChatMessageSubjectPlayerNameArray[20][250]; // 0x00102F5A length: 5000
        char DAT_ChatMessageObjectPlayerNameArray[20][250]; // 0x001042E2 length: 5000
        undefined1 padding_0x10566a[2]; // 0x0010566A length: 2
        undefined4 DAT_ChatMessageArrayIndex; // 0x0010566C length: 4
        // Ring-buffer cursor used while drawing chat lines: starts at DAT_ChatMessageArrayIndex (minus scroll
        // offset in lobby) and walks backwards, wrapping 0 -> 0x13 (20 chat slots)
        undefined4 chatRenderIterIndex; // 0x00105670 length: 4
        undefined4 DAT_InsultTextIndex; // 0x00105674 length: 4
        ChatEvent DAT_ChatEventArray[20]; // 0x00105678 length: 320
        char shortMapName[120]; // 0x001057B8 length: 120
        int skirmishRelated1; // 0x00105830 length: 4
        char mapName[1000]; // 0x00105834 length: 1000
        char DAT_PlayerNames[9][250]; // 0x00105C1C length: 2250
        char playerNames2[9][250]; // 0x001064E6 length: 2250
        int DAT_PlayerSlotArraySomeValue[9]; // 0x00106DB0 length: 36
        // [192 0x0047EDE0] per-slot flag that must be non-zero for every slot occupied in
        // DAT_CurrentPlayerFullIDArray2 before the host reports all players ready
        int playerReadyFlags[9]; // 0x00106DD4 length: 36
        // [194 0x0048CB00] only occupied slots with this value 0 are compared in the hash check (low confidence)
        int excludedFromSyncCheck[9]; // 0x00106DF8 length: 36
        // Client flag: set 1 when HostShareLobbyState command is executed, cleared on SetPlayerNameUnk;
        // checkAllPlayersReady returns 0 for non-host while it is 0
        int lobbyStateReceivedFromHost; // 0x00106E1C length: 4
        int skirmishUnknownSetting1[4]; // 0x00106E20 length: 16
        int skirmishStartGold; // 0x00106E30 length: 4
        int skirmishDefaultPopularity; // 0x00106E34 length: 4
        int skirmishGameSpeedLevel; // 0x00106E38 length: 4
        int skirmishGameIntensityType; // 0x00106E3C length: 4
        int skirmishIntensityRelatedArray[20]; // 0x00106E40 length: 80
        undefined4 skirmishGameIntensityType2; // 0x00106E90 length: 4
        // [183 0x004274F0] filled 1:1 from
        // RenderingDefinedData.SkirmishIntensityRelatedArray2[skirmishTechLevel][0..9]
        int skirmishIntensityArray2[10]; // 0x00106E94 length: 40
        byte unused03[40]; // 0x00106EBC length: 40
        // Set to 1 right before switchToMenuView(MVT_LOBBY_MENU)+InitSkirmishLobbyData (skirmish, crusade,
        // join/host session, cmdline); cleared in LobbyMenu_Prepare and main-menu prepare. Write-only in this build
        // (9 code refs, all stores; verified in clean.exe).
        int enteringLobbyPending; // 0x00106EE4 length: 4
        undefined4 skirmishTechLevel; // 0x00106EE8 length: 4
        undefined1 padding_0x106eec[4]; // 0x00106EEC length: 4
        undefined4 skirmishWinCondition; // 0x00106EF0 length: 4
        undefined4 skirmishTroopsCostGold; // 0x00106EF4 length: 4
        // [190 0x0048B6C0] non-host players copy the map name received from the host into it
        char sharedMapName[1004]; // 0x00106EF8 length: 1004
        undefined4 skirmishCurrentAdvantageBalance; // 0x001072E4 length: 4
        // Write-only: only ever set to -1 (after GCT_CHANGE_GAME_INTENSITY_OR_BALANCE is queued, MP speed change,
        // skirmish balance setup, lobby setup/init); no reader in clean.exe (5 stores). Paired with
        // unusedSettingsResetB
        int unusedSettingsResetA; // 0x001072E8 length: 4
        // Write-only twin of unusedSettingsResetA (+0x1072e8): set to -1 at the same 5 sites, never read
        int unusedSettingsResetB; // 0x001072EC length: 4
        // Number of messages scrolled back in the lobby chat box; passed to renderChatMessageList, reset to 0 when
        // a new message arrives or chat is cleared. Range 0..15 (lobby chat scroll-up/-down buttons).
        undefined4 lobbyChatScrollOffset; // 0x001072F0 length: 4
        BOOLEnum reparseMaps; // 0x001072F4 length: 4
        // Frame countdown: host sets 0x32 (50) in AcknowledgeMapExistence when a client reports it lacks the map;
        // decremented each lobby frame while non-zero, zeroed on map selection/lobby init. Nothing else reads it
        // (dead timer in this build)
        int mapAbsentAckCountdown; // 0x001072F8 length: 4
        int DAT_MapSelectionScrollOffset; // 0x001072FC length: 4
        int DAT_MapSelectionTotalNumber; // 0x00107300 length: 4
        int DAT_MapSelectionRelativeSelected; // 0x00107304 length: 4
        byte unused04[8]; // 0x00107308 length: 8
        // Per map id: +1 fits player count, -1 too few slots, 0 client lacks map; greys rows and gates start/send-
        // map.
        int mapAvailabilityArray[500]; // 0x00107310 length: 2000
        int mapPlayerCountArray[500]; // 0x00107AE0 length: 2000
        int mapBalanceArray[500]; // 0x001082B0 length: 2000
        int mapU4Int0_2Array[500]; // 0x00108A80 length: 2000
        // Lobby map table sort/filter mode (1..0xb, default 6); set by MapSelectHeader column clicks,
        // saved/restored with skirmish setup (mbr_0xfc). Values: 1/2 = column-0 sort asc/desc, 3/4 = column-2 sort,
        // 5..0xb = player-count column cycle.
        undefined4 mapListSortMode; // 0x00109250 length: 4
        undefined4 savedMapTimeInTicks; // 0x00109254 length: 4
        undefined4 savedUnitsCRC32Hash; // 0x00109258 length: 4
        undefined1 padding_0x10925c[4]; // 0x0010925C length: 4
        undefined4 unknownIncrementBy40_01; // 0x00109260 length: 4
        int DAT_ChatMessageReceiverArray[9]; // 0x00109264 length: 36
        undefined4 DAT_ChatTauntOrMessage; // 0x00109288 length: 4
        undefined4 skirmishPoints; // 0x0010928C length: 4
        // timeGetTime() when a resync starts (ResyncStartCS); copied into lag/announcement timers
        dword resyncStartTime; // 0x00109290 length: 4
        int kickedAtTime; // 0x00109294 length: 4
        // One-shot flag: first time the local player is destroyed/kicked a TEXT_MULTIPLAYER_CONNECTION message is
        // added to chat and this is set 1; reset in lobby init. BUG: VoteKick path checks ==0 but then stores 0
        // again (not 1), so the notice can repeat there.
        undefined4 localDropNoticeShown; // 0x00109298 length: 4
        // [196 0x00490380] only used as Param1 of the DestroyPlayer/LEAVE_GAME command, whose handlers show it as a
        // TEXT_MULTIPLAYER_CONNECTION text index; set to 0x3d on DPSYS_DESTROYPLAYERORGROUP and 0x3e on >60 s
        // silence (0x3f is passed directly by the sync-timeout kicks)
        undefined4 leaveReasonTextIndex; // 0x0010929C length: 4
        int skirmishAutoSaveEveryMinutes; // 0x001092A0 length: 4
        // [194 0x0048C660] reset to timeGetTime() on every autosave and compared against the autosave interval;
        // must be non-zero (presumably set at game start)
        undefined4 autosaveIntervalStartTime; // 0x001092A4 length: 4
        int DAT_MapU4Int2_2; // 0x001092A8 length: 4
        undefined4 DAT_HashCountdown; // 0x001092AC length: 4
        // Host-only 'Connection lost' box: set 1 when host clicks 'Cancel game', which grows the box by 3*16 px and
        // shows the Yes/No confirmation; 'No' clears it; cleared on ResyncStart
        undefined4 cancelGameConfirmShown; // 0x001092B0 length: 4
        undefined4 skirmishStrongWalls; // 0x001092B4 length: 4
        undefined4 skirmishAlliances; // 0x001092B8 length: 4
        undefined4 skirmishNoCowThrowing; // 0x001092BC length: 4
        undefined4 skirmishNoDogs; // 0x001092C0 length: 4
        undefined4 skirmishNoRushSetting; // 0x001092C4 length: 4
        undefined4 skirmishExtremeMode; // 0x001092C8 length: 4
        // [219 0x00429A40] action -0xE XORs it (0x1A26A34) and announces SKIRMISH_MISC text 0xE 'Extreme Powers
        // around Lord'; the On/Off text then tests skirmishExtremeMode (0x1A26A30) - confirmed original-game
        // display bug
        undefined4 skirmishExtremePowersAroundLord; // 0x001092CC length: 4
        // [190 0x0048ACB0] indexed by requesting slot and set to timeGetTime() when an alliance request (Param1==0)
        // is received
        int allianceRequestTime[9]; // 0x001092D0 length: 36
        int DAT_ReceivedAIVFileAvailabilityPerAIArray[9][20]; // 0x001092F4 length: 720
        SkirmishStatistics finalResults; // 0x001095C4 length: 1912
        // [216 0x004909E0] char[4][20] list of typed join IPs (loop bound 0x1a274f4 = base 0x1a274a4 + 4*20):
        // deduped with stricmp, shifted on overflow, cycled into text field 5 by button -1000 via ipArrayIndex
        // (wraps after 3)
        char recentJoinIpAddresses[4][20]; // 0x00109D3C length: 80
        int ipArrayIndex; // 0x00109D8C length: 4
        undefined4 DAT_TwoIfNotHost; // 0x00109D90 length: 4
        undefined4 DAT_MapFileReceivingState; // 0x00109D94 length: 4
        // Per player slot: 0 unknown, 1 player lacks map (host must send it), 2 has map/empty/self; set by
        // ShareMapHashForMapName and AcknowledgeMapExistence. Indexed by player slot 1..8. When all slots are non-
        // zero after StartSendingMapFile the SEND_MAP_TO modal opens.
        short mapPossessionStatePerPlayer[9]; // 0x00109D98 length: 18
        undefined1 padding_0x109daa[2]; // 0x00109DAA length: 2
        int mapSendingFileSize; // 0x00109DAC length: 4
        // int[9] byte counter per slot incremented by chunk size; progress bar divides by mapSendingFileSize; not
        // an address
        int mapBytesTransferredPerSlot[9]; // 0x00109DB0 length: 36
        FILE* mapSendingFileHandles[9]; // 0x00109DD4 length: 36
        FILE* FILEPTR_ReceivedMapFile; // 0x00109DF8 length: 4
        // Per player: index of next map-file part the host sends (incremented each lobby frame), reset to 0 when
        // sending starts
        int mapSendNextPartIndex[9]; // 0x00109DFC length: 36
        // Per player: 0 idle, 1 part sent awaiting ack (ShareMapPart), 2 acknowledged (MapSendingRelated); host
        // only sends next part when != 1. Ghidra also mis-attributes byte reads at +0x1a+slot (lobby slot->player
        // table) to this field
        int mapPartTransferState[9]; // 0x00109E20 length: 36
        byte DAT_RoundTableOrderArray[9]; // 0x00109E44 length: 9
        byte DAT_PlayerGroupArray[9]; // 0x00109E4D length: 9
        // [230 0x004AEA50] copied back into DAT_PlayerGroupArray on Cancel (0x65); filled from DAT_PlayerGroupArray
        // in Synchrony.cpp when the round table is initialised
        byte savedPlayerGroupArray[9]; // 0x00109E56 length: 9
        // Per player: set 1 when host clicks a human player in lobby and command 0x55 (kick) is queued; disables
        // the button; cleared in removePlayerFromLobby. Indices +8.. are used as a separate per-position byte table
        // by skirmish setup. Indices [pos+8] (pos 1..8) actually address the next byte array at +0x109e68 (Ghidra
        // over-indexing).
        byte kickRequestedPerPlayer[9]; // 0x00109E5F length: 9
        char playerPositionsArray[8]; // 0x00109E68 length: 8
        undefined4 protocolInvokerPlayerID; // 0x00109E70 length: 4
        undefined4 currentPlayerSlotID; // 0x00109E74 length: 4
        undefined4 DAT_SomePlayerID; // 0x00109E78 length: 4
        // Map editor: player whose keep/buildings are placed (set by MP_KEEPn buttons, 1 by default);
        // ClickPlaceBuilding uses it instead of the invoker player in MVT_MAP_EDITOR_LANDSCAPING
        undefined4 editorPlacementPlayerID; // 0x00109E7C length: 4
        // 9-byte per-player array serialized by host in HostShareLobbyState together with player IDs, AI,
        // positions; meaning unknown. Only touched by the two serialize calls in HostShareLobbyState (no other code
        // refs).
        byte lobbySharedPlayerBytes[9]; // 0x00109E80 length: 9
        undefined1 padding_0x109e89[3]; // 0x00109E89 length: 3
        // Set to 1 in GameSynchronyState constructor only. Write-only.
        int ctorInitFlag109e8c; // 0x00109E8C length: 4
        undefined1 padding_0x109e90[4]; // 0x00109E90 length: 4
        // timeGetTime of last receive/periodic sync; throttledMultiplayerSyncUpdate sends at most every 10 ms
        undefined4 lastPeriodicSyncTime; // 0x00109E94 length: 4
        // Smallest matchTimesArray value among active players (ticks); -1 before computation
        undefined4 minPlayerMatchTime; // 0x00109E98 length: 4
        // Max of matchTimesArray over occupied slots (SP: copy of mapTimeInTicks); pairs with minPlayerMatchTime
        undefined4 maxPlayerMatchTime; // 0x00109E9C length: 4
        // matchTimesArray[localSlot-1]: local player's match time in ticks
        undefined4 localPlayerMatchTime; // 0x00109EA0 length: 4
        // maxPlayerMatchTime - minPlayerMatchTime (ticks)
        undefined4 matchTimeSpread; // 0x00109EA4 length: 4
        // local match time - min match time when local is not the slowest; looked up in ProtocolDefinedData
        // slowdown table
        undefined4 ticksAheadOfSlowest; // 0x00109EA8 length: 4
        // local - max match time (<=0) when local is the slowest; negative values select catch-up multiplier
        undefined4 ticksBehindFastest; // 0x00109EAC length: 4
        // Column 1 of ProtocolDefinedData slowdown table chosen by ticksAheadOfSlowest; default 1. Computed but
        // never read in this build (no loads of +0x109eb0..b8 in clean.exe; determineGameTicksToPerform ignores
        // them).
        undefined4 latencySlowdownParamA; // 0x00109EB0 length: 4
        // Column 2 of ProtocolDefinedData slowdown table chosen by ticksAheadOfSlowest; default 1. Computed but
        // never read in this build (no loads of +0x109eb0..b8 in clean.exe; determineGameTicksToPerform ignores
        // them).
        undefined4 latencySlowdownParamB; // 0x00109EB4 length: 4
        // Set from ProtocolDefinedData catch-up table by ticksBehindFastest (default 1). Computed but never read in
        // this build (no loads of +0x109eb0..b8 in clean.exe; determineGameTicksToPerform ignores them).
        undefined4 catchUpTickMultiplier; // 0x00109EB8 length: 4
        // Zeroed in GameSynchronyState constructor only. Write-only.
        int ctorZeroed109ebc; // 0x00109EBC length: 4
        // Zeroed in GameSynchronyState constructor only. Write-only.
        int ctorZeroed109ec0; // 0x00109EC0 length: 4
        undefined4 receivedCommandMapTimeInTicks; // 0x00109EC4 length: 4
        undefined1 padding_0x109ec8[4]; // 0x00109EC8 length: 4
        // GetTickCount() at construction. Write-only.
        int ctorTickCount; // 0x00109ECC length: 4
        // [194 0x0048C750] timestamp of last sendSyncPacket126, interval 1800 ms
        undefined4 lastPingSendTime; // 0x00109ED0 length: 4
        // [194 0x0048C750] timestamp of last sendSomeMultiplayerSyncMessageWithType, interval 180 ms
        undefined4 lastSyncMessageTime; // 0x00109ED4 length: 4
        // timeGetTime() at construction. Write-only.
        dword ctorTimeGetTime; // 0x00109ED8 length: 4
        undefined4 MBR_GameCommandID; // 0x00109EDC length: 4
        undefined4 DAT_GameCommandArrayIndex; // 0x00109EE0 length: 4
        undefined4 DAT_CommandParameterOffset; // 0x00109EE4 length: 4
        undefined4 commandDelay; // 0x00109EE8 length: 4
        int MBR_SelectedGameCommands[100][2]; // 0x00109EEC length: 800
        // [192 0x00480440] number of entries written into MBR_SelectedGameCommands, capped at 100
        undefined4 selectedCommandCount; // 0x0010A20C length: 4
        // [192 0x0047EC10] typo in field name; holds an HRESULT compared against DPERR codes
        int DPLAYX_SendAndReceiveResult; // 0x0010A210 length: 4
        undefined4 DAT_TickCount; // 0x0010A214 length: 4

    private:
        GameSynchronyState(GameSynchronyState const&);
        void operator=(GameSynchronyState const&);

    public:
        GameSynchronyState() {};
        ~GameSynchronyState() {};

        // Constructor
        /**
         * Constructor of the global GameSynchronyState: solitary mode, no DirectPlay handles, initial timestamps
         * (GetTickCount/timeGetTime), session name 'Crusader' and default name string 'Contestant', then
         * setupSkirmishLobby, reads the GameSpy config and sets autosave to 10 minutes; returns the global object.
         */
        GameSynchronyState* Constructor_GameSynchronyState();

        /**
         * Returns TRUE if slot playerID has no human (DirectPlay id -1) and an AI is assigned in currentAIArray.
         */
        BOOLEnum isAIPlayer(int playerID);

        /**
         * Writes the DirectPlay service-provider GUID for the current selection into the output: the hardcoded
         * DPSPGUID_TCPIP when useTCPIP is set, otherwise guids[selectedProviderIndex + scrollBarItemOffset].
         */
        void getGUIDForSelectedProvider(GUID* outGuid);

        /**
         * Sets activeMenuTab.tabType from the selected provider GUID: modem -> 1, TCP/IP -> 4, IPX -> 3, any other
         * provider -> 2 (the value named BASMTT_KEEP_OR_MPMENU_OTHER).
         */
        void setMenuTypeBasedOnDirectPlayGUID();

        /**
         * Builds a DirectPlay compound address for the selected provider: element 0 is DPAID_ServiceProvider;
         * TCP/IP adds DPAID_INet (text field 5) and, if text field 6 parses to a nonzero port, a third element;
         * modem adds DPAID_Modem (selected modem name, if any) and DPAID_Phone (text field 7). Calls
         * IDirectPlayLobby3::CreateCompoundAddress twice (size query, then into a GlobalAlloc buffer) and on
         * success stores the buffer and its size via pCompoundAddress/pAddressSize. Returns an HRESULT: 0 on
         * success, the first call's result if it is not DPERR_BUFFERTOOSMALL, E_OUTOFMEMORY if GlobalLock fails, or
         * the second call's error (buffer freed).
         */
        int createCompoundAddressBasedOnSelectedProvider(LPVOID* pCompoundAddress, SIZE_T* pAddressSize);

        /**
         * Fills DPLAYX_SessionName (UTF-16): 'Crusader' when useTCPIP is set, otherwise 'Stronghold-<text field
         * 0>'.
         */
        void setDPlaySessionNameValue();

        /**
         * Creates or joins a DirectPlay session; returns an HRESULT (0 = success). join==FALSE: rebuilds the
         * compound address, recreates IDirectPlay4A and calls InitializeConnection; non-hosts stop there (clearing
         * DPLAY_CurrentSessionGUID and storing the interface), the host opens a new 8-player session (OFE_CREATE).
         * join==TRUE: opens session DPLAY_CurrentSessionGUID on the existing interface (OFE_JOIN). After a
         * successful Open (create or join) it creates the local DirectPlay player (failure returns 0x887701A4
         * without storing the interface). Open/InitializeConnection failures close/release the interface and clear
         * DPLAYX_4A; no lobby interface returns 0x88770082.
         */
        int initializeDirectPlayAndCreateOrJoinSession(BOOLEnum join);

        /**
         * NAME? (better: lockSessionOnGameStart) Host only: updates the DirectPlay session description with the
         * JOINDISABLED and NEWPLAYERSDISABLED flags, keeping app GUID, 8 max players and the regenerated session
         * name. Both callers run when a multiplayer game is launched
         * (ShareGameSeedAndMultiplayerSettingsAndStartGame right before LaunchSkirmishGame, SetPlayerNameUnk during
         * load-game start), so it locks the session.
         */
        void setSessionDescription();

        /**
         * Host only: sets the DirectPlay session description to an open session (no join restrictions), 8 max
         * players, regenerating the session name (0x191e002 = DPLAYX_SessionName).
         */
        void setDirectPlaySessionDescription();

        /**
         * Copies the GUID of the session selected in the session list (scrollBarIndex + scrollBarItemOffset) into
         * pGUID, if a valid row is selected.
         */
        void fetchSessionGUID(GUID* pGUID);

        /**
         * NAME? Re-selects the session whose GUID equals pGUID after the session list was refreshed, scrolling the
         * 10-row list so it is visible (offset = index, or max(count-10,0) near the end); clears the selection if
         * not found.
         */
        void resolveEqualEntries(GUID* pGUID);

        /**
         * Frees all enumerated session names and GlobalAlloc'ed session GUIDs and resets DPLAY_SessionsCount to 0.
         */
        void clearSessionsList();

        /**
         * Tears down multiplayer (with wait cursor): frees session, provider and modem lists, cancels pending
         * messages, destroys the local player and closes IDirectPlay4A (the pointer is cleared without Release),
         * releases the lobby interface and frees the compound address, then resets game mode to solitary and the
         * halt/sync/TCPIP/vote/save flags.
         */
        void disconnectDPlay();

        /**
         * Reads HKCU\Software\GameSpy\GameSpy Arcade value InstDir (RegOpenKeyExA KEY_READ, RegQueryValueExA, max
         * 0x200 bytes) into shellExecuteTarget, appends a backslash and 'aphex.exe', and sets
         * gameSpyArcadeInstalled = 1 if that file can be opened. BUG (original game, harmless): the trailing-
         * backslash check reads s[strlen(s)] (always NUL), so a backslash is always appended.
         */
        void readGameSpyConfig();

        /**
         * Computes tick-rate adjustment from matchTimesArray (slots 1..8; occupied slots only, an unset -1 entry is
         * first set to mapTimeInTicks): min and max time and their spread. If this slot (playerSlot) has the
         * minimum time, field315 = own - max (lag, <= 0), otherwise field314 = own - min (lead). A negative lag
         * selects field318 from the first ProtocolDefinedData.field4_0x4 row whose threshold is below it (default
         * 1); otherwise the first field5_0x64 row with lead <= threshold supplies field316 and field317.
         */
        void computeLatencyAdjustmentFromMatchTimes(int playerSlot);

        /**
         * NAME? Just RLE-compresses size bytes from src into dst via DecoderState::compressRLE and returns its
         * result (compressed length); no length prefix is written here.
         */
        int compressPacketDataRLE(int size, char* src, void* dst);

        /**
         * RLE-decompresses source into DAT_PacketDecodingDestination (0x192d288) and copies the decompressed bytes
         * to destination.
         */
        void decompressTooLongPacketData(byte* source, byte* destination);

        /**
         * Counts slots 1..8 that hold a human player (DirectPlay id != -1).
         */
        int countActiveHumanPlayers();

        /**
         * Counts slots 1..8 that hold either a human player (currentPlayerFullIDArray != -1) or an AI
         * (currentAIArray != 0).
         */
        int countOccupiedPlayerSlots();

        /**
         * Lobby validity check over player slots 1..8 (4 slots per iteration, 2 iterations). A slot is occupied if
         * it has a human ID (currentPlayerFullIDArray != -1) or an AI (currentAIArray != 0); every occupied slot
         * adds 1 to its team's member count. Player count: a human adds 1, and in GM_SKIRMISH_SINGLE_PLAYER every
         * occupied slot adds 1 more (so AIs count only in skirmish). Returns 0 if the player count is < 2 or any
         * team 1..8 has 3+ members; otherwise returns the number of non-empty teams 1..8 (team 0 is ignored).
         */
        int checkPlayerSetValid();

        /**
         * Returns how many occupied slots 1..8 (currentPlayerFullIDArray != -1) have the same team
         * (DAT_GameState.mapAndTime.playerTeams) as the given player slot; the player itself is included when its
         * own slot is occupied.
         */
        int countPlayersInSameTeam(int playerSlot);

        /**
         * Maps a DirectPlay player ID to the player slot 1..8 by searching currentPlayerFullIDArray (last match
         * wins, 0 if not found). In GM_SOLITARY / GM_SKIRMISH_SINGLE_PLAYER simply returns currentPlayerSlotID.
         */
        uint translateMultiplayerIDsIntoPlayerIDs(int dplayPlayerID);

        /**
         * Assigns a slot to a DirectPlay player ID: returns its existing slot 1..8 if already present; otherwise
         * (outside skirmish) takes the first free slot (ID -1) with no AI assigned (currentAIArray < 1), falling
         * back to the first free slot regardless of AI. Stores the ID there and returns the slot, or 0 if all 8
         * slots are taken.
         */
        int addPlayerToCurrentPlayerArray(int playerFullID);

        /**
         * If the last DirectPlay result (DPLAYX_SendAndReceiveREsult) is not one of the known DPERR codes, formats
         * "Error:DirectPlay unknown %x" into a local buffer that is never used (stripped debug output). No other
         * effect.
         */
        void handleUnexpectedDPlayXResult();

        /**
         * Host: returns 0 if any slot 1..8 occupied in DAT_CurrentPlayerFullIDArray2 (!= -1) still has
         * unknownPlayerInfo_01 == 0 (not ready); otherwise sets currentPlayerFullIDArray[slot] = -1 for every slot
         * whose somePlayerRelatedArray entry is 0 and returns 1. Client: returns 1 if field215_0x106e1c != 0, else
         * 0.
         */
        undefined4 checkAllPlayersReadyAndCleanupSlots();

        /**
         * Returns a checksum of the whole unit array (0x2C8E40 bytes of DAT_UnitsState.units) computed by
         * DirectionAlgorithmState::computeHash; used for sync checks around autosave/save and game launch.
         */
        int computeSomeHashOnUnitArray();

        /**
         * Debug modal renderer for desync 'splinter' info at (x,y): prints the splinter category name for types
         * 0..5 (chimps, structures, vegetation, tribes, players, game elements), then total/first split counts for
         * types 0..11 (also layers, flies, moats, teleports, pitch ditches, zones). For chimps it also draws 10
         * pairs of unit hash values from HASH_Units (local vs. other side, 0x2710 bytes apart), coloured
         * differently when the pair differs.
         */
        void renderDebugDataSplitInfo(int x, int y, int width, int height);

        /**
         * Appends an entry to the 20-slot chat ring buffer: advances the index (wraps after 19), stores
         * subject/object player, timeGetTime() timestamp and flag 1, copies the 250-byte chat input text
         * (0x1A1F240) into the message array, the subject name ('Host' text for player 0, else DAT_PlayerNames)
         * into the subject-name array and, if objectPlayerID != 0, that player's name into the object-name array.
         * Resets field237_0x1072f0.
         */
        void addChatMessageToDisplayList(int subjectPlayerID, int objectPlayerID);

        /**
         * Clears chat state: zeroes the 250-byte chat input buffer and the 20x250-byte message and subject-name
         * arrays (the object-name array is NOT cleared), resets the ring index, and zeroes subjectPlayer/time/flag
         * of all 20 ChatEvent entries (objectPlayer is left as is). Resets field237_0x1072f0.
         */
        void clearChatEvents();

        /**
         * Draws the in-game chat overlay: walks back 4 entries from the newest chat event (ring index wraps 0->19);
         * active entries younger than 10 s are drawn on a blended black box (subject name in player colour,
         * '(deceased)' if that player's lord unit is gone/not ULS_NORMAL and mapTimeInTicks - mapStartTick > 200,
         * message text, optional object player name); older ones get flag 0. Each line goes 14 px up. Third stack
         * parameter is never read (ret 0xc).
         */
        void renderInGameChat(int screenX, int screenY, int unused3);

        /**
         * Lobby chat box renderer: starts scrollOffset entries back from the newest chat event and walks at most 5
         * entries upward (17 px per entry, inactive entries still use a line). Active entries get the subject name
         * in player colour and word-wrapped message text; a message wider than one line moves up an extra 18 px and
         * counts as an extra line (max 5 lines). Clips drawing to yPos-0x48..yPos+0x12.
         */
        void renderChatMessageList(int xPos, int yPos, int scrollOffsetOrEntry);

        /**
         * Resets the game command queue: zeroes current/processed/next command indices, clears the 200-entry
         * GameCommand array (0x3E1C0 bytes) and sets each of the 9 per-player lag indicators to 1000.
         */
        void resetGameCommands();

        /**
         * Zeroes the 0x4F8-byte GameCommand entry at the given index if it is < 200.
         */
        void clearGameCommandEntry(int gameCommandID);

        /**
         * NAME? Measures, does not send: builds the command in the next free queue slot (owner = own DirectPlay
         * handle, type = low byte of commandCategory, shown by Ghidra as unaff_SI) by calling its handler in
         * GCS_SCHEDULE_AND_SEND mode, but never calls transmitCommand. If the serialized size exceeds 200 bytes and
         * the type is not 0x41 (GCT_SEND_RESYNC_LOGICALTILEMAP), it compresses the data into a 0x7D wrapper packet
         * (type byte, 3 time bytes, compressed/length-prefixed payload) and returns that length + 1; otherwise it
         * returns DAT_CommandSize. The slot is then cleared. broadcastDesyncResyncCommands uses it to add up the
         * total resync size.
         */
        int measureCommandPacketSize(GameCommandType commandCategory);

        /**
         * Queues a command received from the network (ignored if the queue index is >= 200). For type 0x4D (handler
         * 0x48A8A0 DestroyPlayer) it adds 40 to unknownIncrementBy40_01 and, if the sender is this player, sets the
         * time of the entry at the OLD DAT_CurrentGameCommandID to now+1. A non-zero time lowers this player's lag
         * indicator to (time - now) if smaller, or adds 2 to field62_0xb90 if the time is already due. Fills the
         * slot (state 1, sender, type, time) and runs the handler in GCS_SCHEDULE_RECEIVED_COMMAND mode; if the
         * entry time is then < 1 the payload is copied to the fixed parameter buffer, executed (GCS_EXECUTE) and
         * cleared, else it is copied into the entry and the ring index advances (wraps at 200).
         */
        void scheduleReceivedCommand(GameCommandType commandCategory, DWORD dxPlayerHandle, dword time, void* address);

        /**
         * NAME? Selects due commands rather than returning an ID: collects up to 100 queued commands (state 1..9,
         * time <= mapTimeInTicks) from MBR_GameCommandID on as (commandID, invokerSlot) pairs, bubble-sorts them by
         * player slot, and returns 1 if any were selected; returns 0 if none, or if a pair with slot 0 (unknown
         * sender) is met during sorting.
         */
        int selectDueCommandsSortedByPlayer();

        /**
         * Returns DAT_GameCommandArrayIndex (next free command queue slot); used by the network debug display.
         */
        undefined4 getGameCommandArrayIndex();

        /**
         * Counts queued commands with state 1..9 (pending) from MBR_GameCommandID to the end of the 200-entry
         * array; used by the network debug display.
         */
        int getPendingGameCommandsCount();

        /**
         * Copies size bytes between the caller variable ('destination') and the command parameter stream at
         * DAT_CommandParameterOffset (fixed parameter buffer for GCPL_FIXED_COMMAND_DATA_ADDRESS, else the current
         * GameCommand's parameters), then advances the offset. destSwitch 0 (GCPRW_WRITE_VAR_TO_STREAM) copies
         * the variable INTO the stream; 1 copies the stream OUT into the variable. No-op if size <= 0 or the
         * pointer is NULL.
         */
        void serializeOrDeserializeCommandParameter(void* destination, size_t size,
            GameCommandParameterLocation srcSwitch, GameCommandParameterReadWrite destSwitch);

        /**
         * Per-tick end-of-game check (skips solitary mode; shrine part runs for every non-solitary mode, the rest
         * not in campaign missions and not after game over): counts down each player's commemoration-shrine timer
         * and places the statue when it reaches 0. If GameCore.forceLocalPlayerVictory is set, ends the game at once with
         * only the local player as winner. Otherwise counts per team (teams 1..8) the occupied slots (human or AI)
         * and those whose lord is killed (lordKilledByPlayerID != 0); when at most one team is left undefeated (or,
         * with GameCore.isKingOfTheHill set, some occupied player's field695_0x229c is 0 - then that player's team wins)
         * it ends the game: for each occupied slot playerIsAlive[slot] = 1 if it belongs to the winning team else
         * 0, playerDeathRelated = 1, gameOver/gameOverTime set, win/defeat window shown, siege build tab, mapper
         * command and unit selection cancelled. NAME? decides winners as well as losers (checkSkirmishGameOver).
         */
        void checkSkirmishGameOver();

        /**
         * Returns the lord type for a player slot: for human slots (currentPlayerFullIDArray != -1)
         * GameCore.selectedLordTypes[playerID]; for AI slots 0 for the European lords (Rat, Snake, Pig, Wolf,
         * Richard, Frederick, Philipp, Sheriff, Marshal, Abbot) and 1 for all others (Arabian). Used by lord and
         * siege-engine updates to pick European vs Arabian variants.
         */
        int getLordTypeForPlayer(int playerID);

        /**
         * Before a game starts: copies the local user's name (text entry 0) into DAT_PlayerNames[1], then for slots
         * 1..8 sets finalResults.active (human or AI present), copies the player name into the final-results name
         * table (90-byte stride at 0x1A26D86) and zeroes all per-player final statistics; finally clears the 9x9
         * finalKillMatrix (81 ints).
         */
        void initializeFinalResultsForActivePlayers();

        /**
         * Clears DPLAYX_4A/DPLAYX_LOBBY, sets serviceProviderCount to 3, creates a temporary IDirectPlay4 and an
         * IDirectPlayLobby3 via CoCreateInstance (CLSCTX_INPROC_SERVER), calls IDirectPlay4::EnumConnections(NULL,
         * EnumConnectionsCallback, NULL, 0) to fill the provider GUID/name lists, removes empty entries among the
         * first three reserved positions (index 2, then 1, then 0; shifting both lists and decrementing
         * serviceProviderCount), calls setMenuTypeBasedOnDirectPlayGUID, stores the lobby interface in DPLAYX_LOBBY
         * and releases the IDirectPlay4 (also released, without storing anything, if lobby creation fails). The
         * decompiled COM calls are garbled (stored lobby / released pointer show as 0) because the indirect calls
         * have no prototype: EnumConnections (vtable +0x8C) pops 20 bytes.
         */
        void invokeDirectPlayEnumConnections();

        /**
         * Re-enumerates DirectPlay sessions for the game's application GUID (1D5E2F48-49E5E8C0-...) via
         * IDirectPlay4A::EnumSessions (async, available sessions) unless an enumeration is already running, or
         * respectTimeout is TRUE and less than 3 s passed since the last one; clears the session list first and
         * keeps the previously selected session GUID across the refresh (fetchSessionGUID/resolveEqualEntries).
         */
        void restartDPlaySessionEnumeration(BOOLEnum respectTimeout);

        /**
         * Creates a DirectPlay object for the modem service provider (GUID 44EAA760-CB68-11CF-9C4E-00A0C905425E),
         * queries IDirectPlay4A, calls GetPlayerAddress(0, NULL, &size) (vtable +0x48) expecting
         * DPERR_BUFFERTOOSMALL, allocates a GHND buffer of that size, reads the address and passes it to
         * DPLAYX_LOBBY->EnumAddress with EnumModemAddressCallback (0x0047E160), then releases both interfaces and
         * frees the buffer. The decompiled COM calls are garbled (push slots appear as locals, unaff_ESI/EDI are
         * artefacts); the real code keeps both interfaces in stack locals.
         */
        void createDirectPlayInterfaceModem();

        /**
         * Resets GameSynchronyState to single-player defaults: solitary mode, no host/player handles, chat cleared,
         * teams reset, lag history index -1 / length 5; for all 9 slots clears IDs, AI, names, AIV availability,
         * group data, partial hashes, lag info, the tick half of the 100-entry lag history (ms half is not cleared)
         * and final results; then sets skirmish defaults (popularity 100, speed 40, advantage 3, tech level 4,
         * autosave normalised to 10 min unless 0/5/10/20, command delay 35, extreme mode 1, fog off), resets the
         * command queue and map time and hides the win/defeat window.
         */
        void setupSkirmishLobby();

        /**
         * Game-loop pacing: returns how many game ticks to run this frame. Returns 0 when not in game or halted.
         * Speed (ticks/s) is GameCore.gameSpeedLevel in single player; in multiplayer it is skirmishGameSpeedLevel,
         * reduced when computeLatencyAdjustmentFromMatchTimes reports our match time ahead of the slowest player
         * (field314_0x109ea8): by 2/3 per tick ahead beyond 5 (min 15), or to field 0x109260 (min 1) when more than
         * commandDelay+75 ahead; the lead/lag is stored in field196_0x101ad4. Tick period = 1000/speed ms scaled by
         * gameSpeedMultiplicator. DAT_MillisecCarry accumulates stopwatch time minus period: far behind (carry <
         * -period) -> 0; ticks slower than the period -> 2 or 3 with carry dropped; carry > 10 periods -> 11 with
         * carry dropped; else carry/period+1 keeping the remainder, otherwise 1.
         */
        int determineGameTicksToPerform(int currentPlayerSlotID);

        /**
         * Sends a command over DirectPlay (multiplayer only): packet = category byte + 3-byte time + parameters, or
         * for sizes > 200 bytes (except type 0x41) a 0x7D wrapper with compressed/length-prefixed payload. Sent
         * with SendEx to idTo (size+4 bytes): type 0x75 with priority 0xFFFD (guaranteed only while
         * getAreWeInAInGameMenu is TRUE), type 0x0C priority 0xFFFE non-guaranteed, others 0xFFFF guaranteed.
         * Errors other than DPERR_PENDING go to handleUnexpectedDPlayXResult.
         */
        void transmitCommand(byte commandCategory, undefined4 time, char* addressOfFullCommandObjectOrCommandParameters,
            size_t size, undefined4 idTo);

        /**
         * Multiplayer: broadcasts a 5-byte sync message (type, 3-byte map tick, clTimeDiff byte) and records own
         * match time in matchTimesArray. Every 7th call decrements commandDelay and, unless syncRelatedCountdown is
         * active, raises it to a minimum derived from the worst occupied peer's average1 (half-RTT ticks): 20 if
         * <2, 25 if 2, else lag+27 capped at 50; also decrements clTimeDiff toward 0.
         */
        void sendSomeMultiplayerSyncMessageWithType(undefined4 syncPacketType2);

        /**
         * Handles a received 5-byte sync message: sets the sender's matchTimesArray entry to
         * receivedCommandMapTimeInTicks + its avgHalfRttTicks; raises commandDelay toward the sender's reported
         * time diff (signed payload byte) + 10, by at most 5; raises clTimeDiff toward |mapTimeInTicks - estimated
         * sender tick| by at most 5 (cap 45); raises commandDelay toward clTimeDiff + 10 (capped at the original
         * value + 5); forces commandDelay to 1 while syncRelatedCountdown is non-zero. __thiscall with one stack
         * dword that is never read (ret 4); relies on ECX surviving the call to
         * translateMultiplayerIDsIntoPlayerIDs.
         */
        void processSyncPacket(int unusedParam);

        /**
         * Multiplayer ping: when getAreWeInAInGameMenu is TRUE, increments the ping counter, stamps every slot's
         * lag info (0..8) with current map tick, counter and timeGetTime(), and broadcasts the 2-byte 0x7E ping
         * packet (guaranteed, priority 65000).
         */
        void sendSyncPacket126();

        /**
         * Ping handling: on a 0x7E ping replies 0x7F with the same counter to the sender (SendEx, guaranteed
         * async). On a 0x7F reply stores its arrival time; if the counter matches, stores half the round trip in
         * map ticks and in ms for the sender's slot and, while in game, sets hasLatencySample, writes the sample
         * into a ring of lagHistoryLength entries (all entries on the very first sample; the ring index
         * lagHistoryIndex is one global shared by all slots) and recomputes avgHalfRttTicks and avgHalfRttMs. BUG
         * (original game): the ms sum reads history entries 2..lagHistoryLength+1 instead of 0..lagHistoryLength-1, so two entries this
         * code never writes enter avgHalfRttMs.
         */
        void computeAndSetLatencyInformation();

        /**
         * Debug modal renderer for network state at (x,y): packets received, used command slots ('Chores used'),
         * lag indicators of players 1-4, per-player match times ('Timings'), hash totals ('Crcs', low 12 bits) and
         * their match times ('Crc times') for occupied slots, relativeTimeOffset and gameTicksThisLoop, sync status
         * ('Game in sync' / 'GAME SPLINTERED' / '... - Resyncing'), the local player's 12 partial hash domains
         * (CHI..ZONE, low 12 bits, read from GameSynchronyState+0x7a8e4+slot*0x30), unit/structure/object-ID
         * counts, RNG value, command delay, pending commands, clTimeDiff, clan count, battle levels and both game-
         * mode values.
         */
        void renderDebugDataNetwork(int x, int y, int width, int height);

        /**
         * Queues a locally issued command (commandType is the stack argument; the code keeps it in EBX/BL): fills
         * the next slot of the 200-entry command ring with own DirectPlay handle, type and time =
         * max(mapTimeInTicks, mapTimeInTicksSinglePlayer) + commandDelay, runs the command's handler in
         * GCS_SCHEDULE_AND_SEND mode to serialize parameters, then transmits it. Immediate commands (time < 1) are
         * sent from the fixed parameter buffer, executed locally if the handler switched the plan to GCS_EXECUTE,
         * and the slot is cleared; scheduled ones stay queued and the ring index advances (wraps at 200).
         */
        void queueCommand(GameCommandType commandType);

        /**
         * Executes all due commands: getCommandIDFromCommandSelectionStuff collects queued commands whose time has
         * come into MBR_SelectedGameCommands sorted by player slot (returns 0 if none or on an entry with player
         * slot 0); then for each sets the invoker slot, clears the command params, runs its handler in GCS_EXECUTE
         * mode and marks it GCS_PROCESSED.
         */
        void processWaitingCommands();

        /**
         * Lobby check that all occupied human slots report the same game version (allGameVersionsMatch; forced TRUE
         * and the check stops if an occupied slot has isIncludedPlayer FALSE). On mismatch: if the flag was TRUE
         * before and some player has a lower version than ours, adds a local 'someone has an old version' chat line
         * and sends 'you have an old version' as a chat command to lower-version receivers (temporarily replacing
         * DAT_ChatMessageReceiverArray and text entry 4); also re-announces teams/positions if our
         * DAT_PlayerSlotArraySomeValue flag is set. BUG (original game): the receiver loop tests
         * currentPlayerFullIDArray[9] (stale slot index left by the first loop) instead of each receiver's entry.
         */
        void compareGameVersions();

        /**
         * Prepares the network lobby: clears the 10-entry service-provider list and scroll state, enumerates
         * DirectPlay connections and modem addresses, resolves the local host name via WinSock 1.1 and stores up to
         * two local IPv4 addresses (each with a valid flag) in lanIP, then resets lobby state via
         * setupSkirmishLobby and clears per-slot lag timing.
         */
        void initializeMultiplayerLobby();

        /**
         * Initialises a multiplayer lobby session: resets sync counters, chat, teams, lag history index/length,
         * per-slot (0..8) AI/group/hash/lag-history/final-result data and match times (human player IDs are kept),
         * lobby defaults (speed 40, popularity 100, advantage 3, tech 4, command delay 35), the command queue,
         * mouse state, modals, sounds and default unit colours; then InitSkirmishLobbyData, sets the session
         * description, queues GCT_ASK_FOR_SLOT_ASSIGNMENT and switches to the lobby menu.
         */
        void initMultiplayerLobbyState();

        /**
         * Host-side multiplayer autosave: when autosave is enabled, timeSkirmishGameStart is non-zero, in game, in
         * sync and no save running, and more than skirmishAutoSaveEveryMinutes minutes passed since
         * timeSkirmishGameStart, sets the map name to 'autosave', restarts the timer (also field75_0xbe4) and
         * queues GCT_SAVE with current tick, unit-array hash and flag 1.
         */
        void queueSynchronizedAutosaveProtocol();

        /**
         * Throttled multiplayer sync: sends the 0x7E ping (sendSyncPacket126) when more than 1800 ms passed and the
         * 5-byte sync message when more than 179 ms passed since the respective last send, decrementing a positive
         * syncRelatedCountdown with each sync message.
         */
        void sendPeriodicSyncMessages();

        /**
         * Normalises lobby team groups and computes start order: empty slots get group -1, negative groups of
         * occupied slots become 0; a group containing all occupied players is dissolved (all set to 0), a group
         * with a single member is dissolved; empty group numbers among 1..4 are compacted; then
         * DAT_RoundTableOrderArray[1..n] lists occupied slots sorted by group (ungrouped last) then slot. Host (not
         * skirmish single player) then queues lobby-state share and team/position announce. Returns 1.
         */
        undefined4 reorderTeamsAndPositions();

        /**
         * Desync detection when the hash countdown is 0: clears DAT_GameHalted, takes HASH_HashTotal and
         * DAT_PlayerMatchTimes of the first occupied slot with unknownPlayerInfo_03 == 0 as reference; on the host
         * (unless a desync is already flagged) returns unless every such player has a hash and a match time >= 10,
         * then if any player reports a different hash for the reference match time queues GCT_GAME_DESYNC, sets
         * flag_0xbec, resets per-player sync status arrays and, if syncRelatedCountdown was active, clears it and
         * sets commandDelay to 30.
         */
        void checkGameSync();

        /**
         * NAME? Computes sync hashes; it does not send any resync. Unless the game is halted, or DAT_HashCountdown
         * is non-zero (then it is just decremented), it hashes the local player's game state: units, buildings,
         * trees, tribes, player datas, the mapAndTime section (+AIV mapExtraInfo), logical tile-map layers,
         * entities from index 25, moats, climb data, pitch ditches, AIVs and heat maps. Volatile fields are zeroed
         * while hashing and restored afterwards. It stores per-element hashes in the HASH_* arrays, the 14 category
         * subtotals in HASH_PartialHashPerPlayer[slot] (shown by the decompiler as
         * DAT_PlayerMatchTimes[slot*12+9..22]) and their sum in HASH_HashTotal. If dontSendSyncCommand == 0 it
         * tail-calls queueCommand(12) (handler CommandCheckSync, which sends the lag indicator and HASH_HashTotal).
         */
        void computeStateHashesAndQueueSyncCheck(int dontSendSyncCommand);

        /**
         * Marks the local slot in syncStatus10Related, then waits until every occupied slot
         * (currentPlayerFullIDArray != -1) has reported. While waiting: if announcementReceivedBool is FALSE and
         * more than 60 s have passed since announcementReceiveTime, it queues GCT_KILL_GAME and returns. If it is
         * TRUE and more than 45 s have passed, it queues GCT_LEAVE_GAME (param1 0x3F) for each silent slot, marks
         * that slot as reported and goes on; otherwise it returns. Once all slots have reported it sets
         * syncStatus=1, resets the announcement time/flag, and for each of the 14 categories sets
         * sharedDesyncFlags[c]=1 if any occupied slot's partial hash differs from the first occupied slot's. It
         * then queues GCT_SHARE_SYNC_STATUS. Note: the per-slot stride is 12 ints, so categories 12-13 read the
         * next slot's categories 0-1.
         */
        void checkLagAndSyncStatus();

        /**
         * NAME? Sizing pass that starts a resync; it transmits nothing itself. It waits like checkLagAndSyncStatus
         * until all occupied slots have sent their sync status (60 s kill / 45 s kick; kicked slots are marked 2).
         * For each category flagged in sharedDesyncFlags and each element whose local hash differs from any
         * occupied slot's, it calls sendLongerDataSuchAsResync with the matching GCT_SEND_RESYNC_* /
         * GCT_HOST_SHARE_* type. That call only serializes the command and returns its size, so the sizes add up to
         * the total resync bytes in field73_0xbdc (the progress-bar total). Tile map: layer 0 -> LOGICALTILEMAP,
         * layers 1-9 -> TILEMAPDATA2, layers 10-29 -> TILEMAPDATA1. It then sets the per-chunk byte budget
         * field68_0xba8 = 40000 if the worst occupied connection lag average1 is <= 2, else 10000. It resets the
         * resume position (somePacketSubTypeUnk/field70_0xbb0/field71_0xbb4 = 0), syncRelatedStatusArray to 1,
         * currentPacketTotalSize to 0 and syncStatus to 2, and queues command 90 (SyncPacketSizeAnnouncement). The
         * real chunked sending happens in sendPendingResyncCommandsInBudget.
         */
        void measureResyncSizeAndStartResync();

        /**
         * Resumable resync sender (syncStatus 2 phase, called every game tick). First waits until
         * syncRelatedStatusArray[1..8] are all set (peers acknowledged the previous chunk); if not, returns, unless
         * an announcement was received >45 s ago, in which case every still-unset slot is kicked (GCT_LEAVE_GAME,
         * reason text 0x3f) and marked set. Then resumes at category somePacketSubTypeUnk and element field70_0xbb0
         * / sub-index field71_0xbb4 and, for every element whose local hash differs from a connected player's hash,
         * queues the matching GCT_SEND_RESYNC_* / GCT_HOST_SHARE_* command (order: units, buildings, trees, tribes,
         * player datas, section1023, entities, moats, climb, pitch ditches, unknown2, tile-map layer 0, layers 1-9,
         * layers 10-29, AIVs, heat maps; categories whose sharedDesyncFlags entry is 0 are skipped). When the
         * summed packet sizes exceed field68_0xba8 it saves the resume position and queues command 87
         * (GCT_RESYNC_CHUNK_DONE, actually the chunk barrier: its handler 0x48B170 resets syncRelatedStatusArray
         * and restarts the announcement timer) and returns; when everything is sent it queues
         * GCT_RESYNC_FINISH and sets syncStatus=3.
         */
        void sendPendingResyncCommandsInBudget();

        /**
         * Marks the local slot's receivedSyncStatusByPlayerUnk as 2 and queues GCT_SET_SYNC_STATUS_0 once every
         * occupied slot (currentPlayerFullIDArray != -1) reached 2. Otherwise, if an announcement was received and
         * >45 s have passed, it kicks the unconfirmed occupied slots (GCT_LEAVE_GAME, reason text 0x3f, status
         * forced to 2) and queues GCT_SET_SYNC_STATUS_0; if no announcement was received and >60 s have passed it
         * queues GCT_KILL_GAME.
         */
        void advanceSyncStatusAndKickLaggers();

        /**
         * Waits until announcementReceivedByPlayer[1..8] are all set, then queues GCT_CLOSE_MODAL_DIALOG_FOR_ALL.
         * If no announcement was received at all it queues GCT_KILL_GAME after 45 s; otherwise after 45 s it kicks
         * every slot without an announcement (GCT_LEAVE_GAME reason text 0x3f, resyncStatusByPlayer=2) and then
         * queues GCT_CLOSE_MODAL_DIALOG_FOR_ALL. Unlike the sibling checks it does not skip empty slots (-1 ids).
         */
        void checkGameLagStatusAndKickAccordingly();

        /**
         * In multiplayer modes only (not solitary / single-player skirmish), calls sendPeriodicSyncMessages when
         * more than 10 ms have passed since the last call, tracking the time in field309_0x109e94.
         */
        void throttledMultiplayerSyncUpdate();

        /**
         * Handles a player leaving. Always sets syncRelatedStatusArray[playerID]=1. If in-game and the player is
         * not the local slot: queues command 77 (DestroyPlayer, handler 0x48A8A0; Ghidra shows it as an OR of two
         * enum names) or, while a resync/save is in progress, GCT_LEAVE_GAME, with Param0=playerID and
         * Param1=kickDueToLagStatusUnk (reason text index), adds 40 to unknownIncrementBy40_01 and sets
         * unknownPlayerInfo_03[playerID]. Otherwise (lobby or local slot) clears the slot: name, full id (-1), slot
         * value, inclusion, AIV availability, position, game version, field294 entry; sets reparseMaps, rechecks
         * lobby AIV availability and, if host and not the local slot, reorders teams/positions.
         */
        void removePlayerFromLobby(int playerID);

        /**
         * Per-frame multiplayer connection watchdog (WinMain). Copies currentGameMode; in single-player modes
         * zeroes commandDelay and returns. Queues command 0x5d (ShareAnnouncementWithHost) if
         * shouldSendAnnouncementUnk. When syncStatus==0 and not saving: if in-game and every occupied remote slot
         * has connectionLagInfoArray[].hasLatencySample set, the host flags the first remote player silent for >15 s
         * (laggingPlayerIDUnk + command 0x62 NotifyLaggingPlayer, the 'Not Responding' box) and any player silent
         * for >60 s is removed with reason 0x3e; it also calls sendSyncPacket126 every >1.8 s and the type-0 sync
         * message every >179 ms (decrementing syncRelatedCountdown). While a sync or save is in progress it zeroes
         * all connectionLagInfoArray[].time instead.
         */
        void checkMultiplayerLaggingPlayers();

        /**
         * Main multiplayer receive loop: stamps field309_0x109e94, then repeatedly calls IDirectPlay4A::Receive
         * (61000-byte buffer, DPRECEIVE_ALL) until DPERR_NOMESSAGES / E_PENDING (return) or another error
         * (handleUnexpectedDPlayXResult). System messages: 5 (DPSYS_DESTROYPLAYERORGROUP) removes the player with
         * reason 0x3d; 3 and 0x31 are ignored; 0x101 (DPSYS_HOST) makes us host, sets DAT_HashCountdown=2, restamps
         * timeSkirmishGameStart, clears two 9-entry match-time arrays, shows 'You are now Host' and, outside a
         * game, closes the round-table dialog and reorders teams; others are only sprintf'ed. Packets from other
         * players: protocol 0x7d is decompressed first, the 3-byte map time is extracted, protocol <2 goes to
         * processSyncPacket, <0x7e to scheduleReceivedCommand (packetsReceived++), 0x7e/0x7f to
         * computeAndSetLatencyInformation. Stops if the mode becomes solitary.
         */
        void receiveAllTransmittedCommands();

        /**
         * Switches to GM_MULTIPLAYER and clears the solitary cheats. As a client it queues
         * GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST and pumps receiveAllTransmittedCommands for up to 20 s
         * (GetTickCount) until DAT_HostAnnounced is set; on timeout it disconnects DirectPlay, reinitialises the
         * lobby and returns to the MP connection view with the service-provider dialog. As host it just sets
         * DAT_HostAnnounced=1.
         */
        void waitForMultiplayerHost();

        /**
         * Parses the command line into (option, value) token pairs with double-quote handling and applies '+connect
         * host[:port]' (useTCPIP; connectTarget gets up to 29 chars, copied up to and including the ':';
         * connectPort = number after ':'; user text slots 5 (whole value) and 6 (port)), '+host port' (useTCPIP,
         * willHost, connectPort, text slot 6) and '+name value' (copied to the buffer at 0x191DC80). If TCP/IP was
         * requested it fills an empty user text slot 0 with 'Lord Crusader', sets isHost=willHost and either opens
         * the waiting-for-host connection menu (client) or initialises the lobby, creates the DirectPlay session,
         * switches to the lobby, waits for host, resets teams and queues GCT_ASK_FOR_SLOT_ASSIGNMENT (host;
         * disconnects on failure). Note: local nextTokenCharPos is really the token (row) index and nextArgPos the
         * char position within the token.
         */
        void handleCommandLineArguments(char* arguments);
    };

    static_assert_cpp98_obj(sizeof(GameSynchronyState) == 1090072, GameSynchronyState);

#pragma pack(pop)

} // namespace Synchrony
} // namespace OpenSHC
