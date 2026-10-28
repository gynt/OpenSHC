#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004586F0
    void GameStateStructures::resetTraderState()
    {
        this->mapAndTime.traderState = 0;
        this->mapAndTime.traderWeekCounter = 0;
        return;
    }

}
}
