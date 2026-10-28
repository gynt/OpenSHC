#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // step is not range-checked (no compare in the machine code).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522C50
        void TribesState::addRallyPoint(int section1016ID, int destinationX, int destinationY, int step)
        {
            this->tribes[section1016ID].rallyPointArray[step][0] = (short)destinationX;
            this->tribes[section1016ID].rallyPointArray[step][1] = (short)destinationY;
            this->tribes[section1016ID].rallyPointCount = (short)(step + 1);
        }

    }
}
}
