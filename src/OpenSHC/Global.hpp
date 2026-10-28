/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"

#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace Global {

    using OpenSHC::Rendering::Enums::DirectDrawStatus;

    /**
     * Variadic wrapper around vswprintf: formats `format` with the following arguments into the wide-char buffer
     * `destination`.
     */
    void __cdecl PrintToDestination(wchar_t* destination, wchar_t const* format, ...);

    /**
     * Empty function (just returns); shared by several callers as a no-op callback/destructor regardless of calling
     * convention.
     */
    void __cdecl DoNothing();

    /**
     * Maps a built-in map file name to its localized display name. Dispatches on toupper of the first and other
     * characters, then stricmp against hard-coded names: stock skirmish maps return TEXT_MAP_NAMES[n-1] with
     * *hardcodedMapDescriptionGroupNum = n and GameCore.mapDescUseStringTable = 1; if none matches, a second table
     * of trail/MP map names (underscore file names like "Wide_Open_Plain", "MP-...") returns
     * TEXT_TRAIL_NAMES_CRU[n-1] and sets only the group number. Unknown maps return mapName unchanged with group 0.
     * NAME? better: GetLocalizedBuiltinMapName.
     */
    char* __cdecl GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum);

    /**
     * Checks for DirectDraw 7: loads DDRAW.DLL, requires the DirectDrawCreate and DirectDrawCreateEx exports, calls
     * DirectDrawCreateEx(NULL, &_testInterface, IID_IDirectDraw7, NULL) and immediately Releases the interface
     * (vtable slot 2), frees the DLL and returns DD7_LOADED on success, DD7_NOT_LOADED otherwise.
     */
    DirectDrawStatus __cdecl DetectDXVersionByLoadingDDRAW();

    /**
     * Calls GetVersionExA with an OSVERSIONINFOEXA and returns 1 iff dwPlatformId == VER_PLATFORM_WIN32_NT and
     * (dwMajorVersion > 6 or (== 6 and dwMinorVersion >= 2)), i.e. Windows 8 / NT 6.2 or later as reported by
     * GetVersionExA; 0 otherwise. The result in AL passes through __security_check_cookie. NAME? IsWindows8OrLater.
     * Used by initializeDirectDraw.
     */
    byte __cdecl isWindows8OrLater();

    /**
     * Main WindowProc. Window messages: WM_CREATE/WM_MOVE/WM_SIZE reinit the window and refresh the client rect at
     * 0xF983E8 (in exclusive fullscreen WM_SIZE sets it to 0,0,SM_CXSCREEN,SM_CYSCREEN and WM_CREATE/WM_MOVE do
     * nothing), WM_SETFOCUS/WM_KILLFOCUS resume/pause Miles audio and all Bink videos, WM_ACTIVATEAPP updates
     * gameFocused (deactivation also ends speech streams; reactivation restores DirectDraw surfaces and resets
     * mouse state), WM_DISPLAYCHANGE stores resolution/bpp, WM_CLOSE/WM_QUIT set postWindowCloseMessage=3
     * (WM_DESTROY additionally clears windowHandle and calls PostQuitMessage), WM_PAINT re-blits when not in game;
     * mouse button/move/wheel messages go to DAT_MouseState, WM_CHAR to the text handler. WM_KEYDOWN: Ctrl-typed
     * cheat code on the main menu, text-edit keys, Enter (send chat / open chat or allies), Esc (close modals,
     * pause menu, back-navigation between menu views), Tab hide UI, Space flat view, arrows scroll (Ctrl+Left/Right
     * rotate, Ctrl+Up zoom, Ctrl+Down lowered view), C/X rotate, Z zoom, V lowered view, P pause, +/- game speed
     * (20..90 step 5, solitary and skirmish single player only), A/B/G/H/I/M/N/T jump to and open
     * armory/barracks/granary/keep/engineers guild/market/mercenary post/tunnelers guild (Ctrl: open menu only,
     * Shift: return to saved view), L own lord (Shift+L cycle lords), S cycle signposts, Q/W/E unit stance while
     * the build menu shows the soldier-command panel (build-menu tab 61 = BMTT_SOLDIERS or 62 = its hidden variant;
     * the decompiler prints these union values with BASMTT_SIEGETENT_* names), digits (assembly-point mapper in
     * barracks/mercenary/guild/cathedral menus, else select hotkey group and switch to the soldier panel saving the
     * previous build tab in tabTypeSiegeSubset, or, if already selected, focus its first unit; Ctrl+digit assign
     * group), Alt+digit / Ctrl+Alt+digit jump to / store a camera bookmark (dword tile numbers at 0x117C7E4 +
     * digit*4 = DAT_GameState.mapAndTime+0x58, shown by the decompiler as
     * playerDataArray[8].engineersAssemblyPoints[wParam-6] due to base folding), F1-F10 taunts in skirmish/MP (Ctrl
     * +10), F1 in a Just-Build builder map opens the event trigger menu, Shift+F1/Shift+F2 loadOrSaveGame(10/9);
     * WM_SYSKEYDOWN handles Alt+letter editor/cheat toggles and Alt+Q screenshot. Most paths end in DefWindowProcA;
     * several Esc/Alt paths return without calling it. Note: the local `screenHeight` is misnamed - it only holds
     * the security cookie (XOR &_hwnd); rotations compute newMapOrientation = (mapOrientation +2 or +6) mod 8.
     */
    LRESULT __stdcall WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    /**
     * Program entry (WinMain). Truncates the module path to the exe directory, loads the config path, returns -1
     * early if DAT_TextureRenderCoreObject.allocErrorCode is set or if the
     * 'Global\FireflyStrongholdCrusadersExtreme' mutex already exists (then shows 'already running'). Otherwise
     * initialises cr.tex text, DirectX detection, timer resolution (min(max(wPeriodMin,1),wPeriodMax), remembered
     * in a stack flag so timeEndPeriod is only called if timeBeginPeriod was), user config and SkMasters2,
     * window/DirectDraw, Miles audio, faces, AIV list, cursor, UI menus, loading screen and music, command-line
     * args, SFX, map headers, a blank 400x400 map with pathing/minimap, the joke-message flags and building costs.
     * Main loop: a pending message is fetched with GetMessage/Translate/Dispatch (WM_QUIT ends the loop);
     * otherwise, when focused (always in multiplayer), one frame runs: input polling, menu-view switch, network
     * receive, the scheduled game ticks (processWaitingCommands + processGameTick each), lag check, menu/modal
     * updates, map, minimap/Bink and modal rendering and flip, plus paused/inactive-time accounting; unfocused
     * single-player only updates sound/network and WaitMessage()s. postWindowCloseMessage==1 posts WM_CLOSE. On
     * exit ends the timer period, disconnects DirectPlay, writes config and SkMasters2, shuts down sound and
     * DirectDraw, optionally ShellExecutes '+svc strongholdce' (openOnClose) and calls _exit(0). The 260-byte
     * module-path buffer (esp+0x2C..0x12F after the prologue) is exePathBufferTail[260] (whole buffer despite the
     * name), filled by GetModuleFileNameA(NULL, ..., 0x104).
     */
    int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

} // namespace Global
} // namespace OpenSHC
