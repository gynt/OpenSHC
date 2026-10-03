#include "../../Audio.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Audio {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044C400
    int SFX::ComputeCurrentPlayerRanking()
    {
        int iVar1;
        iVar1 = MACRO_CALL(OpenSHC::Audio::SFX_Func::ComputePlayerRanking)(
            DAT_GameSynchronyState::instance.currentPlayerSlotID);
        return iVar1;
    }

}
}
