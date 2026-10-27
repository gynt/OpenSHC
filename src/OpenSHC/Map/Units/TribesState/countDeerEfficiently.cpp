#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005236A0
        void TribesState::countDeerEfficiently()
        {
            DAT_GameState::instance.mapAndTime.aliveDeerCount = 0;
            for (int unitID = 1; unitID < 2500; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].unitType == UT_ANTELOPESHDEER) {
                    ++DAT_GameState::instance.mapAndTime.aliveDeerCount;
                }
            }
        }

    }
}
}
