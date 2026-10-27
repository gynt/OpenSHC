/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/FilePackager.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVSectionAddress.hpp"
#include "OpenSHC/IO/DirectoryStructNew.hpp"
#include "OpenSHC/IO/DirectoryStructOld.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/MapSectionAddress.hpp"
#include "OpenSHC/UI/RenderLoadAndSaveBar.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::AI::AIV::AIVSectionAddress;
    using OpenSHC::IO::DirectoryStructNew;
    using OpenSHC::IO::DirectoryStructOld;
    using OpenSHC::IO::PackagedFileMagicNumInt;
    using OpenSHC::Map::MapSectionAddress;
    using OpenSHC::UI::RenderLoadAndSaveBar;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000013EC
    class FilePackager {
    public:
        // [052 0x0046D070] initialised to 0xAC, the same value writeMapOrSaveFile stores as
        // directory.fileFormatVersion [RUNTIME] Format version written to new files (0xAC)
        // [052 0x0046D070] initialised to 0xAC, the same value writeMapOrSaveFile stores as
        // directory.magicNumOfFileType [RUNTIME] Format version written to new files (0xAC)
        int mapFormatVersion; // 0x00000000 length: 4
        // [053 0x00474A20] simply copied from directory.fileFormatVersion after reading the directory [RUNTIME]
        // Format version of the loaded map/sav (0xAC = 172 current, 170 older; code tests < 0x9A), not a file magic
        // [053 0x00474A20] simply copied from directory.magicNumOfFileType after reading the directory [RUNTIME]
        // Format version of the loaded map/sav (0xAC = 172 current, 170 older; code tests < 0x9A), not a file magic
        int currentFileFormatVersion; // 0x00000004 length: 4
        // when set, sections are copied raw on both save (no encode) and load (no decode) May have been used to
        // save all sections uncompressed, but crashes the game if set.
        BOOLEnum bypassCompression; // 0x00000008 length: 4
        // [052 0x00474480] also used as the section index while writing, not only reading
        int currentSectionIndex; // 0x0000000C length: 4
        void* tempMem; // 0x00000010 length: 4
        int directorySize; // 0x00000014 length: 4
        void* currentlyReadFileSectionMemory; // 0x00000018 length: 4
        int currentlyReadFileSectionSize; // 0x0000001C length: 4
        RenderLoadAndSaveBar* loadAndSaveBarFunc; // 0x00000020 length: 4
        DirectoryStructNew directory; // 0x00000024 length: 3032
        DirectoryStructOld oldDirectory; // 0x00000BFC length: 2032

    private:
        FilePackager(FilePackager const&);
        void operator=(FilePackager const&);

    public:
        FilePackager() {};
        ~FilePackager() {};

        // Constructor
        /**
         * Constructor of the global FilePackagerObj: sets packagerMapVersionNumUnk = 0xAC, clears tempMem, the
         * save-uncompressed flag and the load/save progress-bar callback; returns &FilePackagerObj.
         */
        FilePackager* Constructor_FilePackager();

        /**
         * Converts a map/save directory read in the old format (100 sections) to the current one (150 sections):
         * copies payload size, magic, section count and constant fields, then the first 100 entries of the
         * uncompressedSize, compressedSize, id, isCompressed and offset arrays.
         */
        void copyFromOldToNewMapDirectory();

        /**
         * Writes the current map/savegame to the active resource file. Mallocs a 6,000,000-byte section buffer
         * (tempMem) and a 100,000-byte scratch buffer, then packs up to 150 entries of mapSectionAddressArray
         * (16-byte entries; stops at address 0, skips entries whose +4 field is non-zero) into tempMem - raw, or
         * via encodeData when isCompressed and FilePackagerObj.bypassCompression is FALSE - filling the directory,
         * reporting per-mille progress through the load/save-bar callback (taken from loadAndSaveBarFunc, which is
         * cleared) and calling sendPeriodicSyncMessages every 10 sections outside single-player modes. Then writes
         * a -1 marker, the size-prefixed imploded minimap preview (renderMiniMapForSaving parameters chosen by map
         * size), a block with the imploded DAT_GameCore.temporaryTextBufferOfSize1000 plus two dwords, fixed blocks
         * of 8, 0x1C, 0x3F9 and 0x50 bytes from globals, a 0 terminator, directorySize 0xBDC + the 0xBD8-byte
         * directory (magic 0xAC) and the payload. BUG: returns without freeing tempMem if the second malloc fails,
         * and without freeing either buffer if _open fails; the next malloc overwrites tempMem, so the memory
         * leaks.
         */
        void writeMapOrSaveFile(MapSectionAddress* mapSectionAddressArray);

        /**
         * Loads a complete .map/.sav file of the current resource. Saves and clears
         * FilePackagerObj.loadAndSaveBarFunc, allocates a 6 MB section buffer and a 100 KB header buffer, resets
         * game state (zeroes mapAndTime, GameState fill 0xFF, default player colours, keep positions, player
         * groups, tribe arrays), reads the optional header blocks when directorySize < 0 (preview, description
         * decoded into temporaryTextBufferOfSize1000, Map.u1-u4 meta: saved tick/CRC, map type, players, mission
         * type, lock state, filename, autosave, balance, keeps), then the section directory (old 0x7F4-byte layout
         * converted) and payload. Every section except id 0x447 with size >= 5 is copied raw or decoded into its
         * mapSectionAddrArray destination (a raw 0x4A0-byte section 1124 is upgraded via UpgradeOldSection1124),
         * advancing the progress bar 50..1000; finally frees the buffers, applies the hard-coded string-table
         * description, derives historicCampaignNumber (1-4) from missionNumber1to20 for campaign missions and
         * resets timeSum_2. iVar4 is reused for timeGetTime().
         */
        void readMapOrSavFile(MapSectionAddress* mapSectionAddrArray);

        /**
         * Reads the current resource's map file, skipping every size-prefixed header block via lseek until a zero
         * size, then the section directory (old 0x7F4 layout converted) and payload into a 6 MB temp buffer, and
         * copies or decodes only the section whose id equals sectionID into its mapSectionAddrArray destination.
         * FilePackagerObj.loadAndSaveBarFunc is cleared on entry and the saved callback is called once with 50; the
         * temp buffer is freed afterwards.
         */
        void readMapHeaderSectionByID(MapSectionAddress* mapSectionAddrArray, int sectionID);

        /**
         * Reads only the header blocks of the current resource's map file. Resets the DAT_GameCore header fields
         * and keep positions, then (if directorySize < 0) loads or skips the minimap preview (decoded into
         * MinimapViewState.loadedMiniMap and colour-converted only when loadPreviewUnk), reads the description
         * block (decoded into mapDescription only when loadPreviewUnk) and the Map.u1-u4 meta (saved tick/CRC, map
         * type, keeps, player count, mission type, siege/invasion, lock state, standalone filename, end int,
         * balance, keep positions). Finally clears mapDescUseStringTable and calls GetStringBasedOnHardcodedMaps on
         * the base name, which sets it back to 1 for built-in maps; the returned name and description group number
         * are discarded.
         */
        void readMapHeader(BOOLEnum loadPreviewUnk);

        /**
         * Opens the .aiv file fileName, reads its section directory (old 0x7F4 layout converted) and payload into a
         * 6 MB temp buffer and copies or decodes every section into the matching entry of the AIVSectionAddress
         * array (entries with unknown != 0 are skipped). Returns 1 if all sections were placed; 0 if the file
         * cannot be opened, the buffer cannot be allocated (the file is then left open), a section has no matching
         * array entry, or a section's uncompressed size exceeds the destination size - that check happens after the
         * copy, and the 'Err:raw/cmp %d' text is only formatted into a local buffer. The decompiler shows the
         * cookie-check call as return value; the real EAX is allSectionsOk.
         */
        int unpackAIVFile(AIVSectionAddress* array, char* fileName);
    };

    static_assert_cpp98_obj(sizeof(FilePackager) == 5100, FilePackager);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
