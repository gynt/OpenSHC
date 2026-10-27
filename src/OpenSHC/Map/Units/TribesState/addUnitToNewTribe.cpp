#include "../TribesState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // UT_HOPSFARMER (12) is mapped to AITT_MONKS (12) - the original compares with 0xC (0x52561F); likely an
        // original source slip (UT_E_MONK intended), kept as is. The tribeType chain is an if/else chain in the
        // original (0x525535..0x5256FC), not a jump table.
        // FUNCTION: STRONGHOLDCRUSADER 0x005254C0
        BOOLEnum TribesState::addUnitToNewTribe(uint unitID)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return FALSE;
            }
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int currentTribeID;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
                && ((currentTribeID = DAT_UnitsState::instance.units[unitID].tribeID) <= 0
                    || this->tribes[currentTribeID].uid != DAT_UnitsState::instance.units[unitID].tribeUID
                    || this->tribes[currentTribeID].tribeState == 0)) {
                int const newTribeID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(owner, 0);
                if (newTribeID > 0) {
                    UnitTypeShort const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (unitType == UT_E_ARCHER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
                    }
                    else if (unitType == UT_E_XBOW) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_CROSSBOWMEN;
                    }
                    else if (unitType == UT_E_SPEAR) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_SPEARMEN;
                    }
                    else if (unitType == UT_E_PIKE) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_PIKEMEN;
                    }
                    else if (unitType == UT_E_MACE) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
                    }
                    else if (unitType == UT_E_SWORD) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
                    }
                    else if (unitType == UT_E_KNIGHT) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
                    }
                    else if (unitType == UT_E_LADDER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_LADDERMEN;
                    }
                    else if (unitType == UT_E_ENGINEER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                    }
                    else if (unitType == UT_HOPSFARMER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_MONKS;
                    }
                    else if (unitType == UT_TUNNELER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;
                    }
                    else if (unitType == UT_A_ARCHER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ARCHERS;
                    }
                    else if (unitType == UT_A_SLAVE) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_SLAVES;
                    }
                    else if (unitType == UT_A_SLINGER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_SLINGERS;
                    }
                    else if (unitType == UT_A_ASSASSIN) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ASSASSINS;
                    }
                    else if (unitType == UT_A_HARCHER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_HORSE_ARCHERS;
                    }
                    else if (unitType == UT_A_SWORDSMAN) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMEN;
                    }
                    else if (unitType == UT_A_FIRETHROWER) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_FIRE_THROWERS;
                    }
                    else if (unitType == UT_S_FBALLISTA) {
                        this->tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS;
                    }
                    this->tribes[newTribeID].nearbyTileOffsetStartIndex = 1;
                    this->tribes[newTribeID].attackWave
                        = (short)DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot;
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_ENGINEER) {
                        if (DAT_UnitsState::instance.units[unitID].state.generic == States::US_STAND_UPUnk) {
                            this->tribes[newTribeID].tribeBehaviorType = STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                        }
                    }
                    else if (DAT_UnitsState::instance.units[unitID].unitType == UT_TUNNELER
                        && DAT_UnitsState::instance.units[unitID].state.generic == States::US_LOOK_AROUNDUnk) {
                        this->tribes[newTribeID].tribeBehaviorType = STBT_0x415;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, newTribeID);
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
