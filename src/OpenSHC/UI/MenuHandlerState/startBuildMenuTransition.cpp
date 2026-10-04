#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    using Audio::SFX::SoundEffectID;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4C80
    void MenuHandlerState::startBuildMenuTransition(int transitionDuration)
    {
        this->buildMenuTransitionStartTime_0x30 = timeGetTime();
        this->buildMenuTransitionDuration_0x34 = transitionDuration;
        this->isBuildMenuTransitioning_0x18 = TRUE;
        this->buildMenuTransitionProgress_0x38 = 0;
        this->buildMenuTransitionDirection_0x2c = (uint)(this->buildMenuTransitionDirection_0x2c < 0) * 2 + -1;
        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
            (Audio::SFX::SoundEffectID)(Audio::SFX::SEID_BURNING_MAN_SCREAM2
                | Audio::SFX::SEID_WOOD_SAW));
    }

}
}
