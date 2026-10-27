#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The rally point copy covers 10 entries (index 9 = bytes 0x25C..0x25F of Tribe, right after the declared
        // rallyPointArray[9][2]; machine code 0x522E73..0x522ECA copies x of entries 0..9, then y of entries 0..9).
        // The first argument is never read.
        // FUNCTION: STRONGHOLDCRUSADER 0x00522DD0
        void TribesState::importStoredInfoFromSlot0(undefined4 unused1, int tribeID)
        {
            if (this->tribeCopiedToSlot0 != 0) {
                this->tribes[tribeID].attackRetargetDelay = this->tribes[0].attackRetargetDelay;
                this->tribes[tribeID].attackTargetUnitID = this->tribes[0].attackTargetUnitID;
                this->tribes[tribeID].attackTargetUnitUID = this->tribes[0].attackTargetUnitUID;
                this->tribes[tribeID].targetUnitTile = this->tribes[0].targetUnitTile;
                this->tribes[tribeID].someTile2 = this->tribes[0].someTile2;
                this->tribes[tribeID].currentRallyPointIndex = this->tribes[0].currentRallyPointIndex;
                this->tribes[tribeID].rallyPointCount = this->tribes[0].rallyPointCount;
                this->tribes[tribeID].rallyMode = this->tribes[0].rallyMode;
                this->tribes[tribeID].unitStance = this->tribes[0].unitStance;
                for (int coord = 0; coord < 2; ++coord) {
                    for (int i = 0; i < 10; ++i) {
                        this->tribes[tribeID].rallyPointArray[i][coord] = this->tribes[0].rallyPointArray[i][coord];
                    }
                }
                return;
            }
            this->tribes[tribeID].unitStance = this->tribes[0].unitStance;
        }

    }
}
}
