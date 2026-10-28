/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /**
         * When resolutionX > 1024 or resolutionY > 768, draws the last loaded gfx (the outer menu border) centred
         * on screen.
         */
        void __cdecl DrawOuterMenuBorder();

        /**
         * Draws the scribe animation frame (clamped 1..44) at menu origin +0x2C0,+399. In the build menu, when the
         * active tab is not value 61 (named BASMTT_SIEGETENT_RAM_OR_BM_TROOP_PANEL), time is not halted and display element
         * 0x14 is inactive, it also draws the current month name and year at resolutionY-20.
         */
        void __cdecl RenderScribeFrame();

        /**
         * NAME? Renders more than gold. Draws the current player's gold (resource 15; red 0xFF if <= 0, shown as
         * 0), population as current/cap (red when crowding > 100; current forced to 0 when the cap is 0) and
         * popularity/100 (red below 50). Each value is drawn digit by digit in the in-game panel.
         */
        void __cdecl RenderGoldPopulationAndPopularity();

        /**
         * Renders value*4/100 right-aligned: green if positive, pale 0xB8EEFB if 0, red if negative. Next to it
         * draws the matching GM_INTERFACE_ICONS2 icon (0x80/0x81/0x82; +3 and y+1 when the flag is FALSE, y-4
         * otherwise). Sets TextManager field8_0x20 during the draw and restores the draw buffer afterwards.
         */
        void __cdecl TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk);

        /**
         * Renders a unit's current action text at (xPos,yPos). getUnitStateTextParameterAndResourceType returns an
         * action-text id plus a goods type. Ids 10/6/9 (typed as RT_BREAD/RT_IRON/RT_WHEAT) with a positive goods
         * type become combined strings: 'Taking'(101) + goods + TEXT_UNIT_ACTIONS[102], 'Returning with'(100) +
         * goods, or 'Going to get'(103) + goods. Any other positive id is shown as TEXT_UNIT_ACTIONS[id].
         */
        void __cdecl RenderUnitCurrentActionText(int unitID, int xPos, int yPos);

        /**
         * Lobby: if a map is selected (or, on a client, a map name is set), builds '<mapName>.map', resolves it and
         * reads its header (sets INT_00b95958 = 1). It measures the word-wrapped description (raw mapDescription or
         * the TEXT_MAP_NAMES string) at width 0x159 into g_mapDescriptionTextHeight and sets the scroll offset to
         * -19. On the host, when the selection differs from g_lobbyLastAllocatedMapSelection or
         * g_lobbyForceSlotReallocation is set, it resets all player positions to -10, puts every human/AI player
         * into a random slot and queues GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS. Always clears
         * g_lobbyForceSlotReallocation.
         */
        void __cdecl DisplayMapDescriptionAndAllocatePlayersToSlots();

        /**
         * Builds DAT_BlendFilterArrays: 33 rows (alpha 0..32), each 64 entries of 4 shorts. For each 5-bit value v
         * (entries 0..31), entry[0] = v*alpha/32 (blue) and entry[2] = the same value shifted to <<11 (RGB565) or
         * <<10 (RGB555), and entry[1] the green value shifted <<5 (64 green levels in 565, 32 in 555). Used by the
         * alpha-blending renderers.
         */
        void __cdecl InitBlendFilterArrays();

        /**
         * Unrolled blit of a full 32x16 diamond terrain tile (128 dwords of GM image
         * DAT_GmImageAddressToBeRendered) to the map-game surface at (g_renderMapTileScreenX, screenY), only if
         * screenY is inside mapGameSurfaceHeightRange. At normal zoom it copies each diamond row as dwords (pitch
         * 0xFD8 pixels = 0x1FB0 bytes). In zoomed-out mode (isZoom2) it writes to the same surface at row screenY/2
         * and byte x DrawSomeX&~1, copying the low pixel of each source dword (horizontal half) and only the source
         * rows matching screenY's parity. Stores the destination pointer in unknownSpecificPointer.
         */
        void __cdecl RenderTerrainTilesCenterPiece();

        /**
         * Renders the current UI button (ButtonGmDataArray[DAT_CurrentButtonGmDataIndex]) at DAT_ButtonX/Y. The
         * picture is the base picture (getPictureNumberInGm(FALSE)), +1 while interacting and +2 if
         * DAT_ButtonDisabled. If the button has an alpha GM it draws with renderGMWithBlending at
         * DAT_ButtonBlendStrength (nothing drawn at strength 32); otherwise it uses plain renderGM. Sets
         * DAT_CurrentButtonPictureInGm = pictureInGm + (0 or 2). extraout_ECX is the &ButtonGmDataArray[index]
         * still in ECX after the thiscall; the upper half of uVar4 is EDX = index*0x1C (array byte offset).
         */
        void __cdecl RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk();

        /**
         * Renders the current UI button with picture getPictureNumberInGm(DAT_ButtonCurrentlyInteracting) at
         * DAT_ButtonX/Y. If the button has an alpha GM it uses renderGMWithBlending(gm, pic, x, y,
         * DAT_ButtonBlendStrength) and skips the draw at strength 32; otherwise renderGM(gm, pic, x, y). Records
         * the button's pictureInGm in DAT_CurrentButtonPictureInGm. The decompiled call arguments match the machine
         * code (getPictureNumberInGm is __thiscall with one stack argument); only the existing local named buttonX
         * actually holds DAT_ButtonY.
         */
        void __cdecl RenderButtonImageWithBlending();

        /**
         * Draws the current button's picture (getPictureNumberInGm(isInteracting)) at DAT_ButtonX/Y on the screen-
         * menu surface via drawTgxGmOnFlaggedSurface, records DAT_CurrentButtonPictureInGm and restores the map-
         * game target. Displayed argument names are shifted by the thiscall misdecompilation.
         */
        void __cdecl RenderCurrentButtonOnScreenMenu();

        /**
         * If blendStrength != 32, draws the current button's picture (getPictureNumberInGm(isInteracting)) blended
         * with the blendStrength argument onto the screen-menu surface at DAT_ButtonX/Y, records
         * DAT_CurrentButtonPictureInGm and restores the map-game target. The decompiled call shows DAT_ButtonY as
         * the blend value; that is a thiscall argument shift.
         */
        void __cdecl RenderCurrentButtonOnScreenMenuWithBlending(int blendStrengthUnk);

        /**
         * Converts 8-bit RGB to a 16-bit pixel for the current colour mode: RGB555 (5/5/5, red<<10) or RGB565
         * (5/6/5, red<<11).
         */
        uint __cdecl TransformToCurrentModeColor(int red, int green, int blue);

        /**
         * Draws the load/save progress bar, throttled to once per >30 ms. Progress 0..1000 maps to 0..300 px; the
         * bar is 15 px high at MenuTextInputState field40_0x94/field41_0x98. In-game it draws on the map surface,
         * sets mbr_0xd0 (2 for tabs 60/62 outside the building/status menu, else 1) and does renderBltAndFlip. In
         * menus it draws the bar and blts only the bar region.
         */
        void __cdecl RenderLoadAndSaveBar(int progressValueUnk);

        /**
         * Renders a basic scenario-editor button and its caption TEXT_SCENARIO[textNumInGroup], centred at button
         * y+6 (brighter colour while interacting).
         */
        void __cdecl RenderScenarioButtonWithText(int textNumInGroup);

        /**
         * Draws the animated tutorial pointer: GID_FLOATS_NEW frames 0x105..0x10E with alpha masks 0x10F..0x118, 10
         * frames of 60 ms. The position is (mainMenuBorderWidth + x - 36, y - 101 + resY - 600), drawn once on the
         * screen-menu surface and once on the map-game surface with the camera offset added. Skipped while
         * g_tutorialTransitionState != 0. BUG (confirmed): for 1680x1050 the y offset is 0xFD2 (4050) instead of
         * 450, so the pointer is drawn far below the screen.
         */
        void __cdecl RenderAnimatedTutorialFloatOverlay(int x, int y);

        /**
         * Shows the tutorial pointer for a tutorial UI element id (2 keep, 5 granary, 8 rations, 10 taxes, 0x11
         * quarry, 0x15 water pot, 0x18 hop farm, etc.) at a hard-coded panel position. It is shown while the step's
         * condition (current mapper command, active tab, tutorial sub-step, rations/taxes setting) is not yet met;
         * ids 0x10 and 0x17 are shown unconditionally. In the building/status menu only ids 8, 10, 11 and 12 are
         * shown.
         */
        void __cdecl RenderTutorialFloatForUIElement(int tutorialElementId);

        /**
         * Draws the end-of-game 'Greatest Lord' table. Computes per-player troops killed (row sums of
         * finalKillMatrix) and troops lost (column sums incl. row 0), bubble-sorts player slots 1..8 by Skirmish-
         * master score (ties: time alive, alive flag) and by 15 statistics (troops lost and buildings destroyed
         * ascending, rest descending; a 16th rank array is initialised but never sorted), gives the score leader +3
         * points and each category leader a bonus if above a threshold and more than twice the runner-up, converts
         * points/3 to 0..5 stars (max 4 when finalResults.active[1] is 0) and renders, for the 8 slots ordered by
         * DAT_FinalResultsOrderByColumn: name, an extra 0x8b icon if alive, stars, killed-lord icons, date of death
         * and the numeric columns of the page DAT_EndscreenStatsPage. Without extreme mode it prints the sort-column caption
         * (plus the date range, formatted into the reused local_30c buffer, for column 0); in extreme mode
         * (isExtremeTrailGame) it instead prints the extreme score, the -M%d-%d.sav save name and the submit-score URL in
         * a white box. BUG (confirmed): the max-population bonus (+1) is added to the troops-killed leader
         * (local_30c[1]) instead of the max-population leader.
         */
        void __cdecl RenderGreatestLordScreen();

        /**
         * Draws the scenario briefing objectives page. When section1095 == 2 it only prints the alternative title
         * TEXT_OBJECTIVES 0x1A; otherwise it prints title 0 and, for each of the 0x27 enabled scenario conditions
         * (0x12/0x13 skipped in GM_CUSTOM_MAP mode), its label, target value (plus goods name for resource goals)
         * and, when the briefing was opened in-game, the current player's actual value in parentheses, with a
         * tick/cross icon (GM_INTERFACE_BUTTONS 6/5 from g_scenarioConditionIsTrue) in a column sized by a first
         * measuring pass. Adds slider-bar progress bars for the victory timer (condition 0x27) and, when condition
         * 8/0xF or INT_00ec02e8 is set, for one timed scenario event (a type-1 event with field +0x78 == 0 found
         * before the first enabled type-3 event of kind 1/0x1B, label 0xF; otherwise that type-3 event, label 0x11;
         * progress = months since scenario start vs the event's date). In GM_CUSTOM_MAP mode it also renders the
         * map name and the word-wrapped scenario description page (g_scenarioDescPageIndex, storing the page count
         * in g_scenarioDescPageCount). Returns the next free y coordinate.
         */
        int __cdecl RenderMissionObjectivesAndDescription();

        /**
         * Draws the avatar of player slot imageID at x,y: frame GM_INTERFACE_ICONS2 picture 0x222+slot, then for AI
         * slots (no human ID, AI character != 0) the portrait 0x20A+aiCharacter; for humans lord icon 0x21B
         * (lordIcons 0) / 0x21C (lordIcons 1), else, if a custom bitmap face is loaded (field69_0x98[slot+0x13] >
         * 0), frame 0x21D plus drawBitmapFace(slot+0x13) at +4,+4; otherwise no face.
         */
        void __cdecl RenderPlayerAvatars(int imageID, int x, int y);

        /**
         * Draws loaded gfx loadedGfxIndex at the given position relative to the main-menu border. A 1024x768 image
         * is centred on screen (position ignored); an image that fits inside the bordered menu rect is drawn with
         * renderLoadedGfx, otherwise with drawGfxOnFlaggedSurface. NAME? effectively RenderLoadedGfxInMenuRect.
         */
        void __cdecl RenderLoadedGfxInMenuRect(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect);

        /**
         * Draws a TGX gfx with blending at (x,y) offset by the main-menu border width/height.
         */
        void __cdecl RenderMenuGfxHelper(int gfxIndex, int x, int y, int blendStrength);

        /**
         * Renders stored menu string DAT_ArrayOfStoredMenuStrings[index] at a position offset by the main-menu
         * border: wrapped multiline text with maxWidth when isSingleLine is FALSE, otherwise a single centred line.
         */
        void __cdecl DrawLoadedMenuStringHelper(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
            int fontSize, BOOLEnum isSingleLine);

        /**
         * Same as DrawLoadedMenuStringHelper but passes blendStrength to the text renderer (fade in/out of
         * credits/history strings).
         */
        void __cdecl DrawLoadedMenuStringHelperWithBlending(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth,
            uint color, int fontSize, BOOLEnum isSingleLine, int blendStrength);

        /**
         * Per-frame credits text page: scroll offset = ms since page start / 80 (elapsed > 1e6 treated as 0, offset
         * max 0x244); blits a 540x220 window of the off-screen map-game surface (where DisplayFullScreenTextPage
         * rendered the text) starting at that offset to the menu surface at border+20, then draws 30 blended black
         * lines (strength 2..31) as fades at the top and bottom edges. NAME? it scrolls the text rather than
         * drawing a progress bar - RenderScrollingTextPage.
         */
        void __cdecl RenderTextPageProgressBar();

        /**
         * Starts a full-screen credits text page: clears the off-screen map-game surface (box 0,0,600,800) to
         * black, renders stored menu string menuStringIndex there as wrapped text at (15,0xCD) width 0x20D, stores
         * the text renderer's resulting y (field1_0x4) + 0xD7, min 0xDC, in textPageContentBottom, resets the scroll offset,
         * restores the text/pencil surface targets and stores timeGetTime() as page start.
         */
        void __cdecl DisplayFullScreenTextPage(int menuStringIndex);

        /**
         * Advances a looping animation counter (historyBookAnimFrame += frameTimeScale/6, reset to 0 at 50) and draws
         * loaded gfx DAT_MissionDefinedData.historyBookPageGfx[frame]+1 at menu position (0x2A0, 0xF) via
         * RenderGfxHelperUnk.
         */
        void __cdecl RenderHistoryBookEdgeUnk();

        /**
         * Fallback renderer: dims the whole screen with a 4x4 pixel pattern and draws a centred white 400x40 box
         * with the text 'No views have been found.'.
         */
        void __cdecl RenderNoViewsFoundWarning();

        /**
         * Walks the MenuView linked list and, for the view matching DAT_GameCore.currentMenuViewType, calls prepare
         * (when TriggerPrepare), doInitial (when TriggerInitial or TriggerPrepare) and doEveryFrame; for
         * MVT_NO_VIEW it only shows the 'no views' warning when TriggerInitial is set. Clears both trigger flags
         * afterwards.
         */
        void __cdecl RenderCurrentMenuView();

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
