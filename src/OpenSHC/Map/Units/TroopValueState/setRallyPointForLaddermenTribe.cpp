#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519790
        void TroopValueState::setRallyPointForLaddermenTribe(int tribeID)
        {
            int laddermenTribeCount = 0;
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState == 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isPlayerSlotNotHuman,
                        DAT_GameState::ptr)(DAT_TribesState::instance.tribes[i].owner)
                    == FALSE) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[i].tribeType != AI::Tribes::AITT_LADDERMEN) {
                    continue;
                }
                laddermenTribeCount++;
                if (laddermenTribeCount == DAT_TribesState::instance.tribes[tribeID].waveAssignmentSlot + 1) {
                    int const unitID = DAT_TribesState::instance.tribes[i].leaderUnitID;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                        DAT_PathFindingState::ptr)(
                        -1, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                    DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][0]
                        = DAT_PathFindingState::instance.ALG_ResultX;
                    DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][1]
                        = DAT_PathFindingState::instance.ALG_ResultY;
                    return;
                }
            }
        }

    }
}
}
