#include "../TribesState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // g_tribeScanIndex (undefined4) is the loop counter, compared signed (jl at 0x52B995). AI tribes in
        // GM_SOLITARY use the switch at 0x52B8F6, all others only dispatch the four animal types (0x52B92A).
        // FUNCTION: STRONGHOLDCRUSADER 0x0052B860
        void TribesState::updateTribes()
        {
            uint const tickSlot = DAT_GameCore::instance.mapTimeInTicks & 0x1f;
            DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation--;
            for (g_tribeScanIndex::instance = 1; (int)g_tribeScanIndex::instance < 0x4e2;
                 g_tribeScanIndex::instance++) {
                if (this->tribes[g_tribeScanIndex::instance].tribeState != 2) {
                    continue;
                }
                if (this->tribes[g_tribeScanIndex::instance].countdown2 > 0) {
                    this->tribes[g_tribeScanIndex::instance].countdown2--;
                }
                if ((g_tribeScanIndex::instance & 0x1f) == tickSlot) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::computeTribePercentages, this)(
                        g_tribeScanIndex::instance);
                }
                if (DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[this->tribes[g_tribeScanIndex::instance].owner]
                        == -1
                    && DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    switch (this->tribes[g_tribeScanIndex::instance].tribeType) {
                    case OpenSHC::AI::Tribes::AITT_TUNNELERS:
                    case OpenSHC::AI::Tribes::AITT_ARCHERS:
                    case OpenSHC::AI::Tribes::AITT_LADDERMEN:
                    case OpenSHC::AI::Tribes::AITT_SPEARMEN:
                    case OpenSHC::AI::Tribes::AITT_PIKEMEN:
                    case OpenSHC::AI::Tribes::AITT_CROSSBOWMEN:
                    case OpenSHC::AI::Tribes::AITT_SWORDSMEN:
                    case OpenSHC::AI::Tribes::AITT_MACEMEN:
                    case OpenSHC::AI::Tribes::AITT_KNIGHTS:
                    case OpenSHC::AI::Tribes::AITT_ENGINEERS:
                    case OpenSHC::AI::Tribes::AITT_MONKS:
                    case OpenSHC::AI::Tribes::AITT_BATTERING_RAMS:
                    case OpenSHC::AI::Tribes::AITT_SIEGE_TOWERS:
                    case OpenSHC::AI::Tribes::AITT_PORTABLE_SHIELDS:
                    case OpenSHC::AI::Tribes::AITT_CATAPULTS:
                    case OpenSHC::AI::Tribes::AITT_TREBUCHETS:
                    case OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS:
                    case OpenSHC::AI::Tribes::AITT_ARAB_ARCHERS:
                    case OpenSHC::AI::Tribes::AITT_SLAVES:
                    case OpenSHC::AI::Tribes::AITT_SLINGERS:
                    case OpenSHC::AI::Tribes::AITT_ASSASSINS:
                    case OpenSHC::AI::Tribes::AITT_HORSE_ARCHERS:
                    case OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMEN:
                    case OpenSHC::AI::Tribes::AITT_FIRE_THROWERS:
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::updateTribeBehaviorBasedOnBehaviorType,
                            DAT_TroopValueState::ptr)(g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_DEER:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::processDeerMoving, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_LIONS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateLionWolfTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_RABBITS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateRabbitTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_CAMELS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateCamelTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case 0x11:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::markTribeAsAnimalTribe, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case 0x12:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::markTribeAsAnimalTribe, this)(
                            g_tribeScanIndex::instance);
                        break;
                    default:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateTribeCombatStanceBehavior,
                            this)(g_tribeScanIndex::instance);
                        break;
                    }
                } else {
                    switch (this->tribes[g_tribeScanIndex::instance].tribeType) {
                    case OpenSHC::AI::Tribes::AITT_DEER:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::processDeerMoving, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_LIONS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateLionWolfTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_RABBITS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateRabbitTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    case OpenSHC::AI::Tribes::AITT_CAMELS:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateCamelTribeBehavior, this)(
                            g_tribeScanIndex::instance);
                        break;
                    default:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateTribeCombatStanceBehavior,
                            this)(g_tribeScanIndex::instance);
                        break;
                    }
                }
                if (this->tribes[g_tribeScanIndex::instance].countdown != 0) {
                    this->tribes[g_tribeScanIndex::instance].countdown--;
                }
            }
        }

    }
}
}
