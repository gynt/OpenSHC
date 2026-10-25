#include "../SoundOptions.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

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
                /*
                  the original tests param_1 with a `sub eax, K; je` chain (0x4928d5),
                  MSVC's sparse switch, whose arms are written in the reverse of the test
                  order, and each arm writes its field back at the shared label
                 */
                switch (param_1) {
                case 2:
                    if (DAT_MenuTextInputState::instance.pendingStreamVolume3 != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(3, (int)(*currentValue));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(4, (int)(*currentValue));
                    }
                    DAT_MenuTextInputState::instance.pendingStreamVolume3 = *currentValue;
                    return;
                case 1:
                    if (DAT_MenuTextInputState::instance.pendingStreamVolume1 != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(1, (int)(*currentValue));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(2, (int)(*currentValue));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(-1, (int)(*currentValue));
                    }
                    DAT_MenuTextInputState::instance.pendingStreamVolume1 = *currentValue;
                    return;
                case 0:
                    if (DAT_MenuTextInputState::instance.pendingStreamVolume0 != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(0, (int)(*currentValue));
                    }
                    DAT_MenuTextInputState::instance.pendingStreamVolume0 = *currentValue;
                    return;
                default:
                    return;
                }
            case 4:
                break;
            default:
                return;
            }
            /*
              the read-back dispatch is the same sparse switch (0x49297f), shared between
              `case 1` and `case 4`
             */
            switch (param_1) {
            case 2:
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume3;
                break;
            case 1:
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume1;
                break;
            case 0:
                *currentValue = DAT_MenuTextInputState::instance.pendingStreamVolume0;
                break;
            default:
                break;
            }
        }

    }
}
}
