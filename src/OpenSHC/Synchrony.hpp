/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "crtdefs.h"
#include "ddraw.h"
#include "dplay.h"
#include "winnt.h"
namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /**
     * Resets the skirmish/multiplayer lobby state: refreshes the AIV availability list, clears the map selection,
     * map name and description, map sections, teams and the lobby minimap, sets every player position to -10
     * (empty), and sets game mode to skirmish/multiplayer. Copies the 20-entry intensity array and 10-entry balance
     * array for the current skirmish tech level from DAT_TroopValueDefinedData and sets start gold from
     * StartGold[techLevel/2]. Enables chat to all 9 receivers. If host, sets all 9 player groups to 0xFF and
     * reorders teams/positions.
     */
    void __cdecl InitSkirmishLobbyData();

    /**
     * For player slot playerID (1..8): clears its AI variation, then marks every variation index already used by
     * other AI-controlled slots (currentPlayerFullIDArray == -1) that have the same AI character (currentAIArray).
     * Assigns the lowest unused variation 0..8 to aiVariationArray[playerID]. If all are used, it stays -1. This
     * keeps two copies of the same AI lord from getting the same nickname/variation.
     */
    void __cdecl ResetAiVariationArrayValue(int playerID);

    /**
     * If playerID has no lobby position yet, counts the map's valid keep positions (keepPositions[i].x >= 0) and
     * how many of them are taken (playerPositionsArray[i] >= 0). It then uses SEC_RNG to pick one of the free
     * positions at random and stores playerID-1 there. Does nothing if every position is taken.
     */
    void __cdecl PutPlayerIntoRandomSlot(int playerID);

    /**
     * For player slots 1..8 that are AI (currentPlayerFullIDArray == -1 and currentAIArray != 0), copies a nickname
     * into DAT_PlayerNames[slot]. The name is the TEXT_XPLAY_WAITING_ROOM string at a base offset per AI character
     * (0x6F + 8*(aiChar-1)) plus the slot's aiVariationArray value.
     */
    void __cdecl SetAIPlayerNickNames();

    /**
     * Returns the 1-based lobby position (slot) whose playerPositionsArray entry equals playerID-1, or 0 if the
     * player has no position.
     */
    int __cdecl GetPlayerPosition(int playerID);

    /**
     * DirectDraw EnumDisplayModes callback (__stdcall, ret 8: DDSURFACEDESC*, context). For 15/16-bit modes
     * (ddpfPixelFormat.dwRGBBitCount at desc+0x54) it sets the matching DWORD flag in
     * DAT_WindowAndDirectDraw.resolutionSupported_0x68 for one of 15 hardcoded resolutions (800x600, 1024x600/768,
     * 1280x720/1024, 1360x768, 1366x768, 1440x900, 1600x900/1200, 1680x1050, 1920x1080/1200, 2560x1440/1600).
     * Always returns DDENUMRET_OK (1). The function name is correct; only its Synchrony namespace is misplaced
     * (rendering/DirectDraw helper).
     */
    HRESULT __stdcall EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam);

    /**
     * DirectPlay EnumConnections callback. TCP/IP, IPX and modem providers go to fixed slots 0/1/2, and any other
     * provider goes to slot scrollBarItemCount, which is then incremented. Stops enumerating (returns 0) when the
     * count exceeds 9. Copies the provider short name into a malloc'd wide string in providerNames[slot] and the
     * provider GUID into GlobalAlloc'd memory in guids[slot].
     */
    BOOL __stdcall EnumConnectionsCallback(
        LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, DPNAME* lpName, DWORD dwFlags, LPVOID lpContext);

    /**
     * DirectPlay EnumSessions callback. If the enumeration has not timed out (dwFlags & DPESC_TIMEDOUT == 0) and
     * fewer than 50 sessions are stored, it duplicates the session name into DPLAY_SessionNames[count] and the
     * instance GUID into GlobalAlloc'd DPLAY_SessionGUIDs[count], then increments DPLAY_SessionsCount (only if
     * GlobalLock succeeded). Returns true (continue) after storing, false on timeout or when the list is full.
     */
    bool __stdcall EnumSessionsCallback_addSession_async(
        DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext);

    /**
     * IDirectPlayLobby::EnumAddress callback (__stdcall, 4 args: guidDataType, dataSize, data, context; context
     * unused; passed at 0x4875F2 to lobby vtable+0x14). For DPAID_Modem data, which is a double-NUL-terminated list
     * of modem names, it mallocs a copy of each name (strlen+2 bytes) into
     * GameSynchronyState.modemNames[modemScrollbarCount++]. Returns FALSE (stop) when 30 names are already
     * stored and another remains, else TRUE. NAME? It collects modem names; it is not a memory-allocation callback.
     */
    BOOLEnum __stdcall EnumModemAddressCallback(int* param_1, undefined4 param_2, char* param_3);

    /**
     * Deserializes size bytes of the current command's parameter data into a temporary malloc'd buffer and copies
     * it byte-by-byte over dest. Each byte that differs is formatted as 'ID:%d OF:%d M:%d S:%d' (player, offset,
     * received, local) into a stack buffer. That text is never output, which suggests the logging was compiled out.
     * Frees the temp buffer. Used by the Resync* commands.
     */
    void __cdecl deserializeCommandParamIntoBufferWithMismatchLog(char* dest, size_t size, undefined4 playerID);

    /**
     * Sets the menu action parameter to 0x1F, opens the MMT_PROGRESS_BAR_BOX modal dialog and runs its load/save
     * button logic with argument 0. It is called from the SetPlayerName command, likely to show a waiting/progress
     * box.
     */
    void __cdecl ProgressBarRelated();

    /**
     * Copies all 9 bytes of DAT_PlayerGroupArray into playerGroupArray2Unk (two dword copies plus byte 8, not just
     * three entries). Also zeroes the roundtable selected-slot and redraw flags and two other globals (0xdf4240,
     * 0xdf4298). Called from the lobby player-list/NPC button handler.
     */
    void __cdecl syncPlayerGroupArrays();

    /**
     * Sets up a Crusade-trail mission (normal, Extreme or Warchest trail by currentTrailType) as a single-player
     * skirmish. Copies the mission map name, clears player names, marks all 9 slots non-human (full-ID array = -1),
     * clears AI characters and sets AI variations to -1; the local user's name goes into slot 1, the game becomes
     * host in GM_SKIRMISH_SINGLE_PLAYER and queues GCT_ASK_FOR_SLOT_ASSIGNMENT. Assigns the mission AI lords
     * (player2AI..) to slots 2..numberOfPlayers, sets nicknames, takes groups from team1..8 (0xFF beyond
     * numberOfPlayers; positive groups become the team, group-0 players get fresh teams above the highest), copies
     * fairness/start levels, clears playerPositionsArray to -10 and for each positionN != 0 stores player index N-1
     * at playerPositionsArray[positionN-1] (decompiler shows it as kickRequestedPerPlayer[positionN+8]).
     */
    void __cdecl LoadSkirmishCampaignData(int missionID);

} // namespace Synchrony
} // namespace OpenSHC
