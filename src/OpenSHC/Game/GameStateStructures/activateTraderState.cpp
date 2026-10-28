#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004586D0
    void GameStateStructures::activateTraderState()
    {
        this->mapAndTime.traderState = 2;
        this->mapAndTime.traderWeekCounter = 0;
    }

}
}
