#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Percentages are of the size after removals (re-read at 0x52727F), divided signed (idiv); an empty tribe
        // gets 100. percentageUnk29c / percentageUnk2a0 are only cleared (0x527127, 0x527135).
        // FUNCTION: STRONGHOLDCRUSADER 0x005270F0
        void TribesState::computeTribePercentages(int tribeID)
        {
            int memberIndex = 0;
            this->tribes[tribeID].percentageDying = 0;
            this->tribes[tribeID].percentageMoving = 0;
            this->tribes[tribeID].percentageMeleeAttacking = 0;
            this->tribes[tribeID].percentageUnk29c = 0;
            this->tribes[tribeID].percentageShooting = 0;
            this->tribes[tribeID].percentageUnk2a0 = 0;
            this->tribes[tribeID].percentageSomething = 0;
            this->tribes[tribeID].movementSpeed = DAT_UnitsState::instance.units[this->tribes[tribeID].leaderUnitID].movementSpeed;
            int digMoatCount = 0;
            int rangedFiringCount = 0;
            int meleeAttackingCount = 0;
            int movingCount = 0;
            int dyingCount = 0;
            this->tribes[tribeID].unitType = DAT_UnitsState::instance.units[this->tribes[tribeID].leaderUnitID].unitType;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(tribeID, memberIndex);
                    ++memberIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isComputerManagedNonPeasant,
                                DAT_UnitsState::ptr)(unitID)
                            != FALSE) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                unitID, tribeID);
                        } else if (DAT_UnitsState::instance.units[unitID].dying != 0) {
                            ++dyingCount;
                        } else {
                            if (DAT_UnitsState::instance.units[unitID].subTileStepProgress != 8) {
                                ++movingCount;
                            }
                            if (DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK) {
                                ++meleeAttackingCount;
                            }
                            if (DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK_WALL) {
                                ++meleeAttackingCount;
                            }
                            if (DAT_UnitsState::instance.units[unitID].state.generic == States::US_DIG_MOAT) {
                                ++digMoatCount;
                            }
                            if (DAT_UnitsState::instance.units[unitID].isRangedUnit != 0
                                && (DAT_UnitsState::instance.units[unitID].state.generic == States::US_RELOAD_WEAPONUnk
                                    || DAT_UnitsState::instance.units[unitID].state.generic == States::US_AIM_WEAPONUnk
                                    || DAT_UnitsState::instance.units[unitID].state.generic == States::US_FIRE_WEAPONUnk)) {
                                ++rangedFiringCount;
                            }
                            UnitTypeShort const tribeUnitType = this->tribes[tribeID].unitType;
                            if (tribeUnitType != UT_NONE
                                && DAT_UnitsState::instance.units[unitID].unitType != tribeUnitType) {
                                this->tribes[tribeID].unitType = UT_NONE;
                            }
                            short const movementSpeed = DAT_UnitsState::instance.units[unitID].movementSpeed;
                            if (movementSpeed > this->tribes[tribeID].movementSpeed) {
                                this->tribes[tribeID].movementSpeed = movementSpeed;
                            }
                        }
                    }
                } while (memberIndex < this->tribes[tribeID].size);
            }
            int const size = this->tribes[tribeID].size;
            this->tribes[tribeID].percentageDying = (short)(size == 0 ? 100 : dyingCount * 100 / size);
            this->tribes[tribeID].percentageMoving = (short)(size == 0 ? 100 : movingCount * 100 / size);
            this->tribes[tribeID].percentageMeleeAttacking
                = (short)(size == 0 ? 100 : meleeAttackingCount * 100 / size);
            this->tribes[tribeID].percentageShooting = (short)(size == 0 ? 100 : rangedFiringCount * 100 / size);
            this->tribes[tribeID].percentageSomething = (short)(size == 0 ? 100 : digMoatCount * 100 / size);
        }

    }
}
}
