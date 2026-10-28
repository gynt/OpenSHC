#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433560
    void Helpers::TriggerScribeReaction(int taxesSettingUnk)
    {
        if (DAT_GameCore::instance.scribeReactionType == 0) {
            DAT_GameCore::instance.scribeReactionType = taxesSettingUnk;
            DAT_GameCore::instance.scribeAnimationPhase = TRUE;
            DAT_GameCore::instance.scribeAnimLastTickMs = timeGetTime();
            DAT_GameCore::instance.scribeAnimationFrame2 = 0;
        }
    }

}
}
