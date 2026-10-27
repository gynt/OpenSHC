/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/DecoderBuffer.hpp'
*/

#pragma once

#include "OpenSHC/IO/Helpers/BufferHelper.hpp"
namespace OpenSHC {
namespace IO {
    namespace DecoderBuffer {

        using OpenSHC::IO::Helpers::BufferHelper;

        /**
         * PKWARE implode/explode read callback. `param` is a BufferHelper: returns 0 if its overflow flag (+0x30)
         * is set; otherwise copies up to *size bytes from buffer0 (imploding, mode 1) or buffer1 (exploding) at its
         * current offset into buf and advances the offset. When imploding, updates the running CRC32 (+0x28) over
         * the bytes read. Returns the byte count read.
         */
        uint __cdecl ReadBufferAndComputeHash(char* buf, uint* size, void* param);

        /**
         * PKWARE implode/explode write callback. `param` is a BufferHelper: unless the overflow flag (+0x30) is
         * set, appends *size bytes from buf to buffer1 (imploding, also adds to compressedSize +0x2C) or buffer2
         * (exploding); sets the overflow flag if the data does not fit. When exploding (mode 2), updates the
         * running CRC32 (+0x28) over the written bytes.
         */
        void __cdecl WriteBufferAndComputeHash(char* buf, uint* size, void* param);

    } // namespace DecoderBuffer
} // namespace IO
} // namespace OpenSHC
