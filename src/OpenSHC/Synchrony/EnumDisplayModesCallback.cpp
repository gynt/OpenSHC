#include "../Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

/*
  Function always returns DDENUMRET_OK (1).   It seems the supported resolutions are hardcoded. They check for the
  dimensions and then set a   flag. -TheRedDaemon   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */
// FUNCTION: STRONGHOLDCRUSADER 0x00467BC0
HRESULT __stdcall Synchrony::EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam)
{
    DWORD _bitCount;
    DWORD _displayHeight;
    DWORD _displayWidth;
    _displayWidth = displayDesc->dwWidth;
    _displayHeight = displayDesc->dwHeight;
    _bitCount = (displayDesc->ddpfPixelFormat).dwRGBBitCount;
    if ((_bitCount == 0xf) || (_bitCount == 0x10)) {
        if (_displayWidth == 800) {
            if (_displayHeight == 600) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._800x600 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x400) {
            if (_displayHeight == 0x300) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1024x768 = 1;
                return 1;
            }
            if (_displayHeight == 600) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1024x600 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x500) {
            if (_displayHeight == 0x400) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1280x1024 = 1;
                return 1;
            }
            if (_displayHeight == 0x2d0) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1280x720 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x640) {
            if (_displayHeight == 0x4b0) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1600x1200 = 1;
                return 1;
            }
            if (_displayHeight == 900) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1600x900 = 1;
            }
        } else if (_displayWidth == 0x5a0) {
            if (_displayHeight == 900) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1440x900 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x780) {
            if (_displayHeight == 0x438) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1920x1080 = 1;
                return 1;
            }
            if (_displayHeight == 0x4b0) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1920x1200 = 1;
                return 1;
            }
        } else if (_displayWidth == 0xa00) {
            if (_displayHeight == 0x5a0) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._2560x1440 = 1;
                return 1;
            }
            if (_displayHeight == 0x640) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._2560x1600 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x556) {
            if (_displayHeight == 0x300) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1366x768 = 1;
                return 1;
            }
        } else if (_displayWidth == 0x550) {
            if (_displayHeight == 0x300) {
                DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1360x768 = 1;
                return 1;
            }
        } else if ((_displayWidth == 0x690) && (_displayHeight == 0x41a)) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68._1680x1050 = 1;
            return 1;
        }
    }
    return 1;
}

}
