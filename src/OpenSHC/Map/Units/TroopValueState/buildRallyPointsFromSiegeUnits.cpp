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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519690
        void TroopValueState::buildRallyPointsFromSiegeUnits(int tribeID)
        {
            DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState == 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isPlayerSlotNotHuman,
                        DAT_GameState::ptr)(DAT_TribesState::instance.tribes[i].owner)
                    == FALSE) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[i].tribeType != AI::Tribes::AITT_CATAPULTS
                    && DAT_TribesState::instance.tribes[i].tribeType != AI::Tribes::AITT_TREBUCHETS) {
                    continue;
                }
                int const siegeUnitID = DAT_TribesState::instance.tribes[i].leaderUnitID;
                if (DAT_UnitsState::instance.units[siegeUnitID].stoneAmmunition <= 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                    DAT_PathFindingState::ptr)(
                    -1, DAT_UnitsState::instance.units[siegeUnitID].x, DAT_UnitsState::instance.units[siegeUnitID].y);
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                    = DAT_PathFindingState::instance.ALG_ResultX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = DAT_PathFindingState::instance.ALG_ResultY;
                DAT_TribesState::instance.tribes[tribeID].rallyPointCount++;
            }

            if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex < 0) {
                DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
            }
            if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex
                >= DAT_TribesState::instance.tribes[tribeID].rallyPointCount) {
                DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
            }
        }

    }
}
}
