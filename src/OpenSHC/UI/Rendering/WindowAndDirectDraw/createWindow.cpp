#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "WindowsSystemMetricInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "GeneralWindowsMessage": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00467A90
        BOOLEnum WindowAndDirectDraw::createWindow(LPCSTR windowName, uint cursorResource)
        {
            ATOM _atom;
            int nHeight;
            int nWidth;
            HWND__* hWndParent;
            HMENU__* hMenu;
            HINSTANCE__* hInstance;
            void* lpParam;
            WNDCLASSA _wndClassA;
            _wndClassA.lpfnWndProc = MACRO_CALL(OpenSHC::Global_Func::WindowMsgProcessingFunc);
            _wndClassA.style = 0;
            _wndClassA.cbClsExtra = 0;
            _wndClassA.cbWndExtra = 0;
            _wndClassA.hInstance = this->hInstanceUnk_0xa8;
            _wndClassA.hIcon = LoadIconA(this->hInstanceUnk_0xa8, (CHAR*)(cursorResource & 0xffff));
            _wndClassA.hCursor = (HICON__*)0x0;
            _wndClassA.hbrBackground = (HBRUSH__*)0x0;
            _wndClassA.lpszMenuName = (CHAR*)0x0;
            _wndClassA.lpszClassName = "FFwinClass";
            _atom = RegisterClassA(&_wndClassA);
            if (_atom == 0) {
                return FALSE;
            }
            lpParam = (void*)0x0;
            hMenu = (HMENU__*)0x0;
            hWndParent = (HWND__*)0x0;
            hInstance = this->hInstanceUnk_0xa8;
            nHeight = GetSystemMetrics(SM_CYSCREEN);
            nWidth = GetSystemMetrics(SM_CXSCREEN);
            this->windowHandle = CreateWindowExA(
                0, "FFwinClass", windowName, 0x90000000, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
            return (uint)(this->windowHandle != (HWND__*)0x0);
        }

    }
}
}
