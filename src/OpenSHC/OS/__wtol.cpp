#include "../OS.func.hpp"

#include "stdlib.h"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00580C0B
long OS::__wtol(WCHAR_CONST* wideStr)
{
    long lVar1;
    lVar1 = wcstol(wideStr, (wchar_t**)0x0, 10);
    return (long)(lVar1);
}

}
