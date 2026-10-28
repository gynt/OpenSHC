#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/g_tribeUnitSearchIndex.hpp"
#include "OpenSHC/Globals/g_tribeUnitSearchWord.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The cursor globals are undefined4 in the header but compared signed (jge/jl at 0x52244E, 0x52246B).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522410
        int TribesState::getSpecificUnitFromTribe(int tribeID, int iterationStep)
        {
            if (iterationStep == 0) {
                g_tribeUnitSearchWord::instance = this->tribes[tribeID].firstOccupiedMaskWord;
                g_tribeUnitSearchIndex::instance = 0;
            }
            for (int wordIndex = g_tribeUnitSearchWord::instance; wordIndex < 200; ++wordIndex) {
                if (this->tribes[tribeID].unitSelectionBitMasked[wordIndex] != 0) {
                    for (int bitIndex = g_tribeUnitSearchIndex::instance; bitIndex < 16; ++bitIndex) {
                        if ((this->tribes[tribeID].unitSelectionBitMasked[wordIndex] & (1 << bitIndex)) != 0) {
                            g_tribeUnitSearchIndex::instance = bitIndex + 1;
                            if ((int)g_tribeUnitSearchIndex::instance == 16) {
                                g_tribeUnitSearchWord::instance = wordIndex + 1;
                                g_tribeUnitSearchIndex::instance = 0;
                            } else {
                                g_tribeUnitSearchWord::instance = wordIndex;
                            }
                            return wordIndex * 16 + bitIndex;
                        }
                    }
                }
                g_tribeUnitSearchIndex::instance = 0;
            }
            return 0;
        }

    }
}
}
