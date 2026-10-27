#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

// The original has no return value except on the "spend the remaining stone" path (see below).
#pragma warning(disable : 4715)

namespace OpenSHC {
namespace Synchrony {

    // missing = 20 - ammo (movsx, signed jle 0x466018), stone = (missing + 1) / 2 (cdq; sar), stock < stone is
    // signed (jl 0x466030), remaining stock <= 0 ends the function (jle 0x466074). Only the path that spends the
    // remaining stone has eax = &stoneAmmunition (lea at 0x466096); the other exits leave whatever is in eax.
    // The only caller (0x4850C9, CommandSelectionReplenishAmmo, void) ignores the result. The index is only
    // the getUnitIDForIndexInTribe argument, so incrementing it in the for header equals the original's
    // increment right after the call (0x465FDA); the header form matched better (61.9 vs 53.2).
    // FUNCTION: STRONGHOLDCRUSADER 0x00465F90
    short* Actions::SelectionReplenishAmmo(int playerID, int tribeID)
    {
        for (int i = 0; i < DAT_TribesState::instance.tribes[tribeID].size; i++) {
            int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                DAT_TribesState::ptr)(tribeID, i);
            if (DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                && DAT_UnitsState::instance.units[unitID].dying == 0
                && (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                    || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET)) {
                int missingAmmo = 20 - DAT_UnitsState::instance.units[unitID].stoneAmmunition;
                if (missingAmmo > 0) {
                    int stoneNeeded = (missingAmmo + 1) / 2;
                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_STONE] < stoneNeeded) {
                        int stone = DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_STONE];
                        if (stone > 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                                DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone, 0);
                            DAT_UnitsState::instance.units[unitID].stoneAmmunition += stone * 2;
                            return &DAT_UnitsState::instance.units[unitID].stoneAmmunition;
                        }
                        break;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stoneNeeded, 0);
                    DAT_UnitsState::instance.units[unitID].stoneAmmunition += missingAmmo;
                }
            }
        }
    }

}
}
