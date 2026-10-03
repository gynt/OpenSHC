#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    using OpenSHC::Game::Player::PlayerData;


    /*
      Iterates all players and validates their lady and jester unit references. If a unit ID no longer   matches the
      stored UID in UnitsState (i.e. the unit was replaced or removed), both the unit ID   and its self-reference field
      are cleared to zero. Prevents stale references to dead or reassigned   units.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045ACC0
    void Version::ValidateLadyAndJesterUnitRefs()
    {
        PlayerData* piVar1;
        piVar1 = &DAT_GameState::instance.playerDataArray[1];
        do {
            if ((piVar1->ladyIDUnk != 0)
                && (piVar1->someUnitIDSelfRef != DAT_UnitsState::instance.units[piVar1->ladyIDUnk].uid)) {
                piVar1->ladyIDUnk = 0;
                piVar1->someUnitIDSelfRef = 0;
            }
            if ((piVar1->jesterIDUnk != 0)
                && (piVar1->someUnitIDSelfRef_2 != DAT_UnitsState::instance.units[piVar1->jesterIDUnk].uid)) {
                piVar1->jesterIDUnk = 0;
                piVar1->someUnitIDSelfRef_2 = 0;
            }
            piVar1 = piVar1 + 0xe7d;
        } while ((int)piVar1 < 0x117e990);
    }

}
}
