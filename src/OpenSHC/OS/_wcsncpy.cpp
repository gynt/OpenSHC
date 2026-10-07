#include "../OS.func.hpp"

namespace OpenSHC {

/*
  Library Function - Single Match   Name: _wcsncpy   Library: Visual Studio 2005 Release   decompilerscript: committed:
  2025-01-30 21:57:43.216000
 */
// FUNCTION: STRONGHOLDCRUSADER 0x00580A1D
wchar_t* OS::_wcsncpy(wchar_t* _Dest, wchar_t* _Source, size_t _Count)
{
    wchar_t wVar1;
    uint uVar2;
    uint uVar3;
    wchar_t* pwVar4;
    pwVar4 = _Dest;
    if (_Count) {
        do {
            wVar1 = *_Source;
            *pwVar4 = wVar1;
            pwVar4 = pwVar4 + 1;
            _Source = _Source + 1;
            if (wVar1 == L'\0')
                break;
            _Count = _Count - 1;
        } while (_Count);
        if ((_Count) && (uVar2 = _Count - 1, uVar2)) {
            for (uVar3 = uVar2 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
                pwVar4[0] = L'\0';
                pwVar4[1] = L'\0';
                pwVar4 = pwVar4 + 2;
            }
            for (uVar2 = (uint)((uVar2 & 1)); uVar2 != 0; uVar2 = uVar2 - 1) {
                *pwVar4 = L'\0';
                pwVar4 = pwVar4 + 1;
            }
        }
    }
    return _Dest;
}

}
