/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/WindowAndDirectDraw.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/ColorModeInt.hpp"
#include "OpenSHC/Rendering/ScreenResolutionArrayStruct.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "ddraw.h"
#include "winnt.h"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorModeInt;
        using OpenSHC::Rendering::ScreenResolutionArrayStruct;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::ScreenResolutionEnumInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000001E4
        class WindowAndDirectDraw {
        public:
            BOOLEnum drawingReady_0x0; // 0x00000000 length: 4
            dword depthBitsPerPixel; // 0x00000004 length: 4
            int screenHorizontalResolutionInPixels; // 0x00000008 length: 4
            int screenVerticalResolutionInPixels; // 0x0000000C length: 4
            int screenWidthOnInit_0x10; // 0x00000010 length: 4
            int screenHeightOnInit_0x14; // 0x00000014 length: 4
            int gameResolutionX; // 0x00000018 length: 4
            int gameResolutionY; // 0x0000001C length: 4
            // MainMenuBorderWidth and MainMenuBorderHeight describe the space between the game resolution and the
            // central 800x600 resolution. And at the same time they are the upper left coords of this central
            // screen part. So depending on how they are actually used, a name change might be appropriate.
            int mainMenuBorderWidth; // 0x00000020 length: 4
            int mainMenuBorderHeight; // 0x00000024 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int gameOnScreenPosX_0x28; // 0x00000028 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int gameOnScreenPosY_0x2c; // 0x0000002C length: 4
            // [254 0x0046F750] set to adjustedRect.right - adjustedRect.left - resolutionX, i.e. total non-client
            // width Unsigned Double-Word (ddw, 4-bytes)
            int windowFrameExtraWidth; // 0x00000030 length: 4
            // [254 0x0046F750] set to adjustedRect.bottom - adjustedRect.top - resolutionY, i.e. total non-client
            // height Unsigned Double-Word (ddw, 4-bytes)
            int windowFrameExtraHeight; // 0x00000034 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int resolutionX; // 0x00000038 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int resolutionY; // 0x0000003C length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int byteSizeOfOneHorizontalLine; // 0x00000040 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int gameResolutionY_3_0x44; // 0x00000044 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int byteSizeofScreenResolution; // 0x00000048 length: 4
            // [255 0x00479540] used as biSizeImage and bfSize-0x36 for the 24-bit BMP (width*3*height) Unsigned
            // Double-Word (ddw, 4-bytes)
            int bmp24ImageByteSize; // 0x0000004C length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword colorDepth; // 0x00000050 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            ColorModeInt colorBitMode; // 0x00000054 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            BOOLEnum runGameAsExclusiveFullscreen; // 0x00000058 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            ScreenResolutionEnumInt currentGameResolution; // 0x0000005C length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword windowMoveEventBlitCountdown; // 0x00000060 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            dword postWindowCloseMessage; // 0x00000064 length: 4
            ScreenResolutionArrayStruct resolutionSupported_0x68; // 0x00000068 length: 64
            // [UNK PASS] was hInstanceUnk_0xa8
            HINSTANCE hInstance; // 0x000000A8 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            HWND windowHandle; // 0x000000AC length: 4
            RECT clientOnScreenCoords; // 0x000000B0 length: 16
            // [255 0x0046FFB0] set to 2 after DDraw reinit; renderBltAndFlip uses values 1 (force immediate
            // present), 2 (blit bottom 128px panel), 3/4 (blit small menu rects) and resets it to 0 Unsigned
            // Double-Word (ddw, 4-bytes)
            dword pendingOverlayBltMode; // 0x000000C0 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            BOOLEnum isNotProcessingInputEvents; // 0x000000C4 length: 4
            BOOLEnum gameFocused; // 0x000000C8 length: 4
            // [255 0x00470040] incremented each time the bottom 128px panel strip is blitted from the menu surface
            // Unsigned Double-Word (ddw, 4-bytes)
            dword bottomPanelBltCount; // 0x000000CC length: 4
            // [255 0x00470040] non-zero => blit map-game surface at camera offset instead of full menu surface;
            // value 2 => include the bottom 128px (no panel) Unsigned Double-Word (ddw, 4-bytes)
            dword mapViewBltMode; // 0x000000D0 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            ushort* surfacePointer_screenMenu; // 0x000000D4 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            ushort* surfacePointer_mapGame; // 0x000000D8 length: 4
            // Set when entering build/building/landscaping menus; DoInitial then clears the bottom menu strip
            // (magenta) and reloads/draws the edge_*.tgx side graphics once, clearing it
            dword menuEdgeRedrawPending; // 0x000000DC length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            BOOLEnum not_DDCAPS2_CANBOBHARDWARE_0xe0; // 0x000000E0 length: 4
            undefined1 padding_0xe4[8]; // 0x000000E4 length: 8
            // Unsigned Double-Word (ddw, 4-bytes)
            IDirectDraw* pointerToIDirectDrawInterface; // 0x000000EC length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            IDirectDrawSurface* directDrawBackbufferSurfacePointer; // 0x000000F0 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            IDirectDrawSurface* directDrawPrimarySurfacePointer; // 0x000000F4 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            BOOLEnum NOTSelfBufferOrWindowMode_0xf8; // 0x000000F8 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            IDirectDrawSurface* directDrawOffscreenSurfacePointer_screenMenu; // 0x000000FC length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            IDirectDrawSurface* directDrawOffscreenSurfacePointer_mapGame; // 0x00000100 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            DDSURFACEDESC surfDescBink_offSurfScreenMenu_0x104; // 0x00000104 length: 108
            // Unsigned Double-Word (ddw, 4-bytes)
            DDSURFACEDESC surfDescBink_offSurfMapGame; // 0x00000170 length: 108
            // set in every blend/blit loop of Rendering to the destination surface address before the pixel loop
            undefined* currentBlitDestPtr; // 0x000001DC length: 4
            // [255 0x00470040] timeGetTime of last present; presents throttled to >=5 ms apart Unsigned Double-Word
            // (ddw, 4-bytes)
            dword lastPresentTimeMs; // 0x000001E0 length: 4

        private:
            WindowAndDirectDraw(WindowAndDirectDraw const&);
            void operator=(WindowAndDirectDraw const&);

        public:
            WindowAndDirectDraw() {};
            ~WindowAndDirectDraw() {};

            // Constructor
            /**
             * Initialises the global WindowAndDirectDraw: exclusive fullscreen by default, resolution unset
             * (SRE_neg1), all DirectDraw interface/surface pointers cleared, initial screen size from
             * GetSystemMetrics, flags reset.
             */
            WindowAndDirectDraw* Constructor_WindowAndDirectDraw();

            /**
             * Registers window class "FFwinClass" (WndProc Global::WindowMsgProcessingFunc, icon from resource id
             * cursorResource via LoadIconA, no cursor/background) and creates a visible popup window
             * (WS_POPUP|WS_VISIBLE) covering the primary screen; stores the HWND in windowHandle and returns TRUE
             * on success. The cursorResource parameter is really an icon resource id.
             */
            BOOLEnum createWindow(LPCSTR windowName, uint iconResourceId);

            /**
             * Determines the desktop colour depth (16 if GetDeviceCaps NUMCOLORS is -1, which Windows returns for
             * every depth above 8 bpp; else PLANES*BITSPIXEL) and the primary screen resolution, and forces
             * exclusive fullscreen if the depth is not 16 (i.e. palettised desktops) or the screen is narrower than
             * gameResolutionX.
             */
            void getDeviceCapsAndSetup();

            /**
             * Marks drawing as not ready and releases the DirectDraw surfaces (screen-menu and map offscreen,
             * backbuffer, primary). If alsoReleaseDDInterfaceUnk is set, first resets cooperative level to
             * DDSCL_NORMAL and finally releases the IDirectDraw interface. Note surfacePointer_mapGame is not
             * cleared.
             */
            void releaseSurfacesAndDirectDraw(BOOLEnum alsoReleaseDDInterfaceUnk);

            /**
             * Shutdown: releases all DirectDraw surfaces and the interface, then calls CoUninitialize (tail jump).
             */
            void finalizeDirectDrawShutdown();

            /**
             * In windowed (non-exclusive) mode clips a blit destination rectangle to the primary screen bounds and
             * shrinks/shifts the source rectangle by the same amounts so the blit stays consistent.
             */
            void clipBlitRectsToScreenInWindowedMode(LPRECT destinationRect, LPRECT sourceRect);

            /**
             * Restores lost DirectDraw surfaces (primary when a flip chain is used, then backbuffer, screen-menu
             * and map offscreen surfaces); returns TRUE only if all restores succeed.
             */
            BOOLEnum restoreDXSurfaces();

            /**
             * Releases all DirectDraw surfaces and the interface and marks drawing as not ready (destructor
             * helper).
             */
            void cleanDirectDraw();

            /**
             * Sets the game window style (exclusive: WS_POPUP|WS_VISIBLE; windowed: caption, system menu, minimize
             * box, visible), turns the client rect (0,0,resolution) into a window rect with AdjustWindowRect, sets
             * the game window rect and the global screen rect at 0xf983e8 (resolution, or full screen size when
             * exclusive), stores the non-client extra width/height in gameInWindowPosX_0x30/Y_0x34 and the centred
             * on-screen position (Y shifted up by 20) in 0x28/0x2c, then positions/sizes the window
             * (HWND_NOTOPMOST, SWP_NOACTIVATE), updates it and sets focus.
             * unaff_ESI/unaff_EBP/unaff_EBX/_intendedWindowRect are the left/top/right/bottom of the adjusted local
             * RECT.
             */
            void setWindowStyleRectAndPosition();

            /**
             * Translates currentGameResolution into gameResolutionX/Y (default 800x600) and derives menu border
             * offsets relative to 800x600, line byte size (1366x768 uses a 1368-pixel pitch), screen byte size and
             * other size fields, then resets the rendering rect, surface height ranges and text clip range.
             */
            void setupPreferredScreenResolution();

            /**
             * Creates the DirectDraw interface if needed (DDCREATE_EMULATIONONLY when Global::TestOSVersion is non-
             * zero), reads caps, enumerates display modes and, if the chosen resolution is unsupported, falls back
             * to the first supported one scanning enum values SRE_1920x1200 down to SRE_800x600 (else 1360x768,
             * else 1024x600, else 800x600). Sets cooperative level (normal, or fullscreen-exclusive + 16bpp display
             * mode), creates primary/backbuffer, screen-menu offscreen surface (resolution) and map offscreen
             * surface (4056x2076), caches their pointers, picks RGB565 vs RGB555 from the green mask, initialises
             * colours and the screen/client rect at 0xf983e8. Returns FALSE (after releasing everything) on any
             * failure.
             */
            BOOLEnum initializeDirectDraw();

            /**
             * Stores hInstance into DAT_WindowAndDirectDraw, creates the game window and, on success, initializes
             * COM, queries device caps, applies the preferred resolution (if currentGameResolution >= 0) and sets
             * window style/rect/position; records the current time as the last present time.
             */
            void createCrusaderWindow(HINSTANCE hInstance, LPCSTR windowName, uint cursorResource);

            /**
             * Releases all DirectDraw surfaces and re-initializes DirectDraw with the current resolution; on
             * failure falls back to 800x600, and if that also fails sets postWindowCloseMessage. Afterwards
             * requests a bottom-panel blit (unk_resetViewportRelated=2), sets field37_0xdc=1 and stops both Bink
             * playback slots.
             */
            void recreateDirectDraw();

            /**
             * Presents a frame: throttled to one present per 5 ms (unless overlay mode 1 forces it, which also
             * clears mbr_0xd0); when DirectDraw is not ready, the window is not foreground or a window-move
             * countdown is active it only sets MenuView_TriggerInitial (and decrements the countdown). Blits the
             * full menu surface (when mbr_0xd0 is 0; BltFast with clientOnScreenCoords in exclusive fullscreen)
             * and/or the map-game surface at the camera offset (minus the 128px bottom panel unless mbr_0xd0==2) to
             * the back buffer, plus the bottom-panel (mode 2) or menu sub-rect (modes 3/4) overlay; in page-flip
             * mode it Flips and blits the overlay again into the new back buffer; then clears mbr_0xd0 and the
             * overlay mode. param>=100 is reduced by 100; non-zero param cancels the move countdown; param==1 also
             * formats an unused debug string.
             */
            void renderBltAndFlip(int presentFlags);

            /**
             * Blits the visible part of the map-game surface (camera offset, height minus the 128px bottom panel)
             * into the top of the screen/menu offscreen surface (callers: takeScreenshot,
             * TextEditorState::bltTextToScreenIfNeedBe).
             */
            void bltMapGameSurfaceToScreenMenuSurfaceComplete();

            /**
             * Blits sourceRect of the map-game offscreen surface to destinationRect of the screen/menu offscreen
             * surface (rects adjusted for non-exclusive fullscreen).
             */
            void bltMapGameSurfaceToScreenMenuSurface(RECT sourceRect, RECT destinationRect);

            /**
             * If DirectDraw is ready and the window is foreground, blits a rectangle of the map-game surface (given
             * coords expanded by 32px horizontally and 8px vertically; destination = client origin - camera offset
             * + coords) to the back buffer (whole screen in page-flip mode) and flips if page flipping is used.
             * Note the 'width/height' params are actually right/bottom coordinates.
             */
            void bltMapGameSurfaceToScreen(int windowedX, int windowedY, int windowedWidth, int windowedHeigth);

            /**
             * Same as bltMapGameSurfaceToScreen but sources from the screen/menu offscreen surface without camera
             * offset: blits the padded rect (or whole screen in page-flip mode) to the back buffer and flips if
             * page flipping is used.
             */
            void bltScreenMenuSurfaceToScreen(int windowedX, int windowedY, int windowedWidth, int windowedHeigth);

            /**
             * On window activation (window is foreground): clears isNotProcessingInputEvents; in exclusive
             * fullscreen re-creates DirectDraw and sets the client rect (0xF983E8 = clientOnScreenCoords,
             * DAT_WindowAndDirectDraw+0xB0) to the full screen size, otherwise recomputes the client rect in screen
             * coordinates and calls UpdateWindow; then sets focus to the window.
             */
            void reinitWindow();

            /**
             * Switches display mode: if drawing is ready, presents one black frame (zeroes the menu surface,
             * mbr_0xd0 temporarily 0, renderBltAndFlip(1)), then releases DirectDraw, stores the new exclusive-
             * fullscreen flag and resolution, and re-initializes DirectDraw with 800x600 fallback (same retry loop
             * as prepareWindowAndDDrawUnk). NAME? effectively changeDisplayMode.
             */
            void changeResolution(BOOLEnum runAsExclusiveFullscreen, ScreenResolutionEnum resEnum);

            /**
             * Writes a screenshot as a 24-bit BMP to <Documents folder>\screen_capture.bmp (index -1) or
             * screen_capture_NNN.bmp: if the ofstream opened, copies the visible map view into the menu surface,
             * writes a 14-byte BITMAPFILEHEADER (bfSize = pixel bytes + 0x36, bfOffBits 0x36) and the 40-byte
             * BITMAPINFOHEADER, then writes the menu surface bottom-up as B,G,R bytes, always decoding pixels as
             * RGB565 and without BMP row padding, and closes the stream. Ghidra mis-tracks the stack (cdecl
             * insertChar args popped late), so several header/temp locals are aliases of one slot.
             */
            void takeScreenshot(int screenshotIndex);
        };

        static_assert_cpp98_obj(sizeof(WindowAndDirectDraw) == 484, WindowAndDirectDraw);

#pragma pack(pop)

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
