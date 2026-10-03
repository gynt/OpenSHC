#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE7E0
        void AIMessageQueue::playEventVideoBik(char* eventText, char* eventVideoBik, char* eventWavFile)
        {
            char cVar1;
            char (*pacVar2)[100];
            if (eventText != (char*)0x0) {
                if (this->messagePlaying_0x0 == FALSE) {
                    this->currentMessageText_0x8 = eventText;
                    this->currentMessageUnknownValue_0x4 = 1;
                    this->currentMessageUnknownValue2_0xd4 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                        eventVideoBik, eventWavFile);
                } else if (this->storedMessages_0x924 != 10) {
                    this->savedMessageUnknownValue_0x104[this->storedMessages_0x924] = 1;
                    this->savedMessageTextPtr_0xdc[this->storedMessages_0x924] = eventText;
                    pacVar2 = this->savedMessageVfxFile_0x12c + this->storedMessages_0x924;
                    do {
                        cVar1 = *eventVideoBik;
                        (*pacVar2)[0] = cVar1;
                        eventVideoBik = eventVideoBik + 1;
                        pacVar2 = (char (*)[100])(*pacVar2 + 1);
                    } while (cVar1 != '\0');
                    pacVar2 = this->savedMessageSfxFile_0x514 + this->storedMessages_0x924;
                    do {
                        cVar1 = *eventWavFile;
                        (*pacVar2)[0] = cVar1;
                        eventWavFile = eventWavFile + 1;
                        pacVar2 = (char (*)[100])(*pacVar2 + 1);
                    } while (cVar1 != '\0');
                    this->savedMessageUnknownValue2_0x8fc[this->storedMessages_0x924] = 0;
                    this->storedMessages_0x924 = this->storedMessages_0x924 + 1;
                }
            }
        }

    }
}
}
