#include "OpenSHC/Globals/unitValueKilledByCurrentPlayer.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044aa70
    void addUnitValueKilledByCurrentPlayer(int value)
    {
        if (value > 0) {
            unitValueKilledByCurrentPlayer::instance += value;
        }
    }

} // namespace Game
} // namespace OpenSHC
