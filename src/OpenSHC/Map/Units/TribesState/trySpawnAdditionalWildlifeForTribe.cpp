#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // tribe+0x288 (extraSpawnTimer, typed undefined1[2] in Tribe.hpp) is a signed short counter: add word 1 and
        // movsx compare at 0x526137..0x52614C. The spawn position and rng byte are read before the timer test.
        // FUNCTION: STRONGHOLDCRUSADER 0x005260B0
        undefined4 TribesState::trySpawnAdditionalWildlifeForTribe(
            int tribeID, int spawnInterval, int maxAnimalCount, int unitType)
        {
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return 0;
            }
            if (tribeID <= 0) {
                return 0;
            }
            if (this->tribes[tribeID].wildlifeAlarmTimer != 0) {
                return 0;
            }
            if (DAT_GameCore::instance.missionNumber == 0x26 && unitType == UT_CAMELSHBEAR) {
                return 0;
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
            int const spawnX = DAT_UnitsState::instance.units[sourceUnitID].x;
            int const spawnY = DAT_UnitsState::instance.units[sourceUnitID].y;
            int const spawnHeight = DAT_UnitsState::instance.units[sourceUnitID].terrainOrClimbHeight;
            short& spawnTimer = *(short*)this->tribes[tribeID].extraSpawnTimer;
            ++spawnTimer;
            if (spawnTimer < spawnInterval) {
                return 0;
            }
            spawnTimer = 0;
            if (rng < 100) {
                return 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::countLivingUnitsOfType, DAT_UnitsState::ptr)(
                    unitType)
                >= maxAnimalCount) {
                return 0;
            }
            if (unitType == UT_CAMELSHBEAR) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createAnimal, this)(
                    OpenSHC::Commands::M_MAPPER_CAMEL, spawnX, spawnY, spawnHeight);
            }
            return 1;
        }

    }
}
}
