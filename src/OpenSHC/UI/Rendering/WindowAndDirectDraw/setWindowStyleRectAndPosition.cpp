#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Rendering/WindowInformation.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_WindowInformation.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046F750
        void WindowAndDirectDraw::setWindowStyleRectAndPosition()
        {
            int _y;
            int _x;
            uint dwStyle;
            tagRECT _intendedWindowRect;
            /*
              initially visible + (either pop-up window if f98390 is set, or a window with   a title bar and ...
              0xCA0000 -> WS_BORDER, WS_DLGFRAME, WS_SYSMENU, WS_MINIMIZEBOX      Hoever, if exclusive, it becomes only:
              WS_POPUP
             */
            dwStyle = (-(uint)(this->runGameAsExclusiveFullscreen != FALSE) & 0x7f360000) + 0xca0000 | 268435456;
            /*
              set a new window style GWL_STYLE      Needed to add signature overwrite to not break stack analysis.
              -TheRedDaemon
             */
            SetWindowLongA(this->windowHandle, GWL_STYLE, dwStyle);
            SetRect(&_intendedWindowRect, 0, 0, this->resolutionX, this->resolutionY);
            AdjustWindowRect(&_intendedWindowRect, dwStyle, 0);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::WindowInformation_Func::storeWindowRectangleInfoUnk,
                DAT_WindowInformation::ptr)(0, 0, (LONG)((int)(this->resolutionX)), (LONG)((int)(this->resolutionY)));
            _x = this->resolutionX;
            _y = this->resolutionY;
            if (this->runGameAsExclusiveFullscreen != FALSE) {
                _y = GetSystemMetrics(SM_CYSCREEN);
                _x = GetSystemMetrics(SM_CXSCREEN);
            }
            SetRect(&this->clientOnScreenCoords, 0, 0, _x, _y);
            this->gameInWindowPosY_0x34 = (_intendedWindowRect.bottom - _intendedWindowRect.top) - this->resolutionY;
            this->gameInWindowPosX_0x30 = (_intendedWindowRect.right - this->resolutionX) - _intendedWindowRect.left;
            this->gameOnScreenPosY_0x2c = (this->screenVerticalResolutionInPixels - this->gameResolutionY) / 2 + -0x14;
            this->gameOnScreenPosX_0x28 = (this->screenHorizontalResolutionInPixels - this->gameResolutionX) / 2;
            SetWindowPos(this->windowHandle, (HWND__*)-2, this->gameOnScreenPosX_0x28 - _intendedWindowRect.left,
                this->gameOnScreenPosY_0x2c - _intendedWindowRect.top,
                _intendedWindowRect.right - _intendedWindowRect.left,
                _intendedWindowRect.bottom - _intendedWindowRect.top, 0x10);
            UpdateWindow(this->windowHandle);
            SetFocus(this->windowHandle);
            return;
        }

    }
}
}
