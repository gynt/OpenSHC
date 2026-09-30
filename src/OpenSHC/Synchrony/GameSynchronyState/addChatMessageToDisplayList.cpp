#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047F6A0
    void GameSynchronyState::addChatMessageToDisplayList(int subjectPlayerID, int objectPlayerID)
    {
        DWORD DVar1;
        char (*src)[250];
        char (*destination)[250];
        this->DAT_ChatMessageArrayIndex = this->DAT_ChatMessageArrayIndex + 1;
        if (20 < this->DAT_ChatMessageArrayIndex) {
            this->DAT_ChatMessageArrayIndex = 0;
        }
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].subjectPlayer = subjectPlayerID;
        DVar1 = timeGetTime();
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].time = DVar1;
        /*
          such a weird way to write: DAT_01a22de8
         */
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].flag = 1;
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].objectPlayer = objectPlayerID;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
            (void*)((int)(this->receivedChatMessage)),
            (void*)((int)(this->DAT_ChatMessageArray + this->DAT_ChatMessageArrayIndex)));
        if (subjectPlayerID == 0) {
            destination = this->DAT_ChatMessageSubjectPlayerNameArray + this->DAT_ChatMessageArrayIndex;
            /*
              "Host"   added by script: "Host"
             */
            src = (char (*)[250])MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)((OpenSHC::DE::SHCDE::eTextSections)76, 7);
        } else {
            destination = this->DAT_ChatMessageSubjectPlayerNameArray + this->DAT_ChatMessageArrayIndex;
            src = this->DAT_PlayerNames + subjectPlayerID;
        }
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            250, (void*)((int)(src)), (void*)((int)(destination)));
        if (objectPlayerID != 0) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
                (void*)((int)(this->DAT_PlayerNames + objectPlayerID)),
                (void*)((int)(this->DAT_ChatMessageObjectPlayerNameArray + this->DAT_ChatMessageArrayIndex)));
        }
        this->field237_0x1072f0 = 0;
    }

}
}
