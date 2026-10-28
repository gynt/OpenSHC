#include "../SoundOptions.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492890
        void SoundOptions::MenuItemActionHandler_SoundOptions_VolumeSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 100;
                break;
            case 2:
            case 3:
                if (param_1 == 0) {
                    if (DAT_MenuTextInputState::instance.musicVolume != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume,
                            DAT_SoundSystemState::ptr)(0, (int)((int)(*currentValue)));
                    }
                    DAT_MenuTextInputState::instance.musicVolume = *currentValue;
                    return; // 0x49297E ret
                }
                if (param_1 != 1) {
                    if (param_1 != 2) {
                        return; // 0x4928E3 jne ret
                    }
                    if (DAT_MenuTextInputState::instance.speechVolume != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume,
                            DAT_SoundSystemState::ptr)(3, (int)((int)(*currentValue)));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume,
                            DAT_SoundSystemState::ptr)(4, (int)((int)(*currentValue)));
                    }
                    DAT_MenuTextInputState::instance.speechVolume = *currentValue;
                    return; // 0x492917 ret
                }
                if (DAT_MenuTextInputState::instance.sfxVolume != *currentValue) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume, DAT_SoundSystemState::ptr)(
                        1, (int)((int)(*currentValue)));
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume, DAT_SoundSystemState::ptr)(
                        2, (int)((int)(*currentValue)));
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setStreamOrSfxVolume, DAT_SoundSystemState::ptr)(
                        -1, (int)((int)(*currentValue)));
                }
                DAT_MenuTextInputState::instance.sfxVolume = *currentValue;
                return;
            case 4:
                break;
            default:
                return;
            }
            if (param_1 == 0) {
                *currentValue = DAT_MenuTextInputState::instance.musicVolume;
            }
            if (param_1 == 1) {
                *currentValue = DAT_MenuTextInputState::instance.sfxVolume;
            }
            if (param_1 == 2) {
                *currentValue = DAT_MenuTextInputState::instance.speechVolume;
            }
        }

    }
}
}
