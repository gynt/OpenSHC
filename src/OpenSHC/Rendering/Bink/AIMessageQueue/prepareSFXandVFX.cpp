#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BE8A0
        void AIMessageQueue::prepareSFXandVFX(
            char* messageText, char* messageVfxFile, char* messageSfxFile, int param_4)
        {
            char* _charRunPtr1;
            char* _charRunPtr2;
            char _char;
            if (messageText != (char*)0x0) {
                if (this->messagePlaying_0x0 == FALSE) {
                    this->currentMessageText_0x8 = messageText;
                    this->currentMessageUnknownValue2_0xd4 = param_4;
                    this->currentMessageUnknownValue_0x4 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                        messageVfxFile, messageSfxFile);
                } else if (this->storedMessages_0x924 != 10) {
                    this->savedMessageUnknownValue_0x104[this->storedMessages_0x924] = 1;
                    this->savedMessageTextPtr_0xdc[this->storedMessages_0x924] = messageText;
                    _charRunPtr1 = this->savedMessageVfxFile_0x12c[this->storedMessages_0x924];
                    do {
                        _char = *messageVfxFile;
                        *_charRunPtr1 = _char;
                        messageVfxFile = messageVfxFile + 1;
                        _charRunPtr1 = _charRunPtr1 + 1;
                    } while (_char != '\0');
                    _charRunPtr2 = this->savedMessageSfxFile_0x514[this->storedMessages_0x924];
                    do {
                        _char = *messageSfxFile;
                        *_charRunPtr2 = _char;
                        messageSfxFile = messageSfxFile + 1;
                        _charRunPtr2 = _charRunPtr2 + 1;
                    } while (_char != '\0');
                    this->savedMessageUnknownValue2_0x8fc[this->storedMessages_0x924] = param_4;
                    this->storedMessages_0x924 = this->storedMessages_0x924 + 1;
                }
            }
        }

    }
}
}
