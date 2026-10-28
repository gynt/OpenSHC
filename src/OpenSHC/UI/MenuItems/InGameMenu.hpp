/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/InGameMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace InGameMenu {

            /**
             * Per-frame in-game menu handler: while a bink video is flagged as playing, clears the flag once the
             * second bink slot has no video and forces a redraw (GameCore.countdown = 1). Parameter unused.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_UpdateMessageVideoPlayingFlag(int param_1, ...);

            /**
             * Scribe (popularity book) animation, skipped in editor and Siege That modes. While a scribe reaction
             * runs it ticks every 60 ms: phase 0 walks scribeAnimationFrame towards 6 and then enters phase 1,
             * phase 1 advances scribeAnimationFrame2, phase 2 steps the frame towards the popularity frame ((100 -
             * popularity/100)/10 + 1) and ends the reaction there. Every call it then picks the frame: no reaction
             * -> the popularity frame; reactions 1-3 in phase 1 -> scribeAnimFramesA/B/C[frame2], where a 0 entry
             * ends the reaction and keeps the current frame. Sets GameCore.countdown = 1 (redraw request) when the
             * frame changed or the month changed.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int param_1, ...);

            /**
             * Keyboard 'view to keeps' handler (scroll events 7/8, press counter reset after 1 s): event 7 acts on
             * every second press and cycles the camera through a list whose position 0 is the player's own keep and
             * positions 1..n are the valid (>= 0) entries of the 10-entry tile list mapAndTime.field22_0x58, using
             * GameCore.viewToKeepsTargetIndex as cursor (wraps after the last valid entry); event 8 on a second press focuses
             * the player's own keep.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_ViewToKeeps(int param_1, ...);

            /**
             * Edge/keyboard scroll handler: updates the debug-number display element, then (unless box-selecting or
             * right-click held) moves viewportX/Y by the scroll distance in the current ScrollingHandler direction,
             * scaled up when the framerate is below the game speed, clamps the viewport to the map and records the
             * tutorial action.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_Scrolling(int param_1, ...);

            /**
             * Mini-map interaction handler: for param 2 it just releases menu handling (DAT_StopHandlingMenuItems =
             * 0) unless TileMapState.mapInteractionMode == 1 and the active tab is not the siege-tent tab; otherwise,
             * unless a wall/stair/crenel placement is being dragged or MouseState.selectionBoxActive is set, it closes
             * the bink modal if a video plays or (when no building/peasant bink plays) scrolls the main viewport to
             * the clicked minimap position.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_MiniMapInteraction(int param_1, ...);

            void __cdecl MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection(int param_1, ...);

            /**
             * Per-frame in-game mouse handler for unit selection and orders (the stack argument is never read).
             * Handles drag-box/point selection (interaction mode 3 = shift-add; a click in mode 2 first deselects
             * everything), auto-selecting a freshly built siege engine, siege-tent build-menu tab switching, and
             * tactical-power targeting (mode 5 waits for button release; mode 4 rejects the target tile when the
             * own lord is dead, when its squared tile distance from the own keep exceeds 2500 (50 tiles) or 12544
             * (112 tiles) for power 3 - in Extreme it may instead lie within that radius of the own living lord -
             * or when it is within 25 tiles of a non-allied keep, unless (Extreme) that enemy lord is alive and the
             * tile is inside the same radius around him; on click it queues GCT_ACTIVATE_TACTICAL_POWERS). With
             * units selected it chooses the context cursor/pending order (attack unit/building/wall in weapon
             * range, man siege engine, exit siege engine (not while a manning engineer is still in state 0x6D
             * US_FADE_TRANSITION), ignite pitch ditch, ladder, dig/fill moat, move, no-entry; double-click on a
             * selected unit selects all of its type; the lord may only use a few of these; strong-walls skirmish
             * rule blocks wall attacks with text 0x69) and on click dispatches it through the
             * GCT_GIVE_UNITS_INSTRUCTION (36) unit-instruction command (attack, man/operate engine 0x10/0xF,
             * ignite 0x22, attack building 9 (0x24 in attack mode 5), attack wall tile 0x17 (0x23 in mode 5), place
             * ladder 0x18, facing 0x14), move with double-click flag 0x81, rally/patrol waypoints, attack ground
             * and throw cow. Finally sets MouseState.cursorOverlayMode = cursorMode+1 (stays -1 if no cursor was
             * chosen).
             */
            void __cdecl MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk(int param_1, ...);

            /**
             * In-game mouse handler for wall / wood-wall / stair / crenel placement (only when not syncing/saving
             * and the mouse is over the viewport): sets MouseState.cursorOverlayMode = 1000, tracks drag start/end
             * tiles from the mouse tile, counts buildable wall tiles (getWallTilesThatCanBeBuilt) and validates the
             * path. Until the drag is released it renders the wall preview (field145_0x554980 = button not held,
             * i.e. hover-only); on release it queues GCT_PLACE_WALL (start XY, end XY, mapper, tile count) if the
             * build is legal, otherwise shows the failure text when the reason is not the default one.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand();

            /**
             * Right-mouse camera drag (stack argument unused): clears MouseState.mouseBasedEvent; over the
             * viewport, a new right-click with no mapper active (and not in a siege-tent build tab) stores the
             * mouse XY, sets previewEnabled = 1 and GameSynchronyState.editorPlacementPlayerID = 1; while the right
             * button stays held with previewEnabled it calls updateRightDragCameraControl; in all other viewport
             * cases previewEnabled is cleared.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_RightClickDragCamera(int param_1, ...);

            /**
             * Click handler for the in-game main/toolbar buttons, dispatched on the button action id: -1/-6 pause
             * menu (editor: map properties, Siege That: create-siege view), -2 confirm pending destruction, -3
             * delete tool, -4 re-enable menu item handling, -5 open the mission briefing (scenario description, or
             * crusade mission intro for skirmish trail; stops Bink/speech and closes modals), -0x5a allies dialog,
             * -0x5b greatest-lord table, editor -10..-99 select player slot (-9 - id), -0x65/-0x66 editor
             * landscaping / test mode. 0x47..0x4F open that building-and-status tab (forced to 0x4C in
             * tutorial/siege/no-keep-with-army cases, ignored in editor/Siege That); any other id opens that build-
             * menu tab unless already active, with a tab SFX for ids 10/0x14/0x19/0x1C/0x1E/0x28.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_MainButtons(int param_1, ...);

            /**
             * In-game mouse handler while a placement mapper is active (stack argument unused): shows the mapper's
             * info/cost text, then per mapper previews (floating element / footprint) or, on release, places:
             * mangonel/ballista on an own large-tower top with no unit or engine (GCT_SIEGE_TENT),
             * heads/flags/brazier decorations (GCT_SPAWN_ENTITY; brazier in Siege That needs enough gold), assembly
             * points for barracks/mercenary post/engineers/tunnelers (Param0 0x1E)/cathedral (Param0 0x28) after a
             * path-reachability check from the building's parade ground (or campground), queued as GCT value 102
             * (0x66, handler table 0xB38E10[102] = 0x00485830 SetUnitAssemblyPoint; the decompiler shows it as
             * GCT_SHARE_GAME_STATE_PARTIAL_HASHES|GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST) with Param1/2 = clicked
             * tile, then the mapper is cleared; troop placement (Actions::PlaceUnit), moat/anti-moat/dug brushes
             * (GCT_SET_TERRAIN; refused when getUnownedMoatCount() < 15 (same 'too many' text 0x14d, so it behaves
             * like a free-slot count), within the signpost radius + 5 or off a valid castle site; multiplayer
             * throttled to one per ~200 ms), pitch ditches (refused when countUnownedPitchDitches() < 15; painted
             * while the button is held, same throttle) and normal buildings (checkBuildingCanBePlacedHere, free
             * building slots must be >= 20, >= 11 for siege engines, >= 3 for tunnels; GCT_PLACE_BUILDING with gate
             * rotation). After placing it triggers the scribe reaction (2 for
             * gardens/statues/shrines/ponds/well/maypole/dancing bear, 3 for
             * gallows/stocks/cesspits/dungeon/torture devices) or, for siege engines, plays speech 0x15 and clears
             * the mapper; an invalid release shows the failure text/warning sound, and hovering a siege engine
             * shows a tent preview offset by map orientation.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand(int param_1, ...);

            /**
             * Render function for the in-game main/toolbar buttons (keyed by button action id): marks the button
             * disabled/hidden (DAT_ButtonDisabled = 1) when not applicable to the current mode (editor/Siege That,
             * solitary vs skirmish trail, barracks/mercenary menus, battering-ram siege tab), picks a picture
             * offset (2 = active tab or no pending destruction, 8 = current editor player slot for ids -10..-99)
             * and renders the button GM at its base picture (+hover) + offset; with no keep/granary yet (or the
             * stocks tab open) build-tab buttons are drawn greyed with absolute pictures 0x36..0x3B. Draws two
             * black separator lines for -4 and the scribe frame plus gold/population/popularity for 0x47.
             */
            void __cdecl MenuItemRenderFunction_InGameMenu_MainButtons(int param_1, ...);

            /**
             * Render function of the spawn-event locator button (stack argument unused): rendered and enabled
             * (DAT_ButtonDisabled = 0) only while MinimapViewState.spawnMomentCount != 0 and no Bink video is
             * playing; otherwise DAT_ButtonDisabled = 1.
             */
            void __cdecl MenuItemRenderFunction_InGameMenu_SpawnEventLocatorButton(int param_1, ...);

            /**
             * NAME? Click handler of the spawn-event locator button (pair of
             * MenuItemRenderFunction_InGameMenu_SpawnEventLocatorButton; stack argument unused): centers the view
             * on the oldest queued spawn event (spawnMomentX/Y[0]), shifts the X, Y and timestamp queues (20
             * entries each) down by one and decrements spawnMomentCount.
             */
            void __cdecl MenuItemActionHandler_InGameMenu_SpawnEventLocatorButton(int param_1, ...);

            /**
             * In-game menu render callback for the 'keep enclosed' symbol: checks whether the local player's keep
             * is enclosed by walls, sets GameCore.countdown=2 when the state changed since last frame, caches the
             * state, and either hides the button (DAT_ButtonDisabled=1, keep not enclosed) or renders the
             * current button.
             */
            void __cdecl MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol(int param_1, ...);

            /**
             * In-game menu render callback: if VideoBikQueue.displayedSenderPlayer is non-zero (a Bink message tied to a
             * player, sign stripped), draws that player's shield icon (INTERFACE_ICONS2 frame 0x1D5+player) at the
             * button position on the screen-menu surface.
             */
            void __cdecl MenuItemRenderFunction_InGameMenu_BikMessagePlayerShield(int param_1, ...);

        } // namespace InGameMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
