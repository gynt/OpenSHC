/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/ResourceManager.hpp'
*/

#pragma once

#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/IO/FileResourceTypeInt.hpp"
#include "OpenSHC/IO/Helpers/OPENFILENAMEA_Truncated.hpp"
#include "OpenSHC/Map/MapMetaInfo.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "crtdefs.h"
#include "winnt.h"

namespace OpenSHC {
namespace IO {

    using OpenSHC::IO::FileResourceType;
    using OpenSHC::IO::FileResourceTypeInt;
    using OpenSHC::IO::Helpers::OPENFILENAMEA_Truncated;
    using OpenSHC::Map::MapMetaInfo;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000FC794
    class ResourceManager {
    public:
        // Unsigned Double-Word (ddw, 4-bytes)
        int mapFileCounter; // 0x00000000 length: 4
        int loadPositionInCurrentResource; // 0x00000004 length: 4
        char strFile[4]; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword currentSectionIndex; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mbr_0x10; // 0x00000010 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int mapHeaderMagicByte; // 0x00000014 length: 4
        byte unused_0x18[985]; // 0x00000018 length: 985
        char strFileTitle[1001]; // 0x000003F1 length: 1001
        // set exactly when a valid configpath.txt path is stored; then that path replaces the Documents base folder
        // Unsigned Byte (db)
        bool hasConfigPath; // 0x000007DA length: 1
        // [021 0x00477710] C string copied as the base user path instead of the shell folder Unsigned Double-Word
        // (ddw, 4-bytes)
        char userPathOverride[1001]; // 0x000007DB length: 1001
        // Unsigned Double-Word (ddw, 4-bytes)
        FileResourceTypeInt currentActiveResourceType; // 0x00000BC4 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        char loadedMapNames[500][1001]; // 0x00000BC8 length: 500500
        undefined1 padding_0x7aedc[4]; // 0x0007AEDC length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        char resourceFileNameArray[20][1001]; // 0x0007AEE0 length: 20020
        dword mapFileTimes[500]; // 0x0007FD14 length: 2000
        byte unused_0x804e4[2006]; // 0x000804E4 length: 2006
        OPENFILENAMEA_Truncated openFileNameA; // 0x00080CBA length: 76
        undefined1 padding_0x80d06[2]; // 0x00080D06 length: 2
        int fileHandle; // 0x00080D08 length: 4
        MapMetaInfo mapMetaInfoArray[500]; // 0x00080D0C length: 6000
        char mapNames[500][1001]; // 0x0008247C length: 500500
        // Unsigned Double-Word (ddw, 4-bytes)
        int loadedMapsCount; // 0x000FC790 length: 4

    private:
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);

    public:
        ResourceManager() {};
        ~ResourceManager() {};

        // Constructor
        /**
         * ResourceManager constructor: resets mapFileCounter and zeroes 500000 bytes of the loaded-map-name table
         * (0x11BFCF8); returns the global DAT_ResourceManager.
         */
        ResourceManager* Constructor_ResourceManager();

        /**
         * Copies the cached header meta of map entry id (mapMetaInfoArray[id]: type, lock state, balance, end int,
         * player count, mission type, siege/invasion type) into DAT_GameCore/DAT_MapPropertiesState and clears
         * mapU4Int0_2; used by map-choice/lobby screens instead of re-reading the file.
         */
        void loadMapMetaByID(dword id);

        /**
         * Searches DAT_ResourceManager.mapNames (case-insensitive) for mapNameAddress among the first
         * loadedMapsCount entries and returns that map's cached checksum from mapMetaInfoArray, or 0 if not found.
         */
        dword getChecksumOfMapByName(char* mapNameAddress);

        /**
         * Returns the address of the 1001-byte loaded-map-name slot for mapIndex (this->loadedMapNames, 0x11BFCF8),
         * or 0 if the index is >= 500. Really __thiscall: the base is computed from ECX.
         */
        char* mapNames_getLoadedMapNameForIndex(int mapIndex);

        /**
         * Returns resourceFileNameArray[currentActiveResourceType], the full file name of the currently selected
         * resource.
         */
        char* getFileNameOfCurrentActiveResource();

        /**
         * Reads up to 500 bytes of configpath.txt, cuts at the first CR/LF, and if that line is longer than 2 chars
         * strips one trailing backslash, copies it into the ResourceManager config-path string (0x11BF90B) and sets
         * configPathLoadedUnk_0x7da.
         */
        void loadConfigPathTxt();

        /**
         * Returns TRUE if filename can be opened for reading (binary), closing it again; FALSE otherwise.
         */
        BOOLEnum doesFileExist(char* filename);

        /**
         * Configures the shared OPENFILENAMEA for TGX/gfx import: filter and default-extension string from
         * DAT_TextInputDefinedData (+0x710), filter index 1, initial dir "gfx\".
         */
        void setGfxFileFilter();

        /**
         * Configures the shared OPENFILENAMEA for help files: filter/default-extension string from
         * DAT_TextInputDefinedData (+0x71C), filter index 1, initial dir "help\".
         */
        void setHelpFileFilter();

        /**
         * Configures the shared OPENFILENAMEA for sound import: filter/default-extension string from
         * DAT_TextInputDefinedData (+0x728), filter index 1, initial dir "fx\".
         */
        void setSoundFileFilter();

        /**
         * Sums ALL bytes of the file `filename` (read in 1024-byte chunks, each byte sign-extended via movsx) and
         * returns that sum; returns -1 if the file cannot be opened. The loop only ends when _read returns 0, so a
         * read error (-1) would retry forever. Used by setAvailableAIV as a simple AIV checksum.
         */
        int getSignedByteSumOfFile(char* filename);

        /**
         * Restores the loaded map list from the snapshot taken by loadMapHeaders (undoing e.g.
         * mapNames_filterMapsIfMapLock): sets mapFileCounter = loadedMapsCount and copies each saved name
         * mapNames[i] (base 0x12415AC) back into loadedMapNames[i] (address from mapNames_getLoadedMapNameForIndex)
         * via an inlined strcpy. The copy direction is mapNames -> loadedMapNames, opposite to the plate comment.
         * NAME? mapNames_restoreLoadedMapNames.
         */
        void mapNames_syncLoadedMapNames();

        /**
         * Swaps loaded-map entry _mapFileIndex with the next one: exchanges the two 1000-byte names through the
         * temp buffer at 0x123A010 and swaps their mapFileTimes. Used by the bubble sort in discoverMapFiles.
         * unaff_EBP is the address of name[_mapFileIndex], which the compiler stashed in the argument slot.
         */
        void swapMapDataWithNextMap(int _mapFileIndex);

        /**
         * If id1 != id2, copies loaded-map entry id1 (1000-byte name and file time) over entry id2; used to compact
         * the list when filtering locked maps.
         */
        void replaceMapNameWith(dword id1, dword id2);

        /**
         * Extracts the base name of the active resource file (text between the last '\' and the first '.' after it)
         * into DAT_CurrentResourceCoreName and returns it; returns an empty string if the path contains no
         * backslash.
         */
        char* getCurrentResourceBaseName();

        /**
         * Returns TRUE if the active resource's file can be opened (binary), FALSE otherwise.
         */
        BOOLEnum doesFileOfActiveResourceExist();

        /**
         * Zeroes the shared OPENFILENAMEA (0x4C bytes) and fills size, owner window, file/file-title buffers (1000
         * chars each) and Flags=8 (OFN_NOCHANGEDIR).
         */
        void resetOpenFileNameStruct();

        /**
         * Opens the active resource file and reads up to size bytes into destination; stores the byte count in
         * loadPositionInCurrentResource. Returns FALSE if the file cannot be opened.
         */
        BOOLEnum readCurrentResourceIntoDestination(void* destination, size_t size);

        /**
         * Returns the size in bytes of the active resource file (seek to end + tell), or 0 if it cannot be opened.
         */
        int getCurrentResourceSize();

        /**
         * Builds '<active resource name>.<fileExtension>' into resourceFileNameArray[0], opens it (temporarily
         * switching the active type to 0), reads partSize bytes into destination and stores the count in
         * loadPositionInCurrentResource for subsequent readNextPart calls. Returns FALSE if the file is missing.
         * unaff_EDI/unaff_ESI/unaff_retaddr are really destination/partSize/fileExtension (stack mis-tracked after
         * fillMemory_ByteValue).
         */
        BOOLEnum readFirstPartOfCurrentResourceIntoMemory(void* destination, int partSize, char* fileExtension);

        /**
         * Like readFirstPartOfCurrentResourceIntoMemory, but seeks to loadPositionInCurrentResource first and
         * advances it by the number of bytes read (chunked loading of .gm files). unaff_EDI/unaff_ESI/unaff_retaddr
         * are really destination/partSize/fileExtension.
         */
        BOOLEnum readNextPartOfCurrentResourceIntoMemory(void* destination, int partSize, char* fileExtension);

        /**
         * Shows the 'Select TGX file to import' open dialog (gfx\ filter) after resetting mouse state; returns TRUE
         * if the user picked a file.
         */
        BOOLEnum showOpenGfxFileDialog();

        /**
         * Shows an open-file dialog for help files with the given title; returns TRUE if the user picked a file.
         */
        BOOLEnum showOpenHelpFileDialog(LPCSTR dialogTitle);

        /**
         * Shows the 'Select help file to save' save-file dialog; returns TRUE if the user confirmed a file name.
         */
        BOOLEnum showSaveHelpFileDialog();

        /**
         * Shows the 'Select sound file to import' open dialog (fx\ filter); returns TRUE if the user picked a file.
         */
        BOOLEnum showOpenSoundFileDialog();

        /**
         * Sums all bytes of the active resource file (1024-byte chunks, each byte sign-extended) and returns the
         * sum as the map's checksum; returns -1 if the file cannot be opened. A read error (_read returning -1)
         * would loop forever. Used by loadMapHeaders (cached in mapMetaInfoArray) and for multiplayer map-hash
         * sharing.
         */
        int fileHashFunctionByteByByte();

        /**
         * Builds the relative path "\Stronghold Crusader\" and, via string_prependUserPathToString (CSIDL 5 = My
         * Documents), the same path under the user's Documents folder; assigns the full path to the output string
         * if prependUserPath is true, else the relative one. Returns the output string. local_18/local_14 are the
         * length/capacity fields of the relativePath std::string.
         */
        std::string paths_getDocumentsFolderString(bool param_2);

        /**
         * Returns the saves folder path in the output string: relative Documents path + "Saves\" (prependUserPath
         * false) or the same with the user's Documents folder prepended (true). Returns the output string.
         */
        std::string paths_getSavesPath(bool param_2);

        /**
         * Returns the user maps folder path in the output string: relative Documents path + "Maps\" or, if
         * prependUserPath, with the user's Documents folder prepended. Returns the output string.
         */
        std::string paths_getDocumentsMapsFolderString(bool prependUserPath);

        /**
         * Enumerates files matching searchPattern (FindFirst/NextFileA, max 500) into loadedMapNames (name up to
         * the first '.') and mapFileTimes ((FAT date << 16) | FAT time of the last-write time). The time-zone
         * adjustment uses only StandardBias/DaylightBias (base Bias ignored), so times are UTC shifted by the DST
         * delta, not local time. For the built-in patterns "maps\*.map"/"mapsExtreme\*.map" it DISCARDS campaign
         * files mission0-21 and mission33-37, continues with <Documents>\Stronghold Crusader\Maps\*.map
         * (overwriting the first search handle without closing it), and bubble-sorts by the display name from
         * GetStringBasedOnHardcodedMaps; other patterns are sorted with stricmp. BUG (original game, harmless): if
         * the Documents FindFirstFileA fails, INVALID_HANDLE_VALUE is stored over the handle and passed to
         * FindClose, so the first handle always leaks in the built-in-maps case.
         */
        void discoverMapFiles(char const* searchPattern);

        /**
         * Sets currentActiveResourceType and builds the full path for shortFileName into
         * resourceFileNameArray[resourceType]: type-specific folder prefix (castles\, scenarios\, gm\, gfx\, help\,
         * binks\, fx\, scores\, gfx8\, fx\speech\; none for BMP) + name. FRT_SAVES uses the full Documents Saves
         * folder; FRT_MAPS uses maps\<name> and falls back to <Documents>\Stronghold Crusader\Maps\<name> if that
         * file does not exist; other types copy the name unchanged (byte copy using a fixed dst-src offset).
         */
        void resolveResourceFileName(FileResourceType resourceType, char const* shortFileName);

        /**
         * Scans maps\*.map (plus Documents maps), sets loadedMapsCount, and for every map copies its name into
         * mapNames[i], resolves '<name>.map', reads its header (no preview) and caches checksum
         * (fileHashFunctionByteByByte), map type, lock state, balance, end int, player count, mission type and
         * siege/invasion type (truncated to bytes) in mapMetaInfoArray[i]. Optionally advances the loading bar
         * (from base+80 towards base+180).
         */
        void loadMapHeaders(BOOLEnum drawLoadingBar);

        /**
         * Filters the loaded map list to editable maps: reads each map's header and keeps it (compacting via
         * replaceMapNameWith) only if savedMapLocked == MLS_EDITABLE, otherwise decrements mapFileCounter.
         * mapMetaInfoArray is not compacted along with the names; mapNames_syncLoadedMapNames restores the full
         * list.
         */
        void mapNames_filterMapsIfMapLock();
    };

    static_assert_cpp98_obj(sizeof(ResourceManager) == 1034132, ResourceManager);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
