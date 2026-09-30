#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Thin wrapper around Game::GameStateStructures::resetTeams. Resets the team assignments in the   global GameState.
      Called during map version upgrades to clear any team data that may be stale or   incompatible with the new version
      format.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AE00
    void Version::ResetTeams()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
    }

}
}
