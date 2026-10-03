#include "../Global.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0046F570
byte Global::TestOSVersion()
{
    byte _retFlag;
    uint _unknownSecRelated;
    _OSVERSIONINFOEXA _versionInfoEx;
    _unknownSecRelated = MSVC_SecurityCookie::instance ^ (uint)&_versionInfoEx;
    MACRO_CALL(OpenSHC::OS_Func::_memset)(&_versionInfoEx, 0, 0x9c);
    _versionInfoEx.dwOSVersionInfoSize = 0x9c;
    GetVersionExA((_OSVERSIONINFOA*)&_versionInfoEx);
    if ((_versionInfoEx.dwPlatformId == 2) && (4 < _versionInfoEx.dwMajorVersion)) {
        if (_versionInfoEx.dwMajorVersion == 6) {
            if (1 < _versionInfoEx.dwMinorVersion) {
                _retFlag = 1;
                ;
                return (byte)(_retFlag);
            }
        } else {
            _retFlag = 1;
            if (6 < _versionInfoEx.dwMajorVersion)
                goto LAB_0046f5eb;
        }
    }
    _retFlag = 0;
LAB_0046f5eb:;
    return (byte)(_retFlag);
}

}
