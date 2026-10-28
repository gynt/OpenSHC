#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // g_tribeScanIndex (undefined4) is the loop counter and compared signed (jl at 0x527434); the logical state
        // is tested signed (movsx at 0x5273A1): 1, 2 and 4 are valid. An empty tribe is kept while
        // emptyKeepAliveUntilTick != 0 and mapTimeInTicks <= it (signed jl at 0x527410).
        // FUNCTION: STRONGHOLDCRUSADER 0x00527330
        void TribesState::updateTribeUnitAssignments()
        {
            this->activeTribeCount = 0;
            this->highestActiveTribeID = 1;
            for (g_tribeScanIndex::instance = 1; (int)g_tribeScanIndex::instance < 0x4e2;
                 g_tribeScanIndex::instance++) {
                short const tribeState = this->tribes[g_tribeScanIndex::instance].tribeState;
                int iterationStep = 0;
                if (tribeState == 0) {
                    continue;
                }
                if (tribeState != 3) {
                    short const size = this->tribes[g_tribeScanIndex::instance].size;
                    if (size > 0) {
                        int validUnitCount = 0;
                        while (iterationStep < size) {
                            int const unitID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(
                                g_tribeScanIndex::instance, iterationStep);
                            int const logicalState = DAT_UnitsState::instance.units[unitID].logicalState;
                            ++iterationStep;
                            if (logicalState > 0 && (logicalState <= 2 || logicalState == ULS_TRANSITIONING)
                                && DAT_UnitsState::instance.units[unitID].dying == 0
                                && DAT_UnitsState::instance.units[unitID].tribeID == (int)g_tribeScanIndex::instance) {
                                ++validUnitCount;
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                    unitID, g_tribeScanIndex::instance);
                            }
                        }
                        if (validUnitCount != 0) {
                            ++this->activeTribeCount;
                            this->highestActiveTribeID = g_tribeScanIndex::instance;
                            continue;
                        }
                    } else {
                        short const keepAliveUntilTick
                            = this->tribes[g_tribeScanIndex::instance].emptyKeepAliveUntilTick;
                        if (keepAliveUntilTick != 0 && keepAliveUntilTick >= (int)DAT_GameCore::instance.mapTimeInTicks
                            && keepAliveUntilTick != 0) {
                            continue;
                        }
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearTribe, this)(g_tribeScanIndex::instance);
            }
        }

    }
}
}
