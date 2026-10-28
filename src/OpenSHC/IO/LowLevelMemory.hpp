/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/LowLevelMemory.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "crtdefs.h"

namespace OpenSHC {
namespace IO {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000014
    class LowLevelMemory {
    public:
        void* src; // 0x00000000 length: 4
        void* destination; // 0x00000004 length: 4
        int size; // 0x00000008 length: 4
        int value; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4

    private:
        LowLevelMemory(LowLevelMemory const&);
        void operator=(LowLevelMemory const&);

    public:
        LowLevelMemory() {};
        ~LowLevelMemory() {};

        /**
         * Copies 3 bytes from src to dst (a 16-bit word plus the third byte); used to pack/unpack 24-bit values in
         * multiplayer sync messages.
         */
        void moveLowerThreeBytesIntoParam2(void* src, void* dst);

        /**
         * Tail of the byte fill: writes DAT_LowLevelMemory.value as single bytes to the remaining
         * DAT_LowLevelMemory.size bytes at destination (fields read through ECX = this; globals are not updated).
         */
        void fillMemory_setMemoryToValue_0x001();

        /**
         * Tail of the short fill: writes DAT_LowLevelMemory.value as 16-bit words over the remaining
         * DAT_LowLevelMemory.size bytes at destination (an odd size overruns by one byte).
         */
        void fillMemory_setMemoryToValue_0x002();

        /**
         * Tail of the int fill: writes DAT_LowLevelMemory.value as 32-bit ints over the remaining
         * DAT_LowLevelMemory.size bytes at destination (sizes not a multiple of 4 overrun the end).
         */
        void fillMemory_setMemoryToValue_0x004();

        /**
         * Fill stage: while DAT_LowLevelMemory.size >= 16, writes four copies of the 32-bit value and advances
         * destination by 16 / decrements size.
         */
        void fillMemory_setMemoryToValue_0x010();

        /**
         * Fill stage: while DAT_LowLevelMemory.size >= 256, writes 64 copies of the 32-bit value (unrolled) and
         * advances destination by 256 / decrements size.
         */
        void fillMemory_setMemoryToValue_0x100();

        /**
         * Tail of copyData: copies the remaining DAT_LowLevelMemory.size bytes byte-by-byte from src to
         * destination. Returns EAX = size, with the low byte replaced by the last copied byte if any.
         */
        void copyData_0x001();

        /**
         * copyData stage: while DAT_LowLevelMemory.size >= 16, copies 16 bytes (4 dwords) from src to destination
         * and advances both pointers.
         */
        void copyData_0x010();

        /**
         * copyData stage: while DAT_LowLevelMemory.size >= 256, copies 256 bytes (64 unrolled dwords) from src to
         * destination and advances both pointers.
         */
        void copyData_0x100();

        /**
         * Copies characters of a filename into dest until the first '.' or end of string (strips the extension).
         * Does not write a terminating NUL (discoverMapFiles zeroes the slots beforehand).
         */
        void copyStringUntilFirstDot(char* source, char* dest);

        /**
         * Copies sourceName up to its first '.' into dest, then appends '.' and the given extension (NUL-
         * terminated).
         */
        void putFileNameAndAppendFileExtension(char* sourceName, char* dest, char* extension);

        /**
         * Checks whether the known (voiced) lord name callableLordName occurs as a whole word in the player's
         * entered name, case-insensitively (both strings are lowercased in place). If the lengths differ by <2 the
         * player name only has to start with it; otherwise it must start at position 0 or after a space and be
         * followed by space, '.', digit 1-9 or end of string. Returns TRUE on match.
         */
        BOOLEnum isLordNameCallable(char* playerLordNameUnk, char* callableLordName);

        /**
         * Generic memcpy: stores size/src/destination in DAT_LowLevelMemory (ECX = this), then copies in 256-byte,
         * 16-byte and 1-byte stages; returns whatever copyData_0x001 leaves in EAX (not meaningful to callers).
         */
        void copyData(size_t size, void* src, void* dst);

        /**
         * Fills size bytes at destination with the 32-bit value via the 256-, 16- and 4-byte fill stages of
         * DAT_LowLevelMemory (this_00 is just ECX = this passed through).
         */
        void fillMemory_IntegerValue(size_t size, int value, void* destination);

        /**
         * Fills size bytes at dst with a 16-bit value: replicates it into both halves of a dword (value*0x10001)
         * and runs the 256-, 16- and 2-byte fill stages.
         */
        void fillMemory_ShortValue(size_t size, ushort shortValue, void* dst);

        /**
         * Fills size bytes at dst with a byte value: replicates it into all four bytes of a dword
         * (value*0x01010101) and runs the 256-, 16- and 1-byte fill stages of DAT_LowLevelMemory (memset). Really
         * __thiscall with ECX = &DAT_LowLevelMemory and callee cleanup (ret 0xC).
         */
        void fillMemory_ByteValue(size_t size, uchar byteValue, void* dst);
    };

    static_assert_cpp98_obj(sizeof(LowLevelMemory) == 20, LowLevelMemory);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
