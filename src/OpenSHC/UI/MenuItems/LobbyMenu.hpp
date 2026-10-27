/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/LobbyMenu.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace LobbyMenu {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Lobby map-select table header render: unless a modal or the round table is open, draws a table-cell
             * background and one of three column header texts from TEXT_XPLAY_WAITING_ROOM (0x3E/0x3D/0x19A for
             * item 0/1/2) at x offset 8 or 2, in a brighter colour while the button is being interacted with.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int param_1, ...);

            /**
             * Lobby player list render callback, dispatched on item param; all row items map to a slot via
             * DAT_RoundTableOrderArray. 0 = column headers (Players, Status if multiplayer, Eject if host); >10 =
             * info row for order index param-10: team-coloured strip, hover tooltip (you / computer / human + team)
             * and text 0x192 (human) or AI lord name; 1..10 = round-table row (host marker, player shield, player
             * or AI lord name); -9..-1 = ready-flag button (graphic 0xCF/0xCE by DAT_PlayerSlotArraySomeValue,
             * interactive only on own row) or AI type icon (0x272/0x273); <= -200 = eject button (host only, hidden
             * for self and once a kick was sent, shown for AI players); -0x65 = enabled only while a round-table
             * row is free; -0x66 = host button usable with no modal or a lord-select modal; -0x67 = enabled only in
             * single-player skirmish. Row lookups: 1..10 use DAT_RoundTableOrderArray[param], -9..-1 use [-param],
             * >10 use [param-10] and eject buttons use [-200-param] (the decompiler shows the latter as byte
             * offsets from mapPartTransferState / GameSynchronyState).
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...);

            /**
             * Lobby map description panel render: draws a translucent box (with yellow frame and scrollbar track
             * lines when not fading), then, if a map is selected, clips to the panel and draws the map title, '-',
             * the balanced/unbalanced label (text 0x19B/0x19C by GameCore.savedMapBalance) and the description
             * (TEXT_MAP_NAMES entry if mapDescUseStringTable, else GameCore.mapDescription), scrolled by
             * mapDescScrollOffset. Host takes the name via mapNames_getLoadedMapNameForIndex, clients use the
             * synced mapName.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_MapDesc(int param_1, ...);

            /**
             * Scrollbar callback for the lobby map description: event 1 initialises range (min -0x13, max = text
             * height minus visible height 0xCC or 0x6E by variant, current 0), 2/3 store the new scroll offset in
             * g_lobbyMapDescScrollOffset, 4 returns range and current offset, 7 sets *currentValue =
             * visibleHeight-14 (page step). Ignored while a lord-select / round-table modal is open or DAT_MenuFadeState
             * is set.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback for the lobby map description scrollbar: draws the scrollbar with the given thumb
             * position/height unless a round-table / AI-lord-select modal or another modal dialog is active.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_MapDescScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Lobby skirmish game-type/advantage render: item 4 draws the advantage slider and its marker (frame
             * 0x2A2+balance), item 0x14 draws the game type name, the advantage-side text (when balance <3 or >3)
             * and two numbers from a table indexed by (balance + intensity*5)*2+12/13 (x3 on an Extreme skirmish
             * trail), items 1..3 draw the intensity buttons with the selected one highlighted; items 10..19 draw
             * nothing. Buttons are disabled for non-hosts and while a round-table/lord-select modal is open.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...);

            /**
             * Lobby skirmish type/balance click handler (host only, ignored for items 4 and 0x14 or when
             * DAT_MenuFadeState is set): params 1..3 set the game intensity type, params >=10 set the advantage balance
             * (param-9) and play a selection sound; then queues GCT_CHANGE_GAME_INTENSITY_OR_BALANCE.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...);

            /**
             * NAME? Lobby render callback that draws the bottom-left help/info text (BottomLeftTextDisplayState)
             * when no modal dialog is active; could be named ..._BottomLeftText.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_BottomLeftText(int param_1, ...);

            /**
             * Lobby chat box render (multiplayer only): item -3 draws the chat history box and message list
             * scrolled by field237_0x1072f0, -2 the input line with text cursor and current typed text, -1 the
             * local player's name label, other values a TEXT_XPLAY_WAITING_ROOM string label.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_ChatBox(int param_1, ...);

            /**
             * Lobby buttons render dispatcher by item param: 1 = multiplayer host button, fully enabled only when
             * every occupied human slot is ready and checkPlayerSetValid()>1 (else dimmed, not drawn in skirmish);
             * 4 = host start button enabled when all ready, >=2 valid players, a map is selected and
             * mapAvailabilityArray[map] >= 1; 0x69 = send-map button (host, map selected, availability entry 0, no
             * transfer running); 2/3 = plain/text buttons; -0x14 = own ready toggle; -200 = keep-position hover
             * detection on the lobby minimap (sets DAT_LobbyMinimapHoveredKeepIndex); -0x65/-0xB/-2 and -100/-10/-1
             * = up/down scroll arrows; 0x19D = skirmish-only button. Most buttons are disabled while round-table /
             * lord-select modals are open.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_NonBoxedButtons(int param_1, ...);

            /**
             * Lobby map-select table row click (host only, no lord-select/round-table modal): selects the row if
             * scrollOffset+row is below the map count and queues GCT_CHANGE_MAP_SELECTION.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectTable(int param_1, ...);

            /**
             * Lobby map-select table row render: draws the row cell (host: highlighted if it is the selected row;
             * client: highlighted when the row's map name equals the host's synced mapName), then the map's player
             * count, a balance icon (mapBalanceArray), an optional extra icon (mapU4Int0_2Array) and the (possibly
             * localized) map name. Rows whose mapAvailabilityArray entry is < 1 are drawn grey. Disabled while a
             * round-table/lord-select modal is open on the host. The map-name lookup's description-index out value
             * (local_4) is ignored.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectTable(int param_1, ...);

            /**
             * Scrollbar callback for the lobby map list (8 visible rows): 1 reports range 0..total-8 and the
             * current offset, 4 the same but re-syncs *currentValue to the offset, 2/3 apply a dragged offset, 5/6
             * scroll up/down by one, 7 returns page size 6. Any offset change made by the host queues
             * GCT_CHANGE_MAP_SELECTION. Ignored (except event 1) while DAT_MenuFadeState is set.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback for the lobby map list scrollbar: draws it when no lord-select / round-table modal is
             * open, otherwise marks the button disabled.
             */
            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Lobby map list column header click / sort: bubble-sorts mapIndexList by map index (column 0, toggling
             * mapListSortMode 1 asc / 2 desc), by mapBalanceArray (column 2, mode 3 asc / 4 desc) or by
             * (playerCount + mode-5) mod 8 (column 1, modes 5..11), where column 1 advances the mode and re-sorts
             * (max 7 times) until the first entry has player count 13-mode, i.e. skips player counts no map has.
             * Always resets mapAbsentAckCountdown. A negative param -m re-applies saved mode m, then re-locates
             * DAT_MapNameCache in the list to set scroll offset/selection (7 visible rows); a non-negative param
             * (ignored while fading or an AI/roundtable modal is open) sets g_lobbyForceSlotReallocation and re-
             * selects the current row via MapSelectTable.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectHeader(int param_1, ...);

            /**
             * Lobby player-list click handler (negative item params; ignored while DAT_MenuFadeState or the round table
             * is active): -0x65 opens the basic or extended AI lord select (host), -0x66 opens the round table
             * (host, closing a lord-select first), -0x67 opens the random-number-of-enemies dialog (host, single-
             * player skirmish, no modal); eject rows (<= -200, host): an AI lord in that round-table slot is
             * removed (message, position, GCT_HOST_REMOVE_PLAYER_BY_SLOT in MP), a human gets kick command 0x55
             * once; -9..-1 toggles the ready flag only when the row is the local player's, flag_0x7aad8 is set and
             * not in single-player skirmish, then queues GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS.
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...);

            /**
             * Lobby standalone button click handler (ignored while DAT_MenuFadeState or a text-input modal is active): 1
             * = load game (host, all humans ready, >1 players), 2 = leave lobby (skirmish: main menu; MP: end-of-
             * game mode and quit), 4 = start game (all humans ready, >1 players, selected map usable; skirmish
             * launches directly, MP queues GCT_START_MULTIPLAYER_GAME), 0x69 = send selected map, 0x19D = rankings
             * view, -200 press / -0xC9 release = drag-swap start positions on the minimap (host), -0x65/-100 scroll
             * the map description by 14 px, 3/-0x14 = client toggles own ready flag (flag_0x7aad8 set,
             * DAT_TwoIfNotHost==2) and a ready host queues GCT_CHANGE_GAME_INTENSITY_OR_BALANCE, -10/-0xB scroll
             * map list, -1/-2 scroll chat (0..15).
             */
            void __cdecl MenuItemActionHandler_LobbyMenu_NonBoxedButtons(int param_1, ...);

        } // namespace LobbyMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
