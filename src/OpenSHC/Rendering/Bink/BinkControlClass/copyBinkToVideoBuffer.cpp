#include "../../../Rendering.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Rendering/Bink/UnsortedBinkFlag.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/UI/Menu.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using Audio::MSS::enums::SHC_SoundStream;
        using Rendering::Bink::UnsortedBinkFlag;
        using WindowsHelper::Enums::BOOLEnum;
        using UI::Menu;

        // FUNCTION: STRONGHOLDCRUSADER 0x00408FC0
        void BinkControlClass::copyBinkToVideoBuffer(dword param_1)
        {
            BOOLEnum _soundPlaying;
            DWORD _sysTime;
            long _waitingForFrame;
            HRESULT _hResultLock2;
            HRESULT _hResultRestore;
            HRESULT _hResultLock;
            IDirectDrawSurface* _surfacePointer;
            BinkControlClass* _binkStructPtr;
            int _binkObjIndex;
            FakeBink* _binkObjPtr;
            Menu* _menu;
            int _menuBorderHeight;
            int _menuBorderWidth;
            _binkObjIndex = 0;
            _binkStructPtr = (BinkControlClass*)this->soundStreamIndex;
            do {
                if ((_binkStructPtr->soundStreamIndex[0] != Audio::MSS::enums::SND_STR_MUSIC)
                    && ((_soundPlaying = MACRO_CALL_MEMBER(
                             Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                             (Audio::MSS::enums::SHC_SoundStream)(_binkStructPtr->soundStreamIndex[0])),
                        !_soundPlaying
                            || (_sysTime = timeGetTime(), 20000 < _sysTime - _binkStructPtr->startTime[0])))) {
                    _binkStructPtr->soundStreamIndex[0] = Audio::MSS::enums::SND_STR_MUSIC;
                }
                if (_binkStructPtr->unknownParam07[0] == param_1) {
                    _binkStructPtr->unknown01_zero[0] = 0;
                    _binkStructPtr->unknown02_zero[0] = 0;
                }
                if ((_binkStructPtr->binkObjPtrArray[0] != (HBINK)0x0)
                    && (_binkStructPtr->unknownParam07[0] == param_1)) {
                    _waitingForFrame = BinkWait(_binkStructPtr->binkObjPtrArray[0]);
                    if (!_waitingForFrame) {
                        BinkDoFrame(_binkStructPtr->binkObjPtrArray[0]);
                        _binkObjPtr = _binkStructPtr->binkObjPtrArray[0];
                        if ((_binkObjPtr->frameNum == _binkObjPtr->frames)
                            && (_binkStructPtr->unknownParam03[0] == 0)) {
                            if (_binkStructPtr->soundStreamIndex[0] == Audio::MSS::enums::SND_STR_MUSIC) {
                                if (param_1 != 2) {
                                    _binkStructPtr->unknown01_zero[0] = 1;
                                    MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                                        this)(_binkObjIndex);
                                    goto LAB_004091dd;
                                }
                            } else if (param_1 != 2)
                                goto LAB_00409075;
                            _binkStructPtr->unknown02_zero[0] = 1;
                        } else {
                            BinkNextFrame(_binkObjPtr);
                        }
                    LAB_00409075:
                        _binkStructPtr->frameReadyToDisplay[0] = TRUE;
                    }
                    _menuBorderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    _menuBorderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    _menu = DAT_MenuHandlerState::instance.currentMenu;
                    if (param_1 == 2) {
                        (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                            = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                        _menu->yPosition = _menuBorderHeight;
                        DAT_MenuHandlerState::instance.y = _menuBorderHeight;
                        DAT_MenuHandlerState::instance.x = _menuBorderWidth;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox,
                            DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                            DAT_WindowAndDirectDraw::instance.resolutionY,
                            (ushort)((int)(COL_BLACK::instance.shortValue)));
                    }
                    if (_binkStructPtr->frameReadyToDisplay[0]) {
                        if (_binkStructPtr.unknownParam04[0] == 0) {
                            /*
                              Stack pointer also broken here. Lock requires 5 inputs.      Singature Overwrite
                             */
                            _hResultLock = (*(
                                DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu)
                                    ->vTable->Lock)(
                                DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu,
                                (tagRECT*)0x0, &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104,
                                1, (void*)0x0);
                            while (_hResultLock == -0x7789fe3e) {
                                /*
                                  Singature Overwrite
                                 */
                                _hResultRestore
                                    = (*(DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu)
                                            ->vTable->Restore)(
                                        DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu);
                                if (_hResultRestore)
                                    goto LAB_004091dd;
                                /*
                                  Signature Overwrite
                                 */
                                _hResultLock
                                    = (*(DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu)
                                            ->vTable->Lock)(
                                        DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu,
                                        (tagRECT*)0x0,
                                        &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104, 1,
                                        (void*)0x0);
                            }
                            BinkCopyToBuffer(_binkStructPtr->binkObjPtrArray[0],
                                DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.lpSurface,
                                DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.pitchOrLinearSize
                                    .lPitch,
                                _binkStructPtr->binkObjPtrArray[0]->height, _binkStructPtr->xPos[0],
                                _binkStructPtr->yPos[0],
                                this->screenMenuSurfaceType_0x5c | Rendering::Bink::UBF_BINKCOPYALL);
                            _surfacePointer
                                = DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu;
                        } else {
                            /*
                              Signature Overwrite
                             */
                            _hResultLock2
                                = (*(DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame)
                                        ->vTable->Lock)(
                                    DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame,
                                    (tagRECT*)0x0, &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame, 1,
                                    (void*)0x0);
                            while (_hResultLock2 == -0x7789fe3e) {
                                /*
                                  Signature Overwrite
                                 */
                                _hResultRestore
                                    = (*(DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame)
                                            ->vTable->Restore)(
                                        DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame);
                                if (_hResultRestore)
                                    goto LAB_004091dd;
                                /*
                                  Singature Overwrite
                                 */
                                _hResultLock2
                                    = (*(DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame)
                                            ->vTable->Lock)(
                                        DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame,
                                        (tagRECT*)0x0, &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame,
                                        1, (void*)0x0);
                            }
                            /*
                              Bink flag seems plausible. -TheRedDaemon
                             */
                            BinkCopyToBuffer(_binkStructPtr->binkObjPtrArray[0],
                                DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.lpSurface,
                                DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.pitchOrLinearSize.lPitch,
                                _binkStructPtr->binkObjPtrArray[0]->height, _binkStructPtr->xPos[0],
                                _binkStructPtr->yPos[0],
                                this->mapGameSurfaceType | Rendering::Bink::UBF_BINKCOPYALL);
                            _surfacePointer
                                = DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame;
                        }
                        (*_surfacePointer->vTable->Unlock)(_surfacePointer, (tagRECT*)0x0);
                    }
                }
            LAB_004091dd:
                _binkObjIndex = _binkObjIndex + 1;
                _binkStructPtr = (BinkControlClass*)(_binkStructPtr->soundStreamIndex + 1);
                if (1 < _binkObjIndex) {}
            } while (true);
        }

    }
}
}
