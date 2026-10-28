/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuTextInputState.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuModalTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00001828
    class MenuTextInputState {
    public:
        // Which file list dialog is active: 1 load game, 2 load/save map, 3 save game (selects which saved
        // scroll/selection/sort triple to use). Constructor default 3.
        undefined4 fileListMode; // 0x00000000 length: 4
        // Remembered list scroll offset for mode 1
        undefined4 loadGameSavedScrollOffset; // 0x00000004 length: 4
        // Remembered relative selection index for mode 1
        undefined4 loadGameSavedSelection; // 0x00000008 length: 4
        // Remembered sort mode for mode 1 (default 2)
        undefined4 loadGameSavedSortMode; // 0x0000000C length: 4
        // Remembered list scroll offset for mode 3
        undefined4 saveGameSavedScrollOffset; // 0x00000010 length: 4
        // Remembered relative selection index for mode 3
        undefined4 saveGameSavedSelection; // 0x00000014 length: 4
        // Remembered sort mode for mode 3 (default 2)
        undefined4 saveGameSavedSortMode; // 0x00000018 length: 4
        // Remembered list scroll offset for mode 2 (maps)
        undefined4 mapListSavedScrollOffset; // 0x0000001C length: 4
        // Remembered relative selection index for mode 2
        undefined4 mapListSavedSelection; // 0x00000020 length: 4
        // Remembered sort mode for mode 2 (default 2)
        undefined4 mapListSavedSortMode; // 0x00000024 length: 4
        undefined4 menuCurrentlySelectedResolution; // 0x00000028 length: 4
        // [235 0x00493E20] toggled by button 0xc, applied via resetupViewport when it differs from
        // viewportState.isZoomedOut (polarity follows that field)
        // [235 0x00493E20] toggled by button 0xc, applied via resetupViewport when it differs from
        // viewportState.isZoomedOutUnk (polarity follows that field)
        undefined4 menuZoomedOutSetting; // 0x0000002C length: 4
        // Options-dialog working copy of DAT_GameCore.gameSpeedLevel, committed on OK
        undefined4 pendingGameSpeedLevel; // 0x00000030 length: 4
        undefined4 menuScrollSpeedSetting; // 0x00000034 length: 4
        // Options-dialog working copy of DAT_GameCore.settingBubbleHelp
        undefined4 pendingBubbleHelp; // 0x00000038 length: 4
        // Options-dialog working copy of DAT_GameCore.unusedOption1
        undefined1 pendingUnusedOption1; // 0x0000003C length: 1
        undefined1 padding_0x3d[3]; // 0x0000003D length: 3
        undefined4 DAT_SoundActiveMenuVar; // 0x00000040 length: 4
        // Slider 0, copied from streamVolume[0], applied to channel 0, reset to 90 by SMCT_RESET_MUSIC_VOLUME.
        // Sound-options slider 0 value (copied from streamVolume[0] when the dialog opens); on change calls
        // setVolumeUnk(0, v) immediately (likely music)
        undefined4 musicVolume; // 0x00000044 length: 4
        // Slider 1, applied to channels 1,2,-1, reset to 80 by SMCT_RESET_SFX_VOLUME. Sound-options slider 1 value
        // (from streamVolume[1]); on change calls setVolumeUnk for channels 1, 2 and -1 immediately
        undefined4 sfxVolume; // 0x00000048 length: 4
        // Slider 2, applied to channels 3,4, reset to 85 by SMCT_RESET_SPEECH_VOLUME. Sound-options slider 2 value
        // (from streamVolume[3]); on change calls setVolumeUnk for channels 3 and 4 immediately
        undefined4 speechVolume; // 0x0000004C length: 4
        undefined4 menuCursorType; // 0x00000050 length: 4
        undefined4 DAT_GenieVoiceActiveMenuVar; // 0x00000054 length: 4
        undefined4 DAT_MenuOptionsActionParameter; // 0x00000058 length: 4
        MenuModalTypeInt currentModalDialog; // 0x0000005C length: 4
        MenuModalTypeInt modalDialog_2; // 0x00000060 length: 4
        MenuModalTypeInt modalDialog_3; // 0x00000064 length: 4
        MenuModalTypeInt modalDialog_4; // 0x00000068 length: 4
        MenuModalTypeInt modalDialog_5; // 0x0000006C length: 4
        MenuModalTypeInt modalDialog_6; // 0x00000070 length: 4
        // Number of entries in the current save/map file list (= ResourceManager.mapFileCounter)
        undefined4 fileListTotalCount; // 0x00000074 length: 4
        // Current sort mode of the file/map list (0/1 toggled by table header; saved per mode)
        undefined4 fileListSortMode; // 0x00000078 length: 4
        undefined4 DAT_MenuLoadGameRelativeSelectionIndex; // 0x0000007C length: 4
        undefined4 DAT_MenuLoadGameRelativeSelectionOffset; // 0x00000080 length: 4
        // Visible rows in the file list (0x10); scrollbar max = total - visible
        undefined4 fileListVisibleRows; // 0x00000084 length: 4
        undefined4 DAT_SomeTextArrayIndex; // 0x00000088 length: 4
        // Previously clicked mission/map index for double-click detection; reset -1 on list prepare
        undefined4 lastClickedListIndex; // 0x0000008C length: 4
        // timeGetTime of previous click on a mission/map/file list entry; a second click on the same entry within
        // 500 ms counts as double-click (pairs with lastClickedListIndex)
        undefined4 lastListClickTime; // 0x00000090 length: 4
        // Screen x of the load/save progress bar (set by ProgressBarBox modal, used by RenderLoadAndSaveBar; bar is
        // 300 px wide)
        undefined4 progressBarX; // 0x00000094 length: 4
        // Screen y of the load/save progress bar (box y + 0x41, 15 px high)
        undefined4 progressBarY; // 0x00000098 length: 4
        // Set before opening a load/save dialog from a menu view; when the dialog closes, MenuView_TriggerInitial
        // and viewport reset are requested, then cleared
        undefined4 reinitMenuViewOnDialogClose; // 0x0000009C length: 4
        // List index whose minimap preview is currently built (SetupPreviewMinimapDataUnk skips rebuild if equal);
        // -1 forces rebuild
        undefined4 previewMinimapListIndex; // 0x000000A0 length: 4
        // Set 1 after a map/save file was written (LoadAndSaveGameButtonLogic); map editor/siege views reset
        // DAT_EditorUnsavedChanges and clear it next frame
        // Set 1 after a map/save file was written (LoadAndSaveGameButtonLogic); map editor/siege views reset
        // INT_00b95f68 and clear it next frame
        int saveJustCompleted; // 0x000000A4 length: 4
        // accessed by 0x425f11, 0x426037, 0x42604f, 0x44078e
        int field_0xa8; // 0x000000A8 length: 4
        // Checked: set 1 only in loadOrSaveMap which lists maps\*.tmp; 0 in .map and save-game openers; gates save
        // path logic. 1 when the file dialog was opened through loadOrSaveMap, 0 via
        // activateLoadOrSaveMapUI/loadOrSaveGame; changes how the save button stores the typed name
        undefined4 isTmpMapFileList; // 0x000000AC length: 4
        undefined4 DAT_ArrayOfMapU3EndInt2[500]; // 0x000000B0 length: 2000
        // Re-base: the sorted map index list starts at +0x880 (0x1126E28): bubble sorts read
        // [i*4+0x1126E28]/[i*4+0x1126E2C], direct read of 0x1126E28; Ghidra shows every access as
        // DAT_ArrayOfMapIndices[i-1] because the field starts 4 bytes late.
        int mapIndexList[500]; // 0x00000880 length: 2000
        // stores map ids (0x449068) copied back to undo sorting, and used as 0/non-0 flags in SaveLoadMap: shared
        // buffer Re-base: per-entry loadable flags start at +0x1050 (0x11275F8), indexed by list position; old
        // field started at +0x1054.
        int unsortedMapIdsOrLoadableFlags[500]; // 0x00001050 length: 2000
        undefined1 padding_0x1820[8]; // 0x00001820 length: 8

    private:
        MenuTextInputState(MenuTextInputState const&);
        void operator=(MenuTextInputState const&);

    public:
        MenuTextInputState() {};
        ~MenuTextInputState() {};

        // Constructor
        /**
         * Constructor of the global MenuTextInputState: sets the current and stacked modal dialogs (2..6) to
         * MMT_NO_MENU, the file-list kind field0 to 3, and the three saved (offset, selection, sort mode) triples
         * for the load-game (field1..3), save-game (field4..6) and map (field7..9) lists to (0, 0, 2).
         */
        MenuTextInputState* Constructor_MenuTextInputState();

        /**
         * Opens a modal dialog. If no modal was open, remembers the active user-text index, enables text input and
         * clears the text buffer (when the index is non-zero). If the requested dialog differs from the current
         * one, pushes the current dialog onto the 5-deep history (modalDialog_2..6, oldest dropped) and activates
         * the new one in MenuModalComposition1.
         */
        void activateModalDialogAndClearText(MenuModalType dialogID);

        /**
         * Clears the stacked modal dialog history (modalDialog_2..6 = MMT_NO_MENU).
         */
        void clearModalDialog2to6();

        /**
         * Closes all modal dialogs: disables text input, restores the user-text index saved when the first modal
         * opened (clearing the text if that index is non-zero), sets currentModalDialog to MMT_NO_MENU, deactivates
         * the modal composition, clears the history, and if field42_0x9c was set requests a menu-view re-init and
         * viewport reset; clears field42_0x9c.
         */
        void clearAnyOtherModalDialogs();

        /**
         * Closes all modal dialogs like clearAnyOtherModalDialogs but leaves the user-text input state untouched.
         * NAME? e.g. closeAllModalDialogsKeepTextInput.
         */
        void meth_0x4917c0();

        /**
         * Pops the modal dialog history: makes modalDialog_2 current and shifts the rest up. Re-activates that
         * dialog (for MMT_SAVE_MAP also re-arms the filename text input at index 2 with the cursor at the end), or
         * closes everything via clearAnyOtherModalDialogs if the history was empty.
         */
        void popModalDialog();

        /**
         * Opens the load/save map dialog (loadOrSaveMap 9 = load, else save): shows the wait cursor, clears the
         * minimap preview, enumerates maps\*.map (with map-lock filter), fills the identity index mapping, resets
         * list state, opens MMT_LOAD_MAP or MMT_SAVE_MAP (with filename input at text index 2), sets fileListKind
         * (field0) to 2, and if the list is non-empty restores the saved map-list offset/selection/sort triple
         * (field7..9, reset to 0 if out of range) and re-applies the sort via the table-header handler.
         */
        void activateLoadOrSaveMapUI(int loadOrSaveMap);

        /**
         * Variant of activateLoadOrSaveMapUI that enumerates maps\*.tmp instead of *.map: same wait cursor/minimap
         * reset/index mapping, sets field49_0xac = 1 (0 in the other list openers), opens MMT_LOAD_MAP (param 9) or
         * MMT_SAVE_MAP with filename input, does not restore a saved list position and always calls the table-
         * header handler with 1. NAME? only caller is the unused CreateSiege menu (0x4437E0, passes 9 or 10), so
         * this is the load/save dialog for .tmp (siege template) files, e.g. activateLoadOrSaveSiegeTemplateUI.
         */
        void loadOrSaveMap(MenuModalType loadOrSaveAction);

        /**
         * Opens the load (action 9) or save (action 10) game dialog. Saving in multiplayer while saveRelated == 1
         * only closes all modal dialogs. Otherwise: wait cursor, minimap preview cleared; single-player enumerates
         * <saves>\*.sav and fills the identity index mapping; multiplayer enumerates <saves>\*.msv, fills the
         * mapping, sets a per-file flag (MenuTextInputState+0x1050, a 500-int array after the 500-int mapping at
         * +0x880) to 1 and, for loads, queues game command 50 (SubmitMSVMapIndexAndProperties) with the file index.
         * Then opens MMT_LOAD_MAP (fileListKind 1) or MMT_SAVE_MAP with filename input (fileListKind 3), restores
         * that dialog's saved offset/selection/sort triple if the list is non-empty, and re-applies the sort.
         */
        void loadOrSaveGame(int action);
    };

    static_assert_cpp98_obj(sizeof(MenuTextInputState) == 6184, MenuTextInputState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
