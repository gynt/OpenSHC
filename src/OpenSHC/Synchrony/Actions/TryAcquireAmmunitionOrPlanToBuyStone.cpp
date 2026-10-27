#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // stone >= 10 is signed (jl 0x465F37). The lea eax after the ammo add (0x465F5B) is how MSVC compiles the
    // short += in this void function (the same lea comes out of this source); callers ignore eax anyway.
    // Byte-exact only without /GL: this file is listed in cmake/compiler-flags-gl.txt, which makes the code
    // generator pass the arguments in registers (verified: the same body in a non-/GL file matches 100%).
    // FUNCTION: STRONGHOLDCRUSADER 0x00465F20
    void Actions::TryAcquireAmmunitionOrPlanToBuyStone(int playerID, int unitID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_STONE] >= 10) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, 10, 0);
            DAT_UnitsState::instance.units[unitID].stoneAmmunition += 20;
            return;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[OpenSHC::Game::Resources::RT_STONE] = 10;
        }
    }

}
}
