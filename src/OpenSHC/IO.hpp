/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO.hpp'
*/

#pragma once

#include "OpenSHC/IO/Base64State.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace IO {

    using OpenSHC::IO::Base64State;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /**
     * Swaps two 32-bit values in place through pointers a and b. Used by BuildingsState::swapOwnersOfCastle.
     */
    void __cdecl SwapInts(undefined4* a, undefined4* b);

    /**
     * Resets a Base64State encoder context: phase 0, no carried bits, line counter 0. Called before Base64Encode by
     * the sync commands that transmit map/save/player-name data.
     */
    void __cdecl Base64EncodeInit(Base64State* state);

    /**
     * Maps a 6-bit value to its Base64 character from the alphabet table DAT_ProtocolDefinedData.base64Alphabet
     * (pointer at 0xB39070); values > 63 return the padding character '='. The comparison is signed (cmp al,0x3f;
     * jle), so negative chars would index before the table, but Base64Encode only passes masked 0..63 values.
     * Clobbers only EAX/ECX (EDX survives, which Base64Encode relies on).
     */
    char __cdecl Base64Encode_CharacterLookup(char sixBitValue);

    /**
     * Resumable Base64 encoder: encodes `length` bytes of `input` into `output` using the 3-byte/4-char state
     * machine in `state` (phase = bytes of the current group already consumed, carryByte = pending bits), so a
     * stream can be encoded over several calls. Emits '\n' after every 0x1C20 (7200) completed 3-byte groups
     * (groupsOnLine counts groups). Returns the number of output characters written. Machine code keeps the output
     * cursor in EDX across Base64Encode_CharacterLookup calls (which clobber only EAX/ECX) and stores the carry
     * byte in the `input` argument slot and the end pointer in the `length` slot.
     */
    int __cdecl Base64Encode(char* input, int length, char* output, Base64State* state);

    /**
     * Checks whether a file can be opened for binary reading (fopen "rb"). Returns TRUE and sets
     * DAT_FileDoesntExist = FALSE if it opens (file is closed immediately), otherwise returns FALSE and sets
     * DAT_FileDoesntExist = TRUE.
     */
    BOOLEnum __cdecl FileExists(char* fileName);

    /**
     * Loads the skirmish leaderboard file <Documents folder>\skmasters2.dat into DAT_SkMasters2DataArray. Sets the
     * version global to 3.0 and count to 0, builds the path (copy of the documents-folder string + append
     * "skmasters2.dat"), and if the file's float version equals 3.0 and its entry count is >= 1, stores the count
     * and reads that many 0xBF0-byte records. The count is only checked for >= 1 (no upper bound against the array
     * size). Missing file or bad version leaves the leaderboard empty.
     */
    void __cdecl ReadSkMasters2();

    /**
     * Saves the skirmish leaderboard: if DAT_SkMasters2Data_Count > 0, builds <Documents folder>\skmasters2.dat and
     * writes version (float), count, then count 0xBF0-byte records from DAT_SkMasters2DataArray ("wb"). Does
     * nothing when the leaderboard is empty.
     */
    void __cdecl WriteSkMasters2();

} // namespace IO
} // namespace OpenSHC
