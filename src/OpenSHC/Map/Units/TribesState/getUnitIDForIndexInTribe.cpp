#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522390
        int TribesState::getUnitIDForIndexInTribe(int tribeID, int unitSelectionIndex)
        {
            int membersSeen = 0;
            int wordIndex = 0;
            if (this->tribes[tribeID].tribeState == 2 && unitSelectionIndex < this->tribes[tribeID].size) {
                for (; wordIndex < 200; ++wordIndex) {
                    if (this->tribes[tribeID].unitSelectionBitMasked[wordIndex] != 0) {
                        for (int bitIndex = 0; bitIndex < 16; ++bitIndex) {
                            if ((this->tribes[tribeID].unitSelectionBitMasked[wordIndex] & (1 << bitIndex)) != 0) {
                                if (membersSeen == unitSelectionIndex) {
                                    return wordIndex * 16 + bitIndex;
                                }
                                ++membersSeen;
                            }
                        }
                    }
                }
            }
            return 0;
        }

    }
}
}
