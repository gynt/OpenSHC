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
                /*
                  the original tests param_1 with a `sub eax, K; je` chain (0x4928d5),
                  MSVC's sparse switch, whose arms are written in the reverse of the test
                  order, and each arm writes its field back at the shared label
                 */
                switch (param_1) {
                case 2:
                    if (DAT_MenuTextInputState::instance.field22_0x4c != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(3, (int)((int)(*currentValue)));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(4, (int)((int)(*currentValue)));
                    }
                    DAT_MenuTextInputState::instance.field22_0x4c = *currentValue;
                    return;
                case 1:
                    if (DAT_MenuTextInputState::instance.field21_0x48 != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(1, (int)((int)(*currentValue)));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(2, (int)((int)(*currentValue)));
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(-1, (int)((int)(*currentValue)));
                    }
                    DAT_MenuTextInputState::instance.field21_0x48 = *currentValue;
                    return;
                case 0:
                    if (DAT_MenuTextInputState::instance.field20_0x44 != *currentValue) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setVolumeUnk,
                            DAT_SoundSystemState::ptr)(0, (int)((int)(*currentValue)));
                    }
                    DAT_MenuTextInputState::instance.field20_0x44 = *currentValue;
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
                *currentValue = DAT_MenuTextInputState::instance.field22_0x4c;
                break;
            case 1:
                *currentValue = DAT_MenuTextInputState::instance.field21_0x48;
                break;
            case 0:
                *currentValue = DAT_MenuTextInputState::instance.field20_0x44;
                break;
            default:
                break;
            }
        }

    }
}
}
