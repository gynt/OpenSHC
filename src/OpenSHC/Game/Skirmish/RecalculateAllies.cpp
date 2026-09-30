#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AC570
    void Skirmish::RecalculateAllies()
    {
        int _teamMembers;
        int iVar1;
        int _playerID;
        int _team;
        if (400 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
            DAT_AlliesCount::instance = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
            if (DAT_AlliesCount::instance == 0) {}
        }
        _teamMembers = 0;
        _team = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
        DAT_AlliesCount::instance = 0;
        _playerID = 1;
        do {
            if ((_playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1
                    || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)))) {
                if (400 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
                    iVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID);
                    _teamMembers = DAT_AlliesCount::instance;
                    if (iVar1 == 0)
                        goto LAB_004ac619;
                }
                if (_team == DAT_GameState::instance.mapAndTime.playerTeams[_playerID]) {
                    DAT_SomeTeamMemberPlayerIDArray::instance[_teamMembers] = _playerID;
                    _teamMembers = _teamMembers + 1;
                    DAT_AlliesCount::instance = _teamMembers;
                    if (5 < _teamMembers)
                        break;
                }
            }
        LAB_004ac619:
            _playerID = _playerID + 1;
        } while (_playerID < 9);
        if (_teamMembers <= DAT_LastTeamMemberIndex::instance) {
            DAT_LastTeamMemberIndex::instance = _teamMembers + -1;
        }
        if (DAT_LastTeamMemberIndex::instance < 0) {
            DAT_LastTeamMemberIndex::instance = 0;
        }
    }

}
}
