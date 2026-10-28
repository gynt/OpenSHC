/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/DecoderState.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000014
    class DecoderState {
    public:
        // [052 0x0046D140] 0 (CMP_BINARY) passed as the type argument of pkware_implode
        uint implodeCompressionType; // 0x00000000 length: 4
        // [052 0x0046D140] 0x1000 passed as the dsize argument of pkware_implode
        uint implodeDictionarySize; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword crc32; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword sizeUncompressed; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int sizeCompressed; // 0x00000010 length: 4

    private:
        DecoderState(DecoderState const&);
        void operator=(DecoderState const&);

    public:
        DecoderState() {};
        ~DecoderState() {};

        // Constructor
        /**
         * Constructor of the global DAT_DecoderState: sets PKWARE implode compression type 0 (binary) and
         * dictionary size 0x1000 (4 KB); returns &DAT_DecoderState.
         */
        DecoderState* Constructor_DecoderState();

        /**
         * Simple RLE compressor for network packets. Output: int totalSize (incl. 8-byte header), int
         * uncompressedSize, then records: a run of >=3 equal bytes -> ushort (len-1) + 1 value byte; otherwise a
         * literal block -> ushort ((len-1)|0x8000) + len raw bytes. Runs/blocks are capped at 0x7FFF bytes. Returns
         * totalSize. Peeks up to 2 bytes beyond src end.
         */
        int compressRLE(char* src, void* dst, int size);

        /**
         * Decompresses the compressRLE format: reads the uncompressed size at src+4, then processes records from
         * src+8 (bit 15 clear: run of (n&0x7FFF)+1 copies of one byte; set: literal block of that many bytes) into
         * dst. Returns the number of bytes written.
         */
        int decompressRLE(char* src, char* dst);

        /**
         * Compresses sizeUncompressed bytes from src into dst with PKWARE implode: GlobalAlloc(GHND, 0x8DD8) work
         * buffer, zeroed 0x34-byte BufferHelper with buffer0 = {src, 0, size}, buffer1 = {dst, 0, size} (output
         * capacity = sizeUncompressed), mode 1, CRC seed -1; calls pkware_implode with the DecoderBuffer callbacks
         * and DecoderState's type/dictionary size. If implode returns 0 and the overflow flag is clear, stores ~crc
         * to *ptrHash and the compressed byte count to *ptrSize and returns TRUE, else FALSE (outputs untouched).
         * The decompiled helper accesses (stack0xffffffc0, _param.* after the call) are 12 bytes off because
         * GlobalAlloc/GlobalLock are treated as caller-cleaned.
         */
        BOOLEnum doImplode(int* ptrHash, int* ptrSize, undefined* src, undefined* dst, int sizeUncompressed);

        /**
         * Decompresses sizeCompressed bytes from src into dst with PKWARE explode: GlobalAlloc(GHND, 0x8DD8) work
         * buffer, zeroed 0x34-byte BufferHelper with buffer1 = {src, 0, sizeCompressed}, buffer2 = {dst, 0,
         * sizeUncompressed}, mode 2, CRC seed -1; calls pkware_explode with the DecoderBuffer callbacks. On success
         * with no overflow stores ~crc of the output through `hash` and returns TRUE, otherwise FALSE. uStack_40 =
         * 0x8DD8 is really the pushed GlobalAlloc size; Ghidra's stack is skewed by 12 bytes
         * (GlobalAlloc/GlobalLock not treated as stdcall), so &uStack_40 in memset/pkware_explode actually means
         * the BufferHelper.
         */
        BOOLEnum doExplode(int* hash, uchar* src, int sizeCompressed, uchar* dst, int sizeUncompressed);

        /**
         * Implodes sizeUncompressed bytes from src into dst+12 (doImplode on DAT_DecoderState) and prefixes a
         * 12-byte header: uncompressed size, compressed size, CRC32 (copied from DecoderState +0xC/+0x10/+0x8 =
         * 0xF2CC30/34/2C). Returns compressed size + 12. doImplode's result is not checked and its output capacity
         * equals sizeUncompressed, so input that does not shrink leaves the previous call's size/CRC in the header.
         */
        int encodeData(int sizeUncompressed, undefined* src, undefined* dst);

        /**
         * Reverse of encodeData: copies the 12-byte header of `source` into DecoderState (sizeUncompressed,
         * sizeCompressed) and the stored CRC32 into a temporary (the dead `source` argument slot), explodes
         * source+12 into `destination` and returns sizeUncompressed if DecoderState.crc32 (set by doExplode) equals
         * the stored CRC, else 0; doExplode's BOOL result is not checked separately.
         */
        dword decodeData(void* source, void* destination);
    };

    static_assert_cpp98_obj(sizeof(DecoderState) == 20, DecoderState);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
