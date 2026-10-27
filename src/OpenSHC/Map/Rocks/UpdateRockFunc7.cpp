#include "../Rocks.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2AE0
    void Rocks::setCurrentRockGfx0x1F1() { DAT_LandscapeState::instance.rocks[DAT_CurrentRockID::instance].gfx = 0x1f1; }

}
}
