#include "../Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_00df423c.hpp"
#include "OpenSHC/Globals/DAT_00df4240.hpp"
#include "OpenSHC/Globals/DAT_00df4288.hpp"
#include "OpenSHC/Globals/DAT_00df4298.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

/*
  Copies the first three entries from DAT_PlayerGroupArray into playerGroupArray2Unk in   GameSynchronyState, and zeroes
  four related fields. Keeps the secondary player group array in   sync with the primary one, likely called after a
  group membership change or session reset.      renamed by: Claude Sonnet 4.6
 */
// FUNCTION: STRONGHOLDCRUSADER 0x004AEA10
void Synchrony::syncPlayerGroupArrays()
{
    *(dword*)&DAT_GameSynchronyState::instance.playerGroupArray2Unk[0]
        = *(dword*)&DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[0];
    DAT_00df423c::instance = 0;
    DAT_00df4288::instance = 0;
    *(dword*)&DAT_GameSynchronyState::instance.playerGroupArray2Unk[4]
        = *(dword*)&DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4];
    DAT_GameSynchronyState::instance.playerGroupArray2Unk[8] = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8];
    DAT_00df4240::instance = 0;
    DAT_00df4298::instance = 0;
}

}
