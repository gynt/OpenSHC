/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/OS.hpp'
*/

#pragma once

#include "OpenSHC/OS/_atexit_t.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "crtdefs.h"
#include "fcntl.h"
#include "guiddef.h"
#include "mbstring.h"
#include "stdio.h"
#include "sys/stat.h"
#include "time.h"
#include "vadefs.h"
namespace OpenSHC {
namespace OS {

    using OpenSHC::OS::_atexit_t;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /**
     * MSVC STL operator<<(basic_ostream<char>&, char): builds a sentry; if ok, writes the character padded with the
     * fill char up to width (padding first unless adjustfield == left), sets badbit on put failure (via ios::clear,
     * also badbit if rdbuf is NULL), resets width to 0, flushes via _Osfx when no exception is in flight, releases
     * the streambuf lock and returns the stream. Used by WindowAndDirectDraw::takeScreenshot.
     */
    int* __stdcall basic_ostream_insertChar(void* stream, uint ch);

    /**
     * MSVC inline IsEqualGUID / operator==(GUID,GUID): compares the two 16-byte GUIDs (4 bytes at a time, then
     * byte-wise on mismatch) and returns TRUE if identical, FALSE otherwise.
     */
    BOOLEnum __cdecl isEqualGUID(GUID* guid1, GUID* guid2);

    /**
     * MSVC CRT localtime (64-bit time_t): gets the per-thread tm buffer and fills it with _localtime64_s; returns
     * the buffer, or NULL on failure.
     */
    tm* __cdecl _localtime(time_t* _Time);

    /**
     * MSVC CRT _time64: reads GetSystemTimeAsFileTime, converts 100-ns ticks since 1601 to seconds since 1970,
     * optionally stores it in *_Time and returns it.
     */
    __time64_t __cdecl __time64(__time64_t* _Time);

    /**
     * MSVC CRT memset: fills _Size bytes with (byte)_Val; zero fills of >255 bytes use __VEC_memzero when SSE2 is
     * present, otherwise aligns then stores dwords and trailing bytes. Returns _Dst.
     */
    void* __cdecl _memset(void* _Dst, int _Val, size_t _Size);

    /**
     * MSVC CRT sprintf: formats into _Dest via _output_l using a fake string FILE (unbounded), NUL-terminates;
     * returns character count or -1 on invalid args.
     */
    int __cdecl _sprintf(char* _Dest, char const* _Format, ...);

    /**
     * MSVC CRT _stricmp: case-insensitive string compare (ASCII fast path when no locale is set, else _stricmp_l);
     * returns <0/0/>0 or 0x7fffffff on NULL args.
     */
    int __cdecl __stricmp(char const* _Str1, char const* _Str2);

    /**
     * MSVC CRT atexit: registers func via _onexit; returns 0 on success, -1 on failure.
     */
    int __cdecl _atexit(_atexit_t* func);

    /**
     * MSVC CRT free() (VS2005 release CRT; source-level _free_base; FID matches _free and game code calls it
     * directly, e.g. 0x44C7EB). NULL is ignored. With the V6 small-block heap active (g_activeHeap == 3) it looks
     * the block up with ___sbh_find_block under heap lock 4 and frees it with ___sbh_free_block, returning if
     * found; otherwise HeapFree on the CRT heap, mapping failure to errno.
     */
    void __cdecl _free_base(void* _Memory);

    /**
     * MSVC CRT tolower: ASCII A-Z to lower case when no locale is set, otherwise _tolower_l.
     */
    int __cdecl __tolower(int _C);

    /**
     * MSVC CRT fclose: validates the FILE, closes it under the file lock via _fclose_nolock (string streams just
     * get their flag cleared); returns 0 or EOF.
     */
    int __cdecl _fclose(FILE* _File);

    /**
     * MSVC CRT fread: forwards to _fread_s with unlimited buffer size; returns number of elements read.
     */
    size_t __cdecl _fread(void* dstBuffer, size_t elSize, size_t count, FILE* file);

    /**
     * MSVC CRT malloc: sizes > 0xFFFFFFE0 fail with ENOMEM. Loop: exits the process if the CRT heap is missing; in
     * system-heap mode HeapAlloc(size or 1); in V6 mode tries the small-block heap (_V6_HeapAlloc) first, else
     * HeapAlloc with size rounded up to 16 bytes. On failure retries through _callnewh when _newmode is set,
     * otherwise sets errno ENOMEM and returns NULL.
     */
    void* __cdecl _malloc(size_t _Size);

    /**
     * MSVC CRT ftell: returns the current file position under the file lock (_ftell_nolock), -1 on error.
     */
    long __cdecl _ftell(FILE* _File);

    /**
     * MSVC CRT fseek: validates stream and origin (SEEK_SET/CUR/END), seeks under the file lock; returns 0 or -1.
     */
    int __cdecl _fseek(FILE* _File, long _Offset, DWORD _Origin);

    /**
     * MSVC CRT fopen: _fsopen with _SH_DENYNO (0x40).
     */
    FILE* __cdecl _fopen(char const* _Filename, char const* _Mode);

    /**
     * MSVC CRT legacy _vswprintf (no buffer size): calls 0x5804E0 = _vswprintf_l(dest, format, NULL locale, args)
     * and returns its result. The garbled decompiled call comes from a wrong 5-parameter prototype on the callee,
     * not from a tail call.
     */
    int __cdecl __vswprintf(wchar_t* _Dest, wchar_t* _Format, va_list _Args);

    /**
     * MSVC CRT fgetwc: reads one wide char under the file lock; returns WEOF (0xFFFF) on NULL stream.
     */
    wint_t __cdecl _fgetwc(FILE* _File);

    int __cdecl _fwprintf(FILE* param_1, wchar_t const* param_2, ...);

    /**
     * MSVC CRT fwrite: writes _Count elements of _Size under the file lock; returns elements written (0 on bad
     * args).
     */
    size_t __cdecl _fwrite(void* _Str, size_t _Size, size_t _Count, FILE* _File);

    /**
     * MSVC CRT wcsncpy: copies up to _Count wide chars and zero-pads the rest of the buffer; returns _Dest.
     */
    wchar_t* __cdecl _wcsncpy(wchar_t* _Dest, wchar_t* _Source, size_t _Count);

    /**
     * MSVC CRT _wcsicmp: case-insensitive wide-string compare (ASCII A-Z folding when no locale, else _wcsicmp_l);
     * returns difference of first mismatching folded chars.
     */
    int __cdecl __wcsicmp(wchar_t const* _Str1, wchar_t const* _Str2);

    long __cdecl __wtol(wchar_t const* wideStr);

    void __cdecl _free(void* _Memory);

    /**
     * MSVC CRT memcpy_s: copies _MaxCount bytes when the source is non-NULL and they fit in _DstSize (returns 0;
     * also 0 when _MaxCount == 0). NULL destination -> EINVAL; NULL source or overflow -> zero-fills the
     * destination and returns EINVAL / ERANGE; errors go through _invalid_parameter.
     */
    errno_t __cdecl _memcpy_s(void* _Dst, rsize_t _DstSize, void* _Src, rsize_t _MaxCount);

    void __cdecl _free_cpp(void* _Memory);

    /**
     * MSVC CRT _close: validates the low-level file descriptor against the ioinfo table, locks it and calls
     * _close_nolock; returns 0 or -1 (errno EBADF). NAME? This is plain _close, not a UCRT function.
     */
    int __cdecl _ucrt_close(int fileDescriptor);

    /**
     * MSVC CRT _read: validates descriptor and size (< 2 GB), locks the handle and calls _read_nolock; returns
     * bytes read or -1. NAME? This is the VS2005 CRT _read, not a UCRT function.
     */
    int __cdecl _ucrt_read(int fileDescriptor, void* destination, size_t size);

    /**
     * MSVC CRT _open: calls _sopen_helper with _SH_DENYNO; returns the file descriptor or -1. NAME? This is the
     * VS2005 CRT _open, not a UCRT function.
     */
    int __cdecl _ucrt_open(char* _Filename, int _OpenFlag, int _PMode);

    /**
     * MSVC CRT srand: stores seed into the per-thread _holdrand.
     */
    void __cdecl _srand(ulong seed);

    /**
     * MSVC CRT rand: per-thread LCG holdrand = holdrand*214013 + 2531011; returns bits 16..30 (0..32767).
     */
    int __cdecl _rand();

    /**
     * MSVC CRT _strlwr: lowercases A-Z in place (ASCII path when no locale, else _strlwr_s_l); returns the string
     * or NULL on NULL input.
     */
    char* __cdecl __strlwr(char* string);

    /**
     * MSVC CRT _write: validates the descriptor, locks the handle and calls _write_nolock; returns bytes written or
     * -1. NAME? This is the VS2005 CRT _write, not a UCRT function.
     */
    int __cdecl _ucrt_write(int fileDescriptor, void const* src, uint size);

    /**
     * MSVC CRT memcpy (memmove-capable): copies backwards when the ranges overlap with dst after src, otherwise
     * forwards using __VEC_memcpy for co-aligned (same address & 15) >255-byte copies when SSE2 is available, or
     * dword loops with byte head/tail. Returns _Dst.
     */
    void* __cdecl _memcpy(void* _Dst, void* _Src, size_t _Size);

    /**
     * MSVC CRT toupper: ASCII a-z to upper case when no locale is set, otherwise _toupper_l.
     */
    int __cdecl __toupper(int _C);

    /**
     * MSVC CRT _tell: _lseek(handle, 0, SEEK_CUR); returns the current position. NAME? This is the VS2005 CRT
     * _tell, not a UCRT function.
     */
    int __cdecl _ucrt_tell(int handle);

    /**
     * MSVC CRT _lseek: validates the descriptor, locks it and moves the file pointer via the nolock helper; returns
     * new position or -1. NAME? This is the VS2005 CRT _lseek, not a UCRT function.
     */
    int __cdecl _ucrt_lseek(int fileDescriptor, long lDistanceToMove, DWORD moveMethod);

    /**
     * MSVC CRT _strnicmp: case-insensitive compare of up to _MaxCount chars (ASCII fast path or _strnicmp_l);
     * 0x7fffffff on invalid args.
     */
    int __cdecl __strnicmp(char const* _Str1, char const* _Str2, size_t _MaxCount);

    /**
     * MSVC CRT exit: doexit(code, 0, 0) runs atexit handlers and terminates the process.
     */
    __declspec(noreturn) void __cdecl _exit(int _Code);

    int _fwprintf(FILE* stream, wchar_t const* format, ...);

    long __wtol(wchar_t const* str);

} // namespace OS
} // namespace OpenSHC
