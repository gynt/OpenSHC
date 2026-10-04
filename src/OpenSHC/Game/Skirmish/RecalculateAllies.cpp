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

    // FUNCTION: STRONGHOLDCRUSADER 0x004AC570
    void Skirmish::RecalculateAllies()
    {
        int _playerID;
        if (400 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
            DAT_AlliesCount::instance = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer,
                DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
            if (DAT_AlliesCount::instance == 0) {}
        }
        int _teamMembers = 0;
        int _team
            = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
        DAT_AlliesCount::instance = 0;
        for (_playerID = 1; _playerID < 9; _playerID++) {
            if ((_playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1
                    || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)))) {
                if (400 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
                    int iVar1 = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID);
                    _teamMembers = DAT_AlliesCount::instance;
                    if (iVar1 == 0)
                        continue;
                }
                if (_team == DAT_GameState::instance.mapAndTime.playerTeams[_playerID]) {
                    DAT_SomeTeamMemberPlayerIDArray::instance[_teamMembers] = _playerID;
                    _teamMembers = _teamMembers + 1;
                    DAT_AlliesCount::instance = _teamMembers;
                    if (5 < _teamMembers)
                        break;
                }
            }
        }
        if (_teamMembers <= DAT_LastTeamMemberIndex::instance) {
            DAT_LastTeamMemberIndex::instance = _teamMembers + -1;
        }
        if (DAT_LastTeamMemberIndex::instance < 0) {
            DAT_LastTeamMemberIndex::instance = 0;
        }
    }

}
}
