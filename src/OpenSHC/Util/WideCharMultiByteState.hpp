/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Util/WideCharMultiByteState.hpp'
*/

#pragma once

#include "winnt.h"

namespace OpenSHC {
namespace Util {

#pragma pack(push, 1)

    // SIZE: 0x00000001
    class WideCharMultiByteState {
    public:
        undefined1 padding_0x0[1]; // 0x00000000 length: 1

    private:
        WideCharMultiByteState(WideCharMultiByteState const&);
        void operator=(WideCharMultiByteState const&);

    public:
        WideCharMultiByteState() {};
        ~WideCharMultiByteState() {};

        /**
         * Converts a NUL-terminated wide string to multibyte in the text manager's code page (length including
         * terminator; output buffer assumed same size). Returns WideCharToMultiByte's result.
         */
        int wideCharToMultiByteComplete(LPSTR charOut, LPCWSTR wideCharIn);

        /**
         * Converts a NUL-terminated multibyte string (code page of the text manager, MB_PRECOMPOSED) to wide
         * characters including the terminator; returns MultiByteToWideChar's result.
         */
        int multiByteToWideCharacter(LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr);

        /**
         * Converts numOfSymbols wide chars to multibyte (text manager code page) and NUL-terminates the output at
         * numOfSymbols; returns the converter result.
         */
        int wideCharToMultiByteWithSize(LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols);

        /**
         * Converts numberOfSymbols multibyte chars to wide chars (text manager code page) and NUL-terminates the
         * output; returns the converter result.
         */
        int multiByteToWideCharWithSize(LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr, int numberOfSymbols);

        /**
         * Converts one wide character to multibyte via a 12-byte local buffer (wideCharToMultiByteWithSize) and
         * returns its first byte.
         */
        char singleWideCharToMultiByte(WCHAR wideChar);

        /**
         * Converts one multibyte character to a wide character via a local buffer and returns the first WCHAR
         * (return value hidden behind the security-cookie call).
         */
        WCHAR singleMultiByteToWideChar(char character);
    };

    static_assert_cpp98_obj(sizeof(WideCharMultiByteState) == 1, WideCharMultiByteState);

#pragma pack(pop)

} // namespace Util
} // namespace OpenSHC
