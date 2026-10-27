#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BD10
        void TroopValueState::exitSiegeEquipmentForWave(int wave)
        {
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState == 0
                    || DAT_TribesState::instance.tribes[tribeID].attackWave != wave) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].tribeType != OpenSHC::AI::Tribes::AITT_BATTERING_RAMS
                    && DAT_TribesState::instance.tribes[tribeID].tribeType != OpenSHC::AI::Tribes::AITT_SIEGE_TOWERS
                    && DAT_TribesState::instance.tribes[tribeID].tribeType != OpenSHC::AI::Tribes::AITT_PORTABLE_SHIELDS
                    && DAT_TribesState::instance.tribes[tribeID].tribeType != OpenSHC::AI::Tribes::AITT_CATAPULTS
                    && DAT_TribesState::instance.tribes[tribeID].tribeType != OpenSHC::AI::Tribes::AITT_TREBUCHETS
                    && DAT_TribesState::instance.tribes[tribeID].tribeType
                        != OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS) {
                    continue;
                }
                for (int i = 0; i < DAT_TribesState::instance.tribes[tribeID].size;) {
                    int const unitID = MACRO_CALL_MEMBER(
                        TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribeID, i);
                    i++;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                            tribeID, UIT_EXIT_SIEGE_EQUIPMENT, unitID, DAT_UnitsState::instance.units[unitID].uid, 0);
                        DAT_UnitsState::instance.units[unitID].state.generic = States::US_DISAPPEAR;
                    }
                }
            }
        }

    }
}
}
