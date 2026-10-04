#include <ddraw.h>

#include "../Global.func.hpp"

#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"

#include "OpenSHC/Globals/IID_IDirectDraw7.hpp"

namespace OpenSHC {

using Rendering::Enums::DirectDrawStatus;

// FUNCTION: STRONGHOLDCRUSADER 0x0046F4F0
DirectDrawStatus Global::DetectDXVersionByLoadingDDRAW()
{
    typedef HRESULT(WINAPI * DirectDrawCreateExFunc)(GUID FAR*, LPVOID*, REFIID, IUnknown FAR*);
    HINSTANCE__* hLibModule;
    FARPROC _funcAddress;
    DirectDrawCreateExFunc _funcAddressEx;
    HRESULT _foundDirectDraw;
    IDirectDraw* _testInterface;
    hLibModule = LoadLibraryA("DDRAW.DLL");
    if (hLibModule == (HINSTANCE__*)0x0) {
        return Rendering::Enums::DD7_NOT_LOADED;
    }
    _funcAddress = GetProcAddress(hLibModule, "DirectDrawCreate");
    if (_funcAddress != (FARPROC)0x0) {
        _funcAddressEx = (DirectDrawCreateExFunc)GetProcAddress(hLibModule, "DirectDrawCreateEx");
        if (_funcAddressEx != (DirectDrawCreateExFunc)0x0) {
            _foundDirectDraw = (*_funcAddressEx)(
                (GUID*)0x0, (LPVOID*)&_testInterface, *IID_IDirectDraw7::ptr, (IUnknown*)0x0);
            if (-1 < _foundDirectDraw) {
                _testInterface->Release();
                FreeLibrary(hLibModule);
                return Rendering::Enums::DD7_LOADED;
            }
        }
    }
    FreeLibrary(hLibModule);
    return Rendering::Enums::DD7_NOT_LOADED;
}

}
