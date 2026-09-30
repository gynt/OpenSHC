#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitType;

    /*
      Scales every AI lord's health by the per-AI-type multiplier and records the rating.
      The original walks the unit array three units at a time with the body written out
      once per unit, so the three blocks below are kept separate rather than folded.
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0053B610
    void Version::UpgradeMapUnitsLordHealthTo_169()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }

        for (int i = 1; i < 2500; i += 3) {
            Unit* unit = &DAT_UnitsState::instance.units[i];

            if ((unit[0].unitType == OpenSHC::Map::Units::UT_LORD)
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[unit[0].owner] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[unit[0].owner] != 0)) {
                AITypeInt const aiType = DAT_GameState::instance.playerDataArray[unit[0].owner].aiType;
                unit[0].maxHealthRatingLord
                    = (short)DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                          .aiTypeA;
                if (unit[0].health == unit[0].maxHealth) {
                    int const multiplier
                        = DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                              .maxHealthMultiplier;
                    unit[0].health = (unit[0].health * multiplier) / 100;
                    unit[0].maxHealth = (unit[0].maxHealth * multiplier) / 100;
                }
            }

            if ((unit[1].unitType == OpenSHC::Map::Units::UT_LORD)
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[unit[1].owner] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[unit[1].owner] != 0)) {
                AITypeInt const aiType = DAT_GameState::instance.playerDataArray[unit[1].owner].aiType;
                unit[1].maxHealthRatingLord
                    = (short)DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                          .aiTypeA;
                if (unit[1].health == unit[1].maxHealth) {
                    int const multiplier
                        = DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                              .maxHealthMultiplier;
                    unit[1].health = (unit[1].health * multiplier) / 100;
                    unit[1].maxHealth = (unit[1].maxHealth * multiplier) / 100;
                }
            }

            if ((unit[2].unitType == OpenSHC::Map::Units::UT_LORD)
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[unit[2].owner] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[unit[2].owner] != 0)) {
                AITypeInt const aiType = DAT_GameState::instance.playerDataArray[unit[2].owner].aiType;
                unit[2].maxHealthRatingLord
                    = (short)DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                          .aiTypeA;
                if (unit[2].health == unit[2].maxHealth) {
                    int const multiplier
                        = DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[aiType + ~OpenSHC::AI::AIT_NULL]
                              .maxHealthMultiplier;
                    unit[2].health = (unit[2].health * multiplier) / 100;
                    unit[2].maxHealth = (unit[2].maxHealth * multiplier) / 100;
                }
            }
        }
    }

}
}
