/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Commands.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {
    namespace Commands {

        /**
         * Queues GCT_CHANGE_GAME_INTENSITY_OR_BALANCE and resets GameSynchronyState fields 0x1072e8 and 0x1072ec to
         * -1.
         */
        void __cdecl QueueChangeGameIntensityOrBalance();

        /**
         * If the local player's tax slider differs from taxesSetting2, it queues GCT_CHANGE_TAXES with the new
         * value and records the change time. In the Crusader tutorial, a disallowed change resets the slider and
         * shows a hint, and an allowed one updates the tutorial action state.
         */
        void __cdecl QueueChangeTaxes();

        /**
         * Network command with no payload. In the send phase it just switches to execute, and when executed it sets
         * DAT_HostAnnounced = 1.
         */
        void __cdecl InitialAnnounceReply();

        /**
         * Network command carrying a 4-byte game version (0x2A004C). The sender serializes it; on execute it stores
         * the received version in DAT_MultiplayerGameVersions[invokerPlayer] for players 1..8.
         */
        void __cdecl AnnounceGameVersion();

        /**
         * Lobby network command (0x250 bytes). The sender serializes its slot ID, lord icon, lord type, its user
         * name (as a 500-byte wide string) and its AIV availability table (0x50 bytes). On execute, only if the
         * received slot ID != 0 (the slot comes from the payload, not protocolInvokerPlayerID): stores the name in
         * DAT_PlayerNames[slot] and the 90-byte results name table (0x1A26D2C + slot*0x5A), the AIV availability in
         * DAT_ReceivedAIVFileAvailabilityPerAIArray[slot], the lord icon and type, and marks the slot as an
         * included player. It also re-copies the local user's name into its own slot and results entry; the host
         * then re-checks lobby AIV availability.
         */
        void __cdecl AnnouncePlayerInformationSuchAsNameLordTypeAndAvailableAIVS();

        /**
         * Host start-game network command (0x7DC bytes): RNG seed, autosave interval, game speed and the selected
         * map name (wide string, 2000 bytes). The sender converts
         * mapNames_getLoadedMapNameForIndex(ArrayOfMapIndices[scroll+selected-1]) to wide chars (max 1000) in the
         * same stack buffer. Receivers store the values, convert the map name into GameSynchronyState.mapName,
         * update the session description and call LaunchSkirmishGame(0). Decompiler artefacts: the map index is the
         * argument of mapNames_getLoadedMapNameForIndex, not 'numberOfSymbols' (the size is the constant 1000
         * pushed earlier), and stack0xfffff824 is local_7d8.
         */
        void __cdecl ShareGameSeedAndMultiplayerSettingsAndStartGame();

        /**
         * Periodic sync-check command (10 bytes): the sender's lag indicator (2 bytes), game-state hash total (4
         * bytes) and match time (4 bytes). On execute they are stored per invoking player so they can be compared
         * for desync detection.
         */
        void __cdecl CommandCheckSync();

        /**
         * Lobby network command (0x21 bytes) announcing the sender's DAT_PlayerSlotArraySomeValue entry, its AI
         * character, AI variation, host flag, the 9-byte player group array and the 8-byte position array. On
         * execute (invoker 1..8) the slot value goes to the invoker's slot. BUG (original game): the AI character
         * and variation are written into the LOCAL player's slot (currentPlayerSlotID), not the invoker's. The
         * group array is adopted only if the sender's host flag is set; positions are always overwritten.
         */
        void __cdecl AnnounceTeamsAndPositions();

        /**
         * Selection-change network command (4 bytes: two shorts). On execute param0 is sign-extended and passed
         * with param1 to UnitsState::clearOrDeselectUnitFromSelection(invoker, param0, param1): -1 clears the
         * selected tribes of unit type param1, -2 clears tribes NOT of type param1
         * (UnitsState::queueClickNavigateMenuOrEscape queues it with -2), 0 deselects all of the invoker's units,
         * and any other value removes that unit from its tribe and deselects it. NAME? It changes the unit
         * selection; it is not menu navigation.
         */
        void __cdecl ClearOrDeselectUnitSelection();

        /**
         * Network command (0x192 bytes) carrying the 400-byte selectedUnitsBitFlags bitmap and a 2-byte parameter.
         * On execute it overwrites the bitmap and calls playerMakeUnitSelection(invoker, param).
         */
        void __cdecl MakeUnitSelection();

        /**
         * Move-unit network command (8 bytes): three shorts (param0..2) and two signed bytes (param3, param4). On
         * execute it calls giveTribeMoveInstructionHumans with these values.
         */
        void __cdecl ClickMoveUnit();

        /**
         * Map-editor erase network command (5 bytes): x (short), y (short), brush size (byte). On execute it calls
         * TileMapState::eraseAreaWithBrush(x, y, size).
         */
        void __cdecl ClickErase();

        /**
         * Map-editor 'set land' network command (5 bytes): x, y (shorts) and brush/land byte. On execute, if (x,y)
         * is inside 400x400 and the per-tile byte at 0x21aec98[y*400+x] is set, it calls
         * TileMapState::setLand(tileIndex, y, param2). It then updates the walk/path layer, forces a macro-layer
         * update and redraws the minimap.
         */
        void __cdecl ClickSetLand();

        /**
         * Map-editor raise/lower land network command (6 bytes): x, y (shorts), brush size byte and a signed
         * height-delta byte. On execute, for a valid tile, it calls TileMapState::raiseLand, then updates pathing
         * and the macro layer and redraws the minimap.
         */
        void __cdecl ClickRaiseLand();

        /**
         * Map-editor set-terrain network command (10 bytes): x, y (shorts), brush byte, terrain type (int) and an
         * extra byte. On execute, for a valid tile, it calls TileMapState::setTerrain(invoker, tileIndex, y, brush,
         * terrain, extra) and updates pathing. It forces a macro-layer update unless the terrain is L_MOAT, then
         * redraws the minimap. Also used for editor moat placement.
         */
        void __cdecl ClickSetTerrain();

        /**
         * Map-editor level/equalize-height network command (6 bytes): x, y (shorts), brush size byte and a signed
         * byte. On execute, for a valid tile, it calls TileMapState::useLevelBrush, then updates pathing and the
         * macro layer and redraws the minimap.
         */
        void __cdecl ClickHeightEqualize();

        /**
         * Map-editor min/max terrain-height brush network command (6 bytes): x, y (shorts), brush size byte and a
         * signed mode/height byte. On execute, for a valid tile, it calls TileMapState::useTerrainHeightBrush, then
         * updates pathing and the macro layer and redraws the minimap.
         */
        void __cdecl ClickTerrainHeightMinOrMax();

        /**
         * Map-editor create-plateau network command (6 bytes): x, y (shorts) and two unsigned bytes. On execute,
         * for a valid tile, it calls TileMapState::createPlateau, then updates pathing and the macro layer and
         * redraws the minimap.
         */
        void __cdecl ClickCreatePlateau();

        /**
         * Wall-placement network command (12 bytes): four shorts (likely start/end tile coordinates), a 1-byte
         * wall/mapper type and a signed short. On execute it calls TileMapState::placeWalls(invoker, p0, p1, p2,
         * p3, type, p5).
         */
        void __cdecl ClickPlaceWall();

        /**
         * Map-editor place rock/tree network command (6 bytes): x, y (shorts), type byte and size byte. On execute,
         * type 0x14 places a rock with the given size via placeRock, and any other type places a tree of that type
         * via placeTree.
         */
        void __cdecl ClickPlaceRockOrTree();

        /**
         * Network command (6 bytes) carrying three shorts. On execute it calls PathFindingState::raiseLand2(p0, p1,
         * p2), updates the walk/path layer with mode 0x10, forces a macro-layer update and redraws the minimap. Its
         * exact editor tool is unclear.
         */
        void __cdecl ClickRaiseLand2Unk();

        /**
         * Place-building network command (10 bytes): x, y, building type (shorts), two bytes and the dragged tile
         * count. On execute, outside GM_SOLITARY, the building's resource cost is checked for the invoker (abort if
         * insufficient), and the verified drag count is stored. It then calls TileMapState::placeBuilding with the
         * owner taken from GameSynchronyState.editorPlacementPlayerID in the landscaping map editor, otherwise the
         * invoker.
         */
        void __cdecl ClickPlaceBuilding();

        /**
         * Destroy-building network command (7 bytes): building ID (short, sign-extended), refund flag (byte), UID
         * (int). An ID < 1 addresses pitch ditch -ID; it is destroyed via destroyPitchDitch(-id) if the UID in the
         * 20-byte pitch-ditch table (0x1FD2290 + n*0x14) matches. Otherwise, if the building UID matches, it first
         * destroys up to two BT_DRAWBRIDGEs found at the building (refund to invoker, no rubble). It then sets no-
         * rubble for the building itself, refunds it if field203_0x288 == 0, plays FX_TOWER_SMASH
         * (gatehouses/towers) or buildingwreck_01.wav when the owner is the local player, and destroys it.
         */
        void __cdecl ClickDestroyBuilding();

        /**
         * Recruit-unit network command (3 bytes): unit type byte and building ID short. On execute it calls
         * Actions::ProcessRecruitUnit(invoker, unitType, buildingID).
         */
        void __cdecl ClickRecruitUnit();

        /**
         * Removed/unused command slot: just sets the command size to 0.
         */
        void __cdecl _REMOVED_COMMAND1_();

        /**
         * Set-production-type network command (7 bytes): building ID short, produced item byte and building UID
         * int. On execute it calls Actions::SetBuildingProductionType.
         */
        void __cdecl ClickSetBuildingProductionType();

        /**
         * Change-taxes network command (1 byte). On execute it calls Actions::ChangeTaxes(invoker, taxSetting).
         */
        void __cdecl ClickChangeTaxes();

        /**
         * Change-rations network command (1 byte). On execute it calls Actions::ChangeRations(invoker,
         * rationsSetting).
         */
        void __cdecl ClickChangeRations();

        /**
         * Game command handler (size 15 bytes: 2+1+4+4+4). In SCHEDULE_AND_SEND mode serializes command params 0-4
         * into the command buffer; in EXECUTE mode deserializes them and forwards them to
         * UnitsState::relayTribeInstruction (tribe, instruction, two targets, extra arg).
         */
        void __cdecl ClickGiveUnitsInstruction();

        /**
         * Game command handler (size 7: 2+1+4). Sends/receives three params; on EXECUTE calls
         * Actions::OpenOrCloseDrawbridge(invokingPlayer, param0, param1, param2).
         */
        void __cdecl ClickOpenOrCloseDrawbridge();

        /**
         * Game command handler (size 2: 1+1). Sends/receives two byte params; on EXECUTE calls
         * Actions::ProcessBuyOrSell(invokingPlayer, param0, param1) for a market trade.
         */
        void __cdecl ClickBuyOrSell();

        /**
         * Game command handler for the destroy/eraser tool (size 5: tile index dword + signed byte). On EXECUTE: if
         * the byte is -1 it removes the moat owned at the tile (fillProgress reset, removeMoat) if any, and always
         * clears bit 0x400 of MiscDisplayLayer[tile]. Otherwise the byte is a refund percentage: it is halved
         * (signed) when HeightLayer - DefaultHeightLayer at the tile is <= 0x3C, the player gets stone back via
         * giveBackResourceForDestroyedBuilding(-1 = stone, player, percent), and the eraser tile effect is spawned.
         */
        void __cdecl ClickDestroy();

        /**
         * Game command handler (size 7: microX 2, microY 2, terrain height 2, unit type 1) placing a siege engine
         * from the siege tent. On EXECUTE: if currentGameMode != GM_SOLITARY a mangonel/ballista first needs
         * checkRequiredResourcesForBuildingOrPlanToBuy (else abort); a mangonel/ballista is refused if the building
         * on tile (x/8, y/8) already has containsSiegeMangonel1OrBallista2 set. Then spawnUnit(player, player, x,
         * y, height, type), deducts the mangonel/ballista building cost, and if the tile holds a
         * BT_TOWER1/BT_TOWER4 sets its hasUnitsOntop = 1 and field261_0x2fa = 100. For the local player it calls
         * startUnitDestructionConfirmation with the new unit.
         */
        void __cdecl ClickPlaceSiegeTent();

        /**
         * Game command handler (size 2). Sends/receives a 2-byte building id; on EXECUTE calls
         * Actions::ProcessBuildingSleepUpdate(invokingPlayer, buildingId) to change the building's sleep (work
         * stopped) state.
         */
        void __cdecl ClickBuildingSleep();

        /**
         * Game command handler (size 5: x 2, y 2, animal type 1). On EXECUTE, if x,y < 400 and the in-map mask byte
         * at 0x21AEC98[y*400+x] is non-zero, calls TribesState::createAnimal(type, x, y, HeightLayer[tile])
         * (HeightLayer = byte layer at 0x1D32C38).
         */
        void __cdecl ClickCreateAnimal();

        /**
         * Game command handler (size 7: 2+1+4). Sends/receives three params; on EXECUTE calls
         * Actions::GateOpenOrClose(invokingPlayer, param0, param1, param2).
         */
        void __cdecl ClickOpenOrCloseGate();

        /**
         * Multiplayer desync-diagnostics command. Computes the command size from which sharedDesyncFlags are set,
         * then serializes (send, own slot) or deserializes (receive, into the invoking player's slot) the
         * corresponding per-player hash blocks: units, buildings, trees, tribes, player data, section1023, logical
         * tile map, entities (0x2E7C bytes starting at int 25, though 12000 are reserved), moats, climb data, pitch
         * ditches, AIVs, heat maps, unknown2. On receive the host sets receivedSyncStatusByPlayerUnk[player] = 1
         * and records the announcement time; every receiver zeroes currentPacketTotalSize and field73_0xbdc.
         */
        void __cdecl ShareDesyncedHashes();

        /**
         * Lobby command: share the selected map (size 0x7D4 = index dword + 2000-byte UTF-16 map name). Send: index
         * = relative selection + scroll offset; looks up the map-list entry (0 for a negative index), gets its name
         * via mapNames_getLoadedMapNameForIndex and converts it (max 1000 chars) into the separate wide buffer
         * _mapName, which is serialized. Receive: unless GM_SKIRMISH_SINGLE_PLAYER with isSkirmishTrail, converts
         * the name back into GameSynchronyState.mapName; clears it for a negative index, calls
         * DisplayMapDescriptionAndAllocatePlayersToSlots and sets skirmishRelated1 = -1. (The decompiler's
         * 'numberOfSymbols' is the map index, and the wide buffer is _mapName, not &_selectionIndex - see SIGNATURE
         * note.)
         */
        void __cdecl CommandChangeMapSelection();

        /**
         * Lobby command (size 8: two dwords flag, index). On receive at the host, if flag is 0, clears
         * unknownMapRelatedReceivedDataArray[index] and sets field239_0x1072f8 to 50.
         */
        void __cdecl AcknowledgeMapExistence();

        /**
         * Lobby command (size 8: two dwords flag, index). On receive at the host, if flag is 0, zeroes the entry at
         * 0x11275F8 + index*4, i.e. DAT_ArrayOfMapIndices[index+499] = DAT_ArrayOfMapIndices2[index-1] - the second
         * map-list table, which (like the first) is accessed with a one-entry shift everywhere.
         */
        void __cdecl ShareMSVMapIndex();

        /**
         * Lobby/game-start command (size 0x50) that synchronizes the skirmish settings: unknown 16-byte setting,
         * start gold, default popularity, two intensity types, advantage balance, points, win condition, troop gold
         * cost, strong walls, alliances, no dogs, no cow throwing, no-rush, fog of war and the 8-byte player
         * positions array. Send serializes, receive overwrites the local settings.
         */
        void __cdecl ClickInitOrChangeGameIntensityAndBalance();

        /**
         * Lobby command (size 16: four dwords) sharing a player's slot assignment: slot id, source player index
         * (DAT_SomePlayerID), lord icon and selected lord type. On receive, stores lordIcons[slot] /
         * selectedLordTypes[slot]; the host additionally, when slot != source, copies
         * currentPlayerFullIDArray[slot] = DAT_CurrentPlayerFullIDArray2[source] and the name playerNames2[source]
         * into DAT_PlayerNames[slot] (0x1A23384 + slot*250), then sets somePlayerRelatedArray[slot] = 1 and
         * unknownPlayerInfo_01[source] = 1. Finally copies the 0x2100-byte face bitmap of entry source+0x1B into
         * entry slot+0x13 and sets field69_0x98[slot+0x13] = 0x2100.
         */
        void __cdecl SharePlayerName();

        /**
         * Resync command (size 0x9D8 = layer id + chunk index + 0x9D0 bytes) for byte tile layers. The sender
         * serializes chunk param1 (0x9D0 bytes) of layer param0 (10 damage, 11 luminescence, 12 wall owner, 13 path
         * linkage, 14 occupancy, 15 height, 16 AI info, 17 AI zone, 18 tilemap1104, 19 unit death heat map, 20-28
         * pathfinding cost maps 0-8); a non-host receiver deserializes it into the same layer chunk.
         */
        void __cdecl SendResyncCharLayer();

        /**
         * Resync command (size 0x9D8) for 16-bit tile layers: transfers chunk param1 (0x4E8 shorts = 0x9D0 bytes)
         * of layer param0 (1 random, 2 walk, 3 organism, 4 building, 5 unit, 6 entity, 7 certain path, 8 path
         * connection, 9 macro). Sender serializes, non-host receiver deserializes.
         */
        void __cdecl ResyncShortLayer();

        /**
         * Zero-size sync status command. On receive the host sets receivedSyncStatusByPlayerUnk[invokingPlayer] = 2
         * and records the announcement receive time/flag.
         */
        void __cdecl ResyncStatus2();

        /**
         * Zero-size command: on execute clears syncStatus and flag_0xbec and calls
         * CheckDisplayElementByIDAndSetForUnlimitedDisplay(DEID_CONNECTION_LOST, 0) to hide that
         * multiplayer info element (apparently ends a resync/wait state).
         */
        void __cdecl ResetSyncStatus();

        /**
         * Game command handler (size 10: three shorts + dword). On EXECUTE reads three signed shorts and a dword
         * and calls Actions::ProcessTowerRepair(invokingPlayer, p0, p1, p2, p3).
         */
        void __cdecl ClickRepairTower();

        /**
         * Game command handler (size 9: owner byte, three shorts p1-p3, entity type byte, extra byte p5) that
         * spawns an entity via EntityState::spawnEntity(0, owner, p5, p1, p2, p3, p1, p2, p3, type, 0). In Siege
         * That mode (gameMode_2) a brazier costs gold: getBuildingCost(M_MAPPER_BRAZIER, &stone, &gold) and the
         * gold is deducted from the owner (param0, not the invoking player). For the local player it calls
         * startEntityDestructionConfirmation with the new entity.
         */
        void __cdecl CommandSpawnEntity();

        /**
         * Game command handler (size 3: short tribe/unit-group id + byte stance). On EXECUTE calls
         * TribesState::setUnitStance(id, stance).
         */
        void __cdecl ClickUnitStance();

        /**
         * Game command handler (size 7: short id, short x, short y, byte) for shift-click waypoints. On EXECUTE
         * calls TribesState::addRallyPoint(id, x, y, flag).
         */
        void __cdecl ClickExtendRallyPoint();

        /**
         * Thin game command handler (size 4: two shorts unitId, tribeId). On EXECUTE calls
         * UnitsState::selectSiegeEngineAndPlayFeedback(invokingPlayer, unitId, tribeId), which moves the unit from
         * its tribe into tribe tribeId as selected by that player and, for the local owner, plays engineer-
         * shortage/ammo/unit speech for siege engines. NAME? 'SiegeEngineRelated' -> e.g. 'AddUnitToSelectedTribe'
         * (works for any unit; only the feedback is siege-specific).
         */
        void __cdecl AddUnitToSelection();

        /**
         * Thin game command handler (size 2: one short tribeId). On EXECUTE calls
         * UnitsState::selectTribeUnitsForPlayer(invokingPlayer, tribeId), which sets ifSelectedThenPlayerID of
         * every unit in the tribe to that player and adds them to unitCountOfSelection[player]. NAME?
         * 'TribeRelated1' -> e.g. 'SelectTribeForPlayer'.
         */
        void __cdecl TribeRelated1();

        /**
         * Game command handler (size 6: short building id + dword). On EXECUTE calls
         * Actions::ProcessReleaseDogs(invokingPlayer, p0, p1) to release dogs from a kennel.
         */
        void __cdecl ReleaseDogs();

        /**
         * Game command handler (size 4: mode short + id short). Mode 1: sets entityArray[id].logicalState = 3. Mode
         * 2: if unit[id] is a mangonel/ballista, clears containsSiegeMangonel1OrBallista2 of the building on its
         * tile (if any) and refunds 100% of the engine cost to the invoking player (pseudo building id -3 mangonel
         * / -4 ballista); then, for any unit type, sets unit[id].logicalState = ULS_REMOVE. Other modes do nothing.
         */
        void __cdecl RemoveTowerSiegeEngine();

        /**
         * Game command handler (size 0x4BD: three dwords, kind byte, 0x4B0-byte wall placement info array). On
         * EXECUTE copies the placement info into receivedWallPlacementInfoArray and calls destroyWall (kind 3) or
         * destroyPitch (kind 4) with invokingPlayer and the three dword params.
         */
        void __cdecl DestroyWallOrPitch();

        /**
         * Game command handler (size 2: unit id short). On EXECUTE removes the unit from its owner's selection via
         * UnitsState::clearOrDeselectUnitFromSelection(owner, unitId, 0).
         */
        void __cdecl DeselectUnit();

        /**
         * Game command handler (size 1: byte, value unused). On EXECUTE sets
         * mapAndTime.multiplayerUnitSameTileLinkageTimeWindow to 100, opening a time window for recalculating unit
         * same-tile linkage.
         */
        void __cdecl TriggerRecalculationOfUnitSameTileLinkage();

        /**
         * Resync command (size 0x1904 = row index dword + 0x1900 bytes): the sender serializes row param0 of
         * WildlifeState.grid (40 cells x 160 bytes = 0x1900, address grid + param0*0x1900); a non-host receiver
         * overwrites the same row. NAME? more precisely 'ResyncWildlifeGridRow' (the grid is the 40x40 coarse zone
         * grid with area ids and animal/tree/keep counts).
         */
        void __cdecl ResyncZone();

        /**
         * Kick-player command (size 4: player slot). On execute: if the slot is the local player, plays
         * insult1.wav, records kickedAtTime, sets currentGameMode = GM_MULTIPLAYER_END_OF_GAME and runs the menu
         * quit action (action parameter 7, LaunchOrQuitMultiplayerGameUnk(0x16): disconnects and returns to the
         * multiplayer menus); otherwise clears currentAIArray[slot] (removes an AI there). In both cases calls
         * Actions::RemovePositionOfPlayer(slot).
         */
        void __cdecl KickPlayer();

        /**
         * Game command handler (size 3: short id + mode byte). On EXECUTE, mode 0 calls
         * Actions::TryAcquireAmmunitionOrPlanToBuyStone(invokingPlayer, id), otherwise
         * Actions::SelectionReplenishAmmo(invokingPlayer, id).
         */
        void __cdecl CommandSelectionReplenishAmmo();

        /**
         * Zero-size sync command. On execute every receiver sets syncRelatedStatusArray[invokingPlayer] = 1; the
         * host additionally records the announcement receive time and flag.
         */
        void __cdecl BroadCastSyncRelatedStatus();

        /**
         * Multiplayer command (size 4) executed on every peer including the sender. On send it also cancels all
         * pending DirectPlay messages (CancelMessage(0,0)). On execute: param 0 runs the menu quit action
         * (parameter 7, LaunchOrQuitMultiplayerGameUnk(0x16)); any other value sets playerIsAlive[0..8] = 0 and
         * switches to MVT_MISSION_FINISHED_TRANSITION. NAME? no player is targeted - this ends/aborts the game for
         * everyone rather than vote-kicking.
         */
        void __cdecl VoteKick_K_D_B_G_J();

        /**
         * Resync command (size 12) sent by the host: serializes currentPacketTotalSize, field73_0xbdc and
         * field67_0xba4; non-host receivers deserialize them, announcing the size of the upcoming resync data.
         */
        void __cdecl SyncPacketSizeAnnouncement();

        /**
         * Zero-size command. On execute the host sets announcementReceivedByPlayer[invokingPlayer] = 1 and records
         * the receive time and flag.
         */
        void __cdecl ShareAnnouncementWithHost();

        /**
         * Zero-size command. On execute clears saveRelated and closes the active modal dialog
         * (activateModalDialog(MMT_NONE)) on every machine.
         */
        void __cdecl CloseModalDialogForEveryone();

        /**
         * Command (size 500) broadcasting a player's name. Send: converts user text #0 (max 250 chars) to UTF-16
         * and serializes it. Execute: converts it into DAT_PlayerNames[invokingPlayer], copies it into
         * finalResults.names[invokingPlayer], and for every active chat event (flag == 1) whose subjectPlayer /
         * objectPlayer is that player, rewrites the subject / object name of that chat line (the subject array
         * appears as ObjectArray[i - 0x14]).
         */
        void __cdecl SomePlayerNameUpdateCommand();

        /**
         * Thin game command handler (size 4: two shorts x, y). On EXECUTE calls
         * TileMapState::spreadBrazierPlacementAlgorithm(invokingPlayer, x, y), which itself only forwards to
         * PathFindingState::spreadAlgorithmForFlagsAndBraziersUnk(player, x, y, 4, 1). NAME?
         * 'FlagsAndBraziersCommandUnk' could be 'PlaceBraziers'.
         */
        void __cdecl ClickDeleteFlagsAndBraziers();

        /**
         * Command (size 2: player id). On execute stores the lagging player id in laggingPlayerIDUnk, shows
         * multiplayer info element DEID_PLAYER_NOT_RESPONDING (the 'Not Responding' box) and resets
         * field131_0xcd4 to 0.
         */
        void __cdecl NotifyLaggingPlayer();

        /**
         * Command (size 2) sent by the host with field131_0xcd4; non-host receivers copy it and stamp DAT_SomeTime
         * = timeGetTime(). field131_0xcd4 is the TEXT_MULTIPLAYER_CONNECTION string offset (0x41/0x42/0x43) that
         * the host's lagging-player box sets (e.g. 0x42 after clicking 'Eject') before queuing a command; the non-
         * zero DAT_SomeTime makes the box show that message and hide after 2 s. NAME? not a ping - broadcasts the
         * lag-box outcome message.
         */
        void __cdecl ShareNotRespondingResult();

        /**
         * Command (size 0x30) sharing 12 partial game-state hashes: the sender serializes
         * HASH_PartialHashPerPlayer.player[ownSlot].domain01..12 (decompiler shows DAT_PlayerMatchTimes + 9 +
         * slot*12 + i, i.e. just past the 9-int DAT_PlayerMatchTimes); receivers store them into the invoking
         * player's element and set syncStatus10Related[invokingPlayer] = 1.
         */
        void __cdecl ShareGameStatePartialHashes();

        /**
         * Command (size 14) starting a resync/desync check: sender serializes the 14 sharedDesyncFlags bytes;
         * receivers copy them byte by byte into sharedDesyncFlags and set syncStatus = 1.
         */
        void __cdecl ResyncStatusStart();

        /**
         * Game command handler (size 5: point index byte, x short, y short) setting a troop assembly point for the
         * invoking player if (x,y) lies on the 400x400 map and the in-map mask byte at 0x21AEC98 is set. Index 0-9
         * -> barracksAssemblyPoints[idx], 10-19 -> mercenaryAssemblyPoints[idx-10], 20-29 ->
         * engineersAssemblyPoints[idx-20] (decompiler shows mercenaryAssemblyPoints[idx+1]), 30-39 ->
         * tunnelersGuildAssemblyPoint, 40-49 -> cathedralAssemblyPoint. If the target tile holds the player's own
         * producing building (barracks/merc post/parade grounds 2-4; engineers guild/parade ground; tunnelers
         * guild/parade ground 5; cathedral) the point is reset to (0,0). Indices are only range-checked against the
         * group limits, so e.g. idx 22+ would overwrite the tunnelers/cathedral points.
         */
        void __cdecl SetUnitAssemblyPoint();

        /**
         * Lobby command (size 1: map-status byte). On execute the host records field282_0x109d98[invokingPlayer] =
         * 1 if the byte is 0, else 2; then on any machine, once entries 1..8 are all non-zero (every slot
         * answered), opens the MMT_SEND_MAP_TO dialog.
         */
        void __cdecl StartSendingMapFile();

        /**
         * Lobby command (size 0x3EC: 1000-byte map name + file size) starting a map file transfer. Send: serializes
         * the loaded map name of index param0 (1000 bytes) and mapSendingFileSize, builds '<name>.map', resolves it
         * in the maps folder and stores currentPlayerFullIDArray[param1] (the addressee) in DAT_PlayerIDReceiver.
         * Execute on non-host: builds '<name>.map', fopen(..., "wb") into FILEPTR_ReceivedMapFile, sets
         * DAT_MapFileReceivingState = 2, resets the receive progress mapSendingByteBufferAddress[0] = 0 and opens
         * MMT_RECEIVE_MAP_FROM.
         */
        void __cdecl StartReceivingMapFile();

        /**
         * Map transfer acknowledgement (size 1). On execute the host sets field290_0x109e20[invokingPlayer] = 2
         * and, if the byte is 1 and a send file handle is open for that player, sets that player's transfer
         * progress mapSendingByteBufferAddress[player] = mapSendingFileSize (marking the transfer complete).
         */
        void __cdecl MapSendingRelated();

        /**
         * Lobby command (size 0x13: 9-byte DAT_PlayerGroupArray, 9-byte DAT_RoundTableOrderArray, 1-byte open
         * flag). Send: the flag (stack byte [esp+2]) is 1 if the sender's active modal dialog is MMT_ROUNDTABLE
         * (0x78), else 0. Execute: receivers overwrite both arrays and read the flag into [esp+3]; on the host or a
         * client in MVT_LOBBY_MENU, opens MMT_ROUNDTABLE when no dialog is active and the flag is set, or resets
         * the dialog to MMT_NONE when the flag is 0 and the round table is open. The decompiler's unaff_ECX is an
         * artefact: the prologue 'push ecx' only reserves the 4-byte local.
         */
        void __cdecl HostAnnounceRoundTable();

        /**
         * Lobby command (size 12: slot, AI type, AI variation). Syncs currentAIArray[slot] and
         * aiVariationArray[slot]; on execute sets DAT_PlayerSlotArraySomeValue[slot] = (aiType > 0) and calls
         * PutPlayerIntoRandomSlot(slot).
         */
        void __cdecl AddAIPlayer();

        /**
         * Game command handler (size 18: request kind short + four dwords) for ally messages. On EXECUTE dispatches
         * by kind: 0 ProcessAllyRequestAttackDefense, 1 ProcessAllyRequestingGoods, 2 ProcessAllyGoodsRequest (all
         * with p1-p4), 3 ProcessAllyDeniesRequest, 4 ProcessAllyAcceptsRequest, 5
         * processAllyDeniesAttackOrAidRequest (with p1, p4). The invoking player id is not used.
         */
        void __cdecl SendPlayerToPlayerRequestOrResponse();

        /**
         * Command (size 0x200) sharing the AIV file hash: sender serializes AIVState.aivFileHash; receivers store
         * it into receivedAIVFileHash[invokingPlayer] for players 1-8.
         */
        void __cdecl ShareAIVHash();

        /**
         * Multiplayer command 117 (GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC, size 0x88) that transfers one
         * 64-pixel 16-bit row of a lord face bitmap. Send: serializes Param0 (row index 0..0x41) and Param1 (sender
         * slot) plus that row of the local face (face index localLordIcon-2, 0x80 bytes per row, 0x42 rows per
         * face) split into low/high byte halves (one 0x80-byte serialize covering both adjacent stack arrays).
         * Execute: if the received slot is 1..8, writes the row into face slot+0x13 of bitmapsFaces and sets
         * faceBitmapByteSize[slot+0x13] = 0x2100.
         */
        void __cdecl UpdateSkirmishGameMenuFaceBitmap();

        /**
         * Command handler for activating tactical powers (size 8). Send: serializes Param0 (2 bytes), Param1 (4
         * bytes), Param2 (2 bytes). Execute: deserializes them (sign-extending the two shorts) and calls
         * GameState::handleActivateTacticalPowers(Param2, Param0, Param1).
         */
        void __cdecl ActiveTacticalPowers();

        /**
         * Handler for GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST (no payload). Send just switches the action plan to
         * execute; at execute only the host queues GCT_MULTIPLAYER_ANNOUNCE_HOST.
         */
        void __cdecl InitiateAnnounceHost();

        /**
         * Lobby command (size 4) assigning a slot to a player: first copies DPLAYX_ReceivedPlayerID into
         * DAT_PlayerIDReceiver; send serializes protocolInvokerPlayerID; execute deserializes it into
         * currentPlayerSlotID, stores the DirectPlay player handle in currentPlayerFullIDArray[slot], queues
         * GCT_SHARE_AIV_HASH when lordIconUnk > 1, and copies the local face bitmap (index lordIconUnk-2, 0x2100
         * bytes) into face slot (slot+0x13), setting its size entry to 0x2100.
         */
        void __cdecl AssignPlayerIDToPlayerSlot();

        /**
         * Lobby refresh command (size 8): send serializes Param0 and the sender's isHost flag. Execute (only when
         * the local slot is 1..8) records the sender as host slot if its flag is set, queues
         * GCT_ANNOUNCE_GAME_VERSION and GCT_ANNOUNCE_PLAYER_INFO, and when Param0==1 and lordIconUnk>1 also
         * GCT_SHARE_AIV_HASH.
         */
        void __cdecl TriggerLobbyPlayerInformationRefresh();

        /**
         * Chat/taunt command (size 0x220). Send: serializes DAT_ChatTauntOrMessage (code), the typed text as UTF-16
         * (500 bytes), the 9-int receiver mask and Param0. Execute (sender slot 1..8): if the receiver mask entry
         * for the local slot is set: code 0 = plain chat from the sender; code 10000 = text shown with sender 0 (no
         * player); code > 0 = taunt from the sender, code < 0 = taunt (-1-code) on behalf of slot Param0. For
         * taunts the TEXT_INSULTS string is copied into receivedChatMessage and the matching insultN.wav (table at
         * 0xB38DBC) is played; finally addChatMessageToDisplayList(senderSlot, 0).
         */
        void __cdecl ClickTauntOrChat();

        /**
         * Multiplayer save command (size 0x4b). Send: serializes Param0 (map time ticks), Param1 (units CRC),
         * Param2 (1 byte, save dialog mode) and shortMapName as UTF-16, and marks every empty or own slot as
         * acknowledged, others as pending. Execute: stores the save name (non-host base64-encodes the UTF-16 name
         * into shortMapName, host converts it back to ANSI), records savedMapTimeInTicks/savedUnitsCRC32Hash, shows
         * the save progress dialog, stamps lastSaveTimeMs and sets saveRelated; non-host sets
         * shouldSendAnnouncementUnk (the next sync tick then queues command 0x5D ShareAnnouncementWithHost as
         * acknowledgement), host starts the acknowledgement wait (announcementReceiveTime, announcementReceivedBool
         * = FALSE).
         */
        void __cdecl ExecuteSaveGameCommand();

        /**
         * NAME? Command (size 0x42) that broadcasts shortMapName (map/save name) as UTF-16; on execute the non-host
         * base64-encodes it into shortMapName, the host converts it to ANSI. Then snapshots slots 1..8: player id
         * array and the 8 player names into their second copies, copies the 8 player face bitmaps (faces 20..27 ->
         * 28..35, 0x10800 bytes), sets DAT_SomePlayerID to the local slot, clears chat, calls setSessionDescription
         * and ProgressBarRelated, clears field215_0x106e1c and queues command 0x35. Looks like a game-start lobby
         * snapshot rather than setting a player name.
         */
        void __cdecl SetPlayerNameUnk();

        /**
         * Command (size 0x3f0) announcing the selected map: send converts the loaded map name for index Param0 to
         * UTF-16 and serializes it (2000 bytes), then its checksum and Param0. Execute on non-host: computes the
         * checksum of the local map with that name and, if it differs, queues GCT_ACKNOLEDGE_MAP_EXISTENCE with
         * Param0=0 and Param1=received map index. (Decompiler stack offsets in the send path are shifted by 4
         * because mapNames_getLoadedMapNameForIndex lost its index argument.)
         */
        void __cdecl CommandLoadMapHeader();

        /**
         * Command (size 0x7dc) announcing a saved game (.msv): send serializes the save name (map name list entry
         * DAT_ArrayOfMapIndices[Param0-1]) as UTF-16, Param0, and - after appending .msv and reading that file's
         * header - savedMapTimeInTicks and savedUnitsCRC32Hash. Execute on non-host: base64-encodes the received
         * name into a local file name + .msv; if the file is missing or its header time/CRC differ, queues command
         * 0x33 (shown as GCT_LOAD_MAP_HEADER|GCT_MULTIPLAYER_ANNOUNCE_HOST) with Param0=0 and Param1=received
         * index.
         */
        void __cdecl SubmitMSVMapIndexAndProperties();

        /**
         * Resync command (size 0x494): sender transmits the full 0x490-byte unit record at index Param0 with
         * isSelected temporarily cleared; non-host receivers overwrite their copy via
         * deserializeCommandParamIntoBufferWithMismatchLog, preserving their local isSelected value.
         */
        void __cdecl ResyncChimp();

        /**
         * Resync command (size 0x330): sender transmits building record Param0 (0x32c bytes); non-host receivers
         * overwrite their copy and log mismatches.
         */
        void __cdecl SendResyncBuilding();

        /**
         * Resync command (size 0xa0): sender transmits tree/vegetation record Param0 (0x9c bytes) from
         * LandscapeState.trees; non-host receivers overwrite their copy and log mismatches.
         */
        void __cdecl SendResyncVeg();

        /**
         * Resync command (size 0x338): sender transmits tribe record Param0 (0x334 bytes) with its time field
         * zeroed; non-host receivers overwrite their copy while keeping their local time value.
         */
        void __cdecl SendResyncTribe();

        /**
         * Resync command (size 0x39f8): sender transmits GameState.playerDataArray[Param0] (0x39f4 bytes); non-host
         * receivers overwrite their copy and log mismatches.
         */
        void __cdecl SendResyncPlayerData();

        /**
         * Resync command for global game-state blocks (size 0x38ea): Param0 < 0x12 selects a 0x38e6-byte chunk of
         * GameState starting at mapAndTime+0x194 (0x117C920), 0x12 the 16-byte block right after the 18 chunks
         * (0x11BC94C), 0x13 the AIV mapExtraInfo (0x330 bytes). Non-host receivers overwrite and log mismatches;
         * the 'Glob %d' label (GameState offset of the block) is formatted but never passed on.
         */
        void __cdecl SendResyncGlobals();

        /**
         * Resync command (size 0xec): sender transmits EntityState.entityArray[Param0] (0xe8 bytes); non-host
         * receivers overwrite their copy and log mismatches.
         */
        void __cdecl SendResyncEntity();

        /**
         * Resync command (size 0x9d8): sender transmits Param0 (unused by receiver) and one chunk Param1 of
         * TileMapState.LogicLayer (0x274 dword entries = 0x9d0 bytes); non-host receivers overwrite that chunk and
         * log mismatches with Param1*0x274 as id.
         */
        void __cdecl SendResyncIntLayer();

        /**
         * Command (size 4) removing a player from a running multiplayer game: Param0 = player slot, Param1 = reason
         * text index (both sent as shorts); decrements unknownIncrementBy40_01 by 0x28. For another occupied slot
         * it destroys the DirectPlay player, calls destroyPlayerCompletely, clears the lord unit's
         * lastEncounteredEnemyPlayerID, clears the slot's id/slot/included/group/version entries and name, and
         * posts 'has left the game'. If the target is the local slot it shows reason text Param1 from
         * TEXT_MULTIPLAYER_CONNECTION once (latched by field261_0x109298).
         */
        void __cdecl DestroyPlayer();

        /**
         * Resync command (size 0x644): sender transmits 100 moat entries (16 bytes each, 0x640 bytes) starting at
         * TileMapState.moats[Param0*100]; non-host receivers overwrite them and log mismatches with id Param0*100.
         */
        void __cdecl ResyncMoat();

        /**
         * Resync command (size 0x208): sender transmits PathFindingState.climbData[Param0] (0x204 bytes); non-host
         * receivers overwrite their copy and log mismatches.
         */
        void __cdecl ResyncTeleClimb();

        /**
         * Resync command (size 0x7d4): sender transmits 100 pitch-ditch entries (20 bytes each, 2000 bytes)
         * starting at TileMapState.pitchDitches[Param0*100]; non-host receivers overwrite them and log mismatches.
         */
        void __cdecl ResyncPitch();

        /**
         * Alliance command (size 3): Param0 = target slot (short), Param1 = action (byte). 0 = request: only at the
         * target's machine, if more than 2 teams are in use or playersPerTeam[sender slot] != 1, records the
         * request time for the sender and shows 'wishes to become an ally'. 2 = cancel: the sender moves to the
         * first unused team (1..8) and 'has cancelled the alliance' is shown. 1 = accept (on every machine): if
         * more than 2 teams are used or playersPerTeam[Param0] != 1, and both players are alone in their teams
         * (countPlayersInSameTeam < 2), the target takes the sender's team and 'has joined with' is shown. Likely
         * BUG (original game): playersPerTeam is indexed directly by the slot number instead of by
         * playerTeams[slot] (verified in machine code).
         */
        void __cdecl CommandSwitchTeams();

        /**
         * NAME? Sync-status broadcast command (size 8): send serializes currentPacketTotalSize and field73_0xbdc,
         * sets syncRelatedStatusArray[0..8] to 1 for slots that are empty (currentPlayerFullIDArray == -1) or
         * flagged in another per-slot array (at +0x106240), else 0, starts the announcement timer and marks the
         * local slot done. Execute queues command 0x58 (GCT_BROADCAST_SYNC_RELATED_STATUS_1) and non-host players
         * adopt the two values.
         */
        void __cdecl SyncRelatedSomething();

        /**
         * Command (no payload) asking all players whether to end the game: receivers other than the sender set
         * quitGameVoteRelated=1, store the request time and open the MMT_ONLINE_VOTE_QUIT_GAME dialog; everyone
         * gets 'End this game?' in chat from the sender.
         */
        void __cdecl SendQuitGameQuestion();

        /**
         * Command (size 4) carrying a player's answer to the quit-game vote in Param0 (0 = yes, 1 = no, 2 = close
         * silently). 1/2 reset quitGameVoteRelated and close the vote dialog (1 also prints 'No' for the voter). At
         * the vote initiator (quitGameVoteRelated==2) a yes is recorded in field122_0xc70[voter]; once slots 1..8
         * are all set, Param0 is set to 1 and GCT_KILL_GAME is queued. 'Yes' is printed for the voter whenever
         * Param0 is still 0 (so not for the vote that completes the kill).
         */
        void __cdecl ShareQuitGameVote();

        /**
         * NAME? Plain kick command (size 4): Param0 = slot to remove, Param1 = reason text index. If the local
         * player is the target and field261_0x109298 is 0 it shows the reason from TEXT_MULTIPLAYER_CONNECTION (it
         * writes 0, not 1, to field261, so this guard never latches). If the slot is occupied: destroys the
         * DirectPlay player, calls destroyPlayerCompletely, clears the lord's lastEncounteredEnemyPlayerID, frees
         * the slot id and name, posts 'has left the game' and marks the slot's sync status as done
         * (receivedSyncStatusByPlayerUnk=2, syncRelatedStatusArray=1).
         */
        void __cdecl VoteKick_SEND_L_E_C_A_F_H_ZAP();

        /**
         * Command (size 0x3ec) sharing the selected custom map's name and file hash. Send: serializes the loaded
         * map name for index Param0 (1000 bytes) and the byte-wise hash of maps\<name>.map, and resets
         * mapPossessionStatePerPlayer (2 = empty/local slot, 0 = must answer). Non-host receivers store the name in
         * sharedMapName and hash their local file: on mismatch they set menu action parameter 2000 and open
         * MMT_QUIT_DIALOG; on match they queue GCT_REPORT_MAP_TRANSFER_NEED with Param0=1.
         */
        void __cdecl ShareMapHashForMapName();

        /**
         * Map file transfer command (size 0x405). Sender (Param1 = target slot, Param0 = chunk number, -1 = abort;
         * nothing sent if the slot has no open file) reads up to 1 KB from mapSendingFileHandles[slot] and sends it
         * with its length and an ack-request flag set every 10th chunk or at end of file (where the file is
         * closed); a flagged chunk sets mapPartTransferState[slot] for occupied remote slots. Abort sends an empty
         * chunk with length -1. Receiver appends to FILEPTR_ReceivedMapFile; when complete or length is -1 it
         * closes the file and dialog, reloads map headers and sets reparseMaps; a flagged chunk is answered with
         * command 0x6B (handler 0x00485E80 MapSendingRelated, Param0=0).
         */
        void __cdecl ShareMapPart();

        /**
         * Resync command (size 0x6d9c): sender transmits AIVState.aivs[Param0] (0x6d98 bytes); non-host receivers
         * overwrite their copy and log mismatches.
         */
        void __cdecl ResyncVillage();

        /**
         * Resync command (size 0xf04): sender transmits AIVState.heatMaps[Param0] (0xf00 bytes); non-host receivers
         * overwrite their copy and log mismatches.
         */
        void __cdecl ResyncAIZone();

        /**
         * Lobby join command (size 1, payload = sender's isHost byte). In solitary mode it sets up slot 1 for the
         * local player and copies its face bitmap to face 20. Otherwise a set sender flag sets DAT_TwoIfNotHost=2,
         * and the host adds the sender's DirectPlay id (1 in single-player skirmish) to the player array, puts the
         * returned slot into a random position, then either takes that slot itself and copies its own face (if it
         * had no slot yet) or queues GCT_ASSIGN_PLAYERID_TO_PLAYER_SLOT; finally queues lobby state, info refresh,
         * map selection (unless in crusade intro with negative switch delay) and intensity commands, reorders teams
         * and sets reparseMaps.
         */
        void __cdecl AskForPlayerSlotAssignment();

        /**
         * Host command (size 0xaa) broadcasting the lobby state: player id array (9 ints), two 9-byte per-slot
         * arrays (field300_0x109e80, field48_0x75c), DAT_PlayerSlotArraySomeValue, currentAIArray, aiVariationArray
         * (9 ints each) and playerPositionsArray (8 bytes). On execute everyone deserializes them, calls
         * reorderTeamsAndPositions and sets field215_0x106e1c = 1.
         */
        void __cdecl HostShareLobbyState();

        /**
         * Resync start command (size 8): when scheduled, delays its own execution time by 30 ticks; on execute sets
         * syncStatus=10, calls recomputeHashesAndSendResync(1), stamps field259_0x109290 with timeGetTime, clears
         * currentPacketTotalSize and field267_0x1092b0, shows multiplayer display element 19 and copies the
         * timestamp into field76_0xbe8 and announcementReceiveTime (announcementReceivedBool=FALSE).
         */
        void __cdecl ResyncStartCS_CS_Sub();

        /**
         * Resync finish command (size 0x40): sender transmits the object id counter, RNG state, tile-map counters,
         * wind block, mapTimeInTicks and gameTicksLoadBalancer; on execute (all players) they are applied, derived
         * data rebuilt (climb edges, dust clouds, a 0x27420-byte buffer cleared, wildlife grid, minimap, peasants,
         * wildlife info), max entity/building/tree/unit/moat/ditch counts reset, syncStatus=3, host restarts the
         * announcement timer, timeSkirmishGameStart is restamped, hashes recomputed and DAT_PlayerMatchTimes reset
         * to 0..8.
         */
        void __cdecl ResyncResumeCS();

        /**
         * Host command (size 4) removing an AI player from lobby slot Param0: non-host receivers clear
         * currentAIArray[slot], remove the slot's start position and reorder teams/positions.
         */
        void __cdecl HostRemoveAIPlayerBySlotID();

    } // namespace Commands
} // namespace Synchrony
} // namespace OpenSHC
