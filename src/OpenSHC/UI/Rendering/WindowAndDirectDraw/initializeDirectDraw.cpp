#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using Rendering::ColorMode;
        using Rendering::ScreenResolutionEnum;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046FA70
        BOOLEnum WindowAndDirectDraw::initializeDirectDraw()
        {
            byte _osVersionTest;
            HRESULT _hResult;
            ScreenResolutionEnumInt _intendedRes;
            HRESULT _hResult2;
            HRESULT _hResultScreenSetting;
            HRESULT _hResult3;
            HRESULT _hResult8;
            HRESULT _hResult9;
            HRESULT _hResult4;
            HRESULT _hResult5;
            HRESULT _hResult6;
            HRESULT _hResult7;
            int _xScreenRes;
            int* _resPointer;
            int _copyLengthScreenMenuDesc;
            int _copyLengthMapGameDesc;
            DWORD* _surfDescScreenMenu_RunPtr;
            DWORD* _surfDescMapGame_RunPtr;
            DWORD* _surfDescScreenMenuBink_RunPtr;
            DWORD* _surfDescMapGameBink_RunPtr;
            DDSURFACEDESC _ddsurfacedesc;
            DDCAPS_SHC _ddcaps;
            IDirectDrawSurface* _directDrawOffscreenSurfacePointer_screenMenu;
            IDirectDrawSurface* _directDrawOffscreenSurfacePointer_mapGame;
            ScreenResolutionEnumInt _runRes;
            IDirectDrawSurface* _surfacePtrGame;
            IDirectDrawSurface* _surfacePtrMap;
            int _yScreenRes;
            /*
              this function has many messed up stack things because DirectDrawCreate is not   properly referenced
             */
            if (this->pointerToIDirectDrawInterface == (IDirectDraw*)0x0) {
                _osVersionTest = MACRO_CALL(Global_Func::TestOSVersion)();
                if (!_osVersionTest) {
                    _hResult = DirectDrawCreate(
                        (GUID*)0x0, (IDirectDraw**)((int)(&this->pointerToIDirectDrawInterface)), (IUnknown*)0x0);
                } else {
                    _hResult = DirectDrawCreate(
                        (GUID*)0x2, (IDirectDraw**)((int)(&this->pointerToIDirectDrawInterface)), (IUnknown*)0x0);
                }
                this->NOTSelfBufferOrWindowMode_0xf8 = TRUE;
                /*
                  HRESULT not really enumerable. This "if" is executed if the Interface   creation fails.
                 */
                if (_hResult) {
                    return FALSE;
                }
            }
            MACRO_CALL(OS_Func::_memset)(&_ddcaps, 0, 0x17c);
            _ddcaps.dwSize = 0x17c;
            /*
              Signature Overwrite
             */
            this->pointerToIDirectDrawInterface->GetCaps(&_ddcaps, (DDCAPS_SHC*)0x0);
            /*
              DDCAPS2_CANBOBHARDWARE == 0x4000   "The overlay hardware can display each field of an interlaced video
              stream   individually."   Seems it sets some flag based on this condtion. But I am not sure what it means.
              -TheRedDaemon
             */
            if (!(_ddcaps.dwCaps2 & DDCAPS2_CANBOBHARDWARE)) {
                this->not_DDCAPS2_CANBOBHARDWARE_0xe0 = TRUE;
            }
            /*
              Signature Overwrite
             */
            this->pointerToIDirectDrawInterface->EnumDisplayModes(0,
                (DDSURFACEDESC*)0x0, (void*)0x0, MACRO_CALL(Synchrony_Func::EnumDisplayModesCallback));
            if (((int)this->currentGameResolution < 0)
                || ((&this->resolutionSupported_0x68.noneUnk)[this->currentGameResolution] == 0)) {
                this->currentGameResolution = Rendering::SRE_neg1;
                _intendedRes = Rendering::SRE_1920x1200;
                _resPointer = &this->resolutionSupported_0x68.1920x1200;
                do {
                    _runRes = _intendedRes;
                    if (*_resPointer != 0)
                        break;
                    _intendedRes = _intendedRes - Rendering::SRE_800x600;
                    _resPointer = _resPointer + -1;
                    _runRes = this->currentGameResolution;
                } while (0 < (int)_intendedRes);
                this->currentGameResolution = _runRes;
                if (this->currentGameResolution == Rendering::SRE_neg1) {
                    if (!this->resolutionSupported_0x68.1360x768) {
                        /*
                          If I am not mistaken, then if 1024x600 supported then use this, else 800x600.   -TheRedDaemon
                         */
                        this->currentGameResolution
                            = (-(uint)(this->resolutionSupported_0x68.1024x600) & 0xe) + Rendering::SRE_800x600;
                    } else {
                        this->currentGameResolution = Rendering::SRE_1360x768;
                    }
                }
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            }
            if (this->runGameAsExclusiveFullscreen == FALSE) {
                /*
                  DDSC_NORMAL -> Wants to be a normal window      Signature Overwrite
                 */
                _hResultScreenSetting = this->pointerToIDirectDrawInterface->SetCooperativeLevel(this->windowHandle, 8);
            } else {
                /*
                  DDSCL_FULLSCREEN, DDSCL_EXCLUSIVE, DDSCL_ALLOWREBOOT -> Takes the screen.   Normally the known
                  behaviour.      Signature Overwrite
                 */
                _hResult2 = this->pointerToIDirectDrawInterface->SetCooperativeLevel(this->windowHandle, 0x13);
                if (_hResult2)
                    goto LAB_0046fbca;
                /*
                  Signature Overwrite
                 */
                _hResultScreenSetting = this->pointerToIDirectDrawInterface->SetDisplayMode(this->resolutionX, this->resolutionY, 0x10);
            }
            /*
              If it fails:
             */
            if (_hResultScreenSetting) {
            LAB_0046fbca:
                MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }
            /*
              Self-Buffering? Or window mode? -TheRedDaemon
             */
            if (this->NOTSelfBufferOrWindowMode_0xf8 == FALSE) {
                MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, (size_t)((int)(108)));
                _ddsurfacedesc.dwSize = 0x6c;
                _ddsurfacedesc.dwFlags = 1;
                _ddsurfacedesc.ddsCaps = 0x200;
                /*
                  Caps valid. -> Primary surface.      In this case, the game draws directly on the otherwise
                  "backbuffer".   I assume they double buffer it themselves.   - TheRedDaemon      Signature Overwrite
                 */
                _hResult3 = this->pointerToIDirectDrawInterface->CreateSurface(&_ddsurfacedesc, &this->directDrawBackbufferSurfacePointer,
                    (IUnknown*)0x0);
                if (_hResult3) {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(TRUE);
                    return FALSE;
                }
            } else {
                MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, 0x6c);
                _ddsurfacedesc.dwBackBufferCount = 1;
                _ddsurfacedesc.dwSize = 0x6c;
                _ddsurfacedesc.dwFlags = 0x21;
                _ddsurfacedesc.ddsCaps = 0x218;
                /*
                  Backbuffer count and caps valid. -> Primary, complex and flip      Signature Overwrite
                 */
                _hResult8 = this->pointerToIDirectDrawInterface->CreateSurface(&_ddsurfacedesc, &this->directDrawPrimarySurfacePointer,
                    (IUnknown*)0x0);
                if (_hResult8)
                    goto LAB_0046fe31;
                MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, 0x6c);
                _ddsurfacedesc.dwSize = 0x6c;
                _ddsurfacedesc.dwFlags = 1;
                _ddsurfacedesc.ddsCaps = 4;
                /*
                  Caps valid
                 */
                /*
                  Signature Overwrite
                 */
                _hResult9 = this->directDrawPrimarySurfacePointer->GetAttachedSurface(&_ddsurfacedesc.ddsCaps,
                    &this->directDrawBackbufferSurfacePointer);
                if (_hResult9)
                    goto LAB_0046fe31;
            }
            MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, (size_t)((int)(108)));
            _ddsurfacedesc.dwWidth = this->resolutionX;
            _ddsurfacedesc.dwSize = 0x6c;
            _ddsurfacedesc.dwFlags = 7;
            _ddsurfacedesc.ddsCaps = 2112;
            _ddsurfacedesc.dwHeight = this->resolutionY;
            /*
              Signature Overwrite
             */
            _hResult4
                = this->pointerToIDirectDrawInterface->CreateSurface(&_ddsurfacedesc, &this->directDrawOffscreenSurfacePointer_screenMenu, (IUnknown*)0x0);
            if (!_hResult4) {
                DAT_BinkControlState::instance.screenMenuSurfaceType_0x5c
                    = BinkDDSurfaceType(this->directDrawOffscreenSurfacePointer_screenMenu);
                _surfacePtrGame = this->directDrawOffscreenSurfacePointer_screenMenu;
                _copyLengthScreenMenuDesc = 27;
                _surfDescScreenMenu_RunPtr = &_ddsurfacedesc.dwSize;
                _surfDescScreenMenuBink_RunPtr = &this->surfDescBink_offSurfScreenMenu_0x104.dwSize;
                for (; _copyLengthScreenMenuDesc != 0; _copyLengthScreenMenuDesc = _copyLengthScreenMenuDesc + -1) {
                    *_surfDescScreenMenuBink_RunPtr = *_surfDescScreenMenu_RunPtr;
                    _surfDescScreenMenu_RunPtr = _surfDescScreenMenu_RunPtr + 1;
                    _surfDescScreenMenuBink_RunPtr = _surfDescScreenMenuBink_RunPtr + 1;
                }
                /*
                  Signature Overwrite
                 */
                _hResult5
                    = (*_surfacePtrGame->vTable->Lock)(_surfacePtrGame, (tagRECT*)0x0, &_ddsurfacedesc, 1, (void*)0x0);
                if (!_hResult5) {
                    this->surfacePointer_screenMenu = _ddsurfacedesc.lpSurface;
                    /*
                      Would break, since ghidra is unable to resolve the stack ptr changes.      Signature Overwrite to
                      solve
                     */
                    this->directDrawOffscreenSurfacePointer_screenMenu->Unlock((tagRECT*)0x0);
                    MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, 0x6c);
                    _ddsurfacedesc.dwSize = 0x6c;
                    _ddsurfacedesc.dwFlags = 7;
                    _ddsurfacedesc.ddsCaps = 0x840;
                    _ddsurfacedesc.dwHeight = 0x81c;
                    _ddsurfacedesc.dwWidth = 0xfd8;
                    /*
                      Signature Overwrite
                     */
                    _hResult6 = this->pointerToIDirectDrawInterface->CreateSurface(&_ddsurfacedesc,
                        &this->directDrawOffscreenSurfacePointer_mapGame, (IUnknown*)0x0);
                    if (!_hResult6) {
                        DAT_BinkControlState::instance.mapGameSurfaceType
                            = BinkDDSurfaceType(this->directDrawOffscreenSurfacePointer_mapGame);
                        _surfacePtrMap = this->directDrawOffscreenSurfacePointer_mapGame;
                        _copyLengthMapGameDesc = 0x1b;
                        _surfDescMapGame_RunPtr = &_ddsurfacedesc.dwSize;
                        _surfDescMapGameBink_RunPtr = &this->surfDescBink_offSurfMapGame.dwSize;
                        for (; _copyLengthMapGameDesc != 0; _copyLengthMapGameDesc = _copyLengthMapGameDesc + -1) {
                            *_surfDescMapGameBink_RunPtr = *_surfDescMapGame_RunPtr;
                            _surfDescMapGame_RunPtr = _surfDescMapGame_RunPtr + 1;
                            _surfDescMapGameBink_RunPtr = _surfDescMapGameBink_RunPtr + 1;
                        }
                        /*
                          Signature Overwrite
                         */
                        _hResult7 = (*_surfacePtrMap->vTable->Lock)(
                            _surfacePtrMap, (tagRECT*)0x0, &_ddsurfacedesc, 1, (void*)0x0);
                        if (!_hResult7) {
                            this->surfacePointer_mapGame = _ddsurfacedesc.lpSurface;
                            /*
                              Same, also breaks stack ptr.      Signature Overwrite
                             */
                            this->directDrawOffscreenSurfacePointer_mapGame->Unlock((tagRECT*)0x0);
                            MACRO_CALL(OS_Func::_memset)(&_ddsurfacedesc, 0, 0x6c);
                            _ddsurfacedesc.dwSize = 0x6c;
                            _ddsurfacedesc.ddpfPixelFormat.dwSize = 0x20;
                            _ddsurfacedesc.dwFlags = 0x1000;
                            /*
                              Signature Overwrite
                             */
                            this->directDrawBackbufferSurfacePointer->GetSurfaceDesc(&_ddsurfacedesc);
                            /*
                              Check the bit mask for green. If 6bit, then use the 565 mode.
                             */
                            this->colorBitMode = Rendering::RGB_555;
                            if (_ddsurfacedesc.ddpfPixelFormat.union_bitMask_GorU == 0x7e0) {
                                this->colorBitMode = Rendering::RGB_565;
                            }
                            MACRO_CALL(Rendering_Func::InitializeColors)();
                            if (this->runGameAsExclusiveFullscreen == FALSE) {
                                GetClientRect(this->windowHandle, &this->clientOnScreenCoords);
                                ClientToScreen(
                                    this->windowHandle, (LPPOINT)((int)((tagPOINT*)&this->clientOnScreenCoords)));
                                ClientToScreen(
                                    this->windowHandle, (LPPOINT)((int)((tagPOINT*)&this->clientOnScreenCoords.right)));
                                UpdateWindow(this->windowHandle);
                                return TRUE;
                            }
                            _yScreenRes = GetSystemMetrics(SM_CYSCREEN);
                            _xScreenRes = GetSystemMetrics(SM_CXSCREEN);
                            SetRect(&this->clientOnScreenCoords, 0, 0, _xScreenRes, _yScreenRes);
                            return TRUE;
                        }
                    }
                }
            }
        LAB_0046fe31:
            MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                TRUE);
            return FALSE;
        }

    }
}
}
