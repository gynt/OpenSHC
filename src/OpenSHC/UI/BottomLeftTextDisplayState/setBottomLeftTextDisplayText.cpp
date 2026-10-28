#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::TextMessageBLLookupStructTypeEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F4E00
    void BottomLeftTextDisplayState::setBottomLeftTextDisplayText(int messageTypeUnk, int textGroupIndex,
        int textNumInGroup, int param_4Raw, int importanceUnk, int displayDurationUnk)
    {
            // main retyped this parameter to int (7e205a01); the union view is rebuilt locally
            TextMessageBLLookupStructUnion param_4;
            *(int*)&param_4 = param_4Raw;
        int iVar1;
        TextMessageBLLookupStructTypeEnumInt TVar2;
        int iVar3;
        TextMessageBLLookupStructTypeEnumInt TVar4;
        TVar4 = ((TextMessageBLLookupStructTypeEnum)0);
        if (messageTypeUnk == 0) {
            /*
              basically clear!
             */
            this->displayedMessageType = 0;
            return; // 0x4F4E12: ret 0x18
        }
        if (this->displayedMessageType != 0) {
            if (importanceUnk < this->currentlyDisplayedTextImportance)
                return;
            if (((textGroupIndex == this->currentlyDisplayedTextGroupIndex_0x4)
                    && (textNumInGroup == this->currentlyDisplayedTextNumInGroup_0x8))
                && (param_4.buildingType == this->messageExtraParam.buildingType))
                goto LAB_004f4e46;
        }
        this->countdown = 0;
    LAB_004f4e46:
        this->displayedMessageType = messageTypeUnk;
        if (textGroupIndex == -1) {
            if (messageTypeUnk == 2) {
                TVar4 = OpenSHC::UI::Enums::TMBLLSTE_BUILDING_TEXT;
            }
            if (DAT_TroopValueDefinedData::instance.TextMessageLookupTable[0].messageType
                != ((TextMessageBLLookupStructTypeEnum)0xffffffff)) {
                iVar1 = 0;
                TVar2 = DAT_TroopValueDefinedData::instance.TextMessageLookupTable[0].messageType;
                iVar3 = 0;
                do {
                    if ((TVar4 == TVar2)
                        && (param_4.buildingType
                            == *(MappersEnum*)((int)&DAT_TroopValueDefinedData::instance.TextMessageLookupTable[0]
                                                   .associatedType
                                + iVar1))) {
                        this->currentlyDisplayedTextGroupIndex_0x4
                            = DAT_TroopValueDefinedData::instance.TextMessageLookupTable[iVar3].textGroupIndex;
                        this->currentlyDisplayedTextNumInGroup_0x8
                            = DAT_TroopValueDefinedData::instance.TextMessageLookupTable[iVar3].textIndexInGroup;
                        break;
                    }
                    iVar1 = iVar3 * 0x10 + 0x10;
                    TVar2 = DAT_TroopValueDefinedData::instance.TextMessageLookupTable[iVar3 + 1].messageType;
                    iVar3 = iVar3 + 1;
                } while (TVar2 != ((TextMessageBLLookupStructTypeEnum)0xffffffff));
            }
        } else {
            this->currentlyDisplayedTextGroupIndex_0x4 = textGroupIndex;
            this->currentlyDisplayedTextNumInGroup_0x8 = textNumInGroup;
            if (((messageTypeUnk == 1) && (textGroupIndex == 0x4d)) && (textNumInGroup == 1)) {
                /*
                  "Not enough workers available to run this building."
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "placement_warning1.wav");
            }
        }
        this->messageExtraParam = param_4;
        this->currentlyDisplayedTextImportance = importanceUnk;
        if (displayDurationUnk == -1) {
            this->textMessageDurationMs = 0;
            return; // 0x4F4EE1: no time write
        }
        this->textMessageDurationMs = displayDurationUnk;
        this->textMessageTime = timeGetTime();
    }

}
}
