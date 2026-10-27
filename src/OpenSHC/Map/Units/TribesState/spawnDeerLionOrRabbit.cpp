#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The spawn position, rng byte and herd sizes are read before the timer test (0x525F7A..0x525FAC); the
        // interval is quartered with a signed divide (cdq at 0x525FBD). Threshold: 0x6E for rabbits during the
        // rabbit-infestation event, else 100 when size >= min size, 25 otherwise (setge at 0x52600B).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525F20
        BOOLEnum TribesState::spawnDeerLionOrRabbit(int tribeID, int spawnInterval, UnitType unitType)
        {
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return FALSE;
            }
            if (tribeID <= 0) {
                return FALSE;
            }
            if (this->tribes[tribeID].wildlifeAlarmTimer != 0) {
                return FALSE;
            }
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            int sourceUnitID = leaderUnitID;
            if (unitType == UT_ANTELOPESHDEER) {
                sourceUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getNonDyingUnit, this)(tribeID);
                if (sourceUnitID == 0) {
                    sourceUnitID = leaderUnitID;
                }
            }
            int const rng = SEC_RNG::instance.currentNumber2 & 0x7f;
            int const spawnHeight = DAT_UnitsState::instance.units[sourceUnitID].terrainOrClimbHeight;
            int const spawnX = DAT_UnitsState::instance.units[sourceUnitID].x;
            int const spawnY = DAT_UnitsState::instance.units[sourceUnitID].y;
            short const herdMinSize = this->tribes[tribeID].wildlifeMinSize;
            short const herdSize = this->tribes[tribeID].size;
            if (herdSize <= herdMinSize) {
                spawnInterval /= 4;
            }
            ++this->tribes[tribeID].wildlifeSpawnTimer;
            if (this->tribes[tribeID].wildlifeSpawnTimer < spawnInterval) {
                return FALSE;
            }
            this->tribes[tribeID].wildlifeSpawnTimer = 0;
            if (herdSize >= this->tribes[tribeID].wildlifeMaxSize) {
                return FALSE;
            }
            int threshold;
            if (unitType == UT_RABBIT && DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation != 0) {
                threshold = 0x6e;
            } else {
                threshold = herdSize < herdMinSize ? 25 : 100;
            }
            if (threshold > rng) {
                return FALSE;
            }
            int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                DAT_UnitsState::ptr)(0, 0, spawnX * 8, spawnY * 8, spawnHeight, unitType);
            if (unitID == 0) {
                return FALSE;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
            DAT_UnitsState::instance.units[unitID].substate = (short)(DAT_UnitsState::instance.units[unitID].fixedRng & 3);
            if (unitType == UT_ANTELOPESHDEER) {
                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 2;
            }
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0x20;
            if (unitType == UT_ANTELOPESHDEER) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateAnimalHerdBehaviorState, this)(tribeID);
            }
            return TRUE;
        }

    }
}
}
