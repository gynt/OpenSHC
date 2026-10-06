#include "../AICState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD070
    BOOLEnum AICState::checkTribeActivityPercentages(int tribeID, BOOLEnum ignoreShooting, BOOLEnum includeMoving)
    {
        if (((!includeMoving) || (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk < 11))
            && ((DAT_TribesState::instance.tribes[tribeID].percentageShootingUnk < 11 || (ignoreShooting == TRUE)))) {
            return (uint)(10 < DAT_TribesState::instance.tribes[tribeID].percentageAttackingUnk);
        }
        return TRUE;
    }

}
}
