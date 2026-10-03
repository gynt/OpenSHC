#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BEA90
        void AIMessageQueue::playBikVideoFromPlayer(int playerIndex, int aiType, int messageType)
        {
            char* _messageText;
            int _negativePlayerIndex;
            char* _messageSfxFile;
            char** _messageVfxFile;
            if ((aiType - 1U < 0x10) && (messageType - 1U < 0x21)) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)("", "",
                    (char*)((int)(DAT_MissionAestheticsDefinedData::instance.field92_0x170[aiType + -0x11])),
                    playerIndex);
                _messageSfxFile
                    = (char*)
                          DAT_MissionAestheticsDefinedData::instance.field92_0x170[aiType + messageType * 0x11 + -0xc];
                _messageVfxFile
                    = (&DAT_MissionAestheticsDefinedData::instance.field644_0xa20)[aiType + messageType * 0x11];
                _negativePlayerIndex = -playerIndex;
                _messageText = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HOT_KEYS, messageType + -0x22 + aiType * 0x22);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)(
                    _messageText, (char*)((int)(_messageVfxFile)), _messageSfxFile, _negativePlayerIndex);
            }
        }

    }
}
}
