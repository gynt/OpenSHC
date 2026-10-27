#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/Globals/CreditsRelatedStructure2_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DABF0
        void AppendCreditsSoundStreamCommand(int command, SHC_SoundStream soundStream)
        {
            if ((int)DAT_CreditsScriptCommandCount::instance < 288) {
                CreditsRelatedStructure2_ARRAY_00eb9b68::instance[DAT_CreditsScriptCommandCount::instance].commandType = command;
                CreditsRelatedStructure2_ARRAY_00eb9b68::instance[DAT_CreditsScriptCommandCount::instance].arg = soundStream;
                DAT_CreditsScriptCommandCount::instance += 1;
            }
        }

    }
}
}
