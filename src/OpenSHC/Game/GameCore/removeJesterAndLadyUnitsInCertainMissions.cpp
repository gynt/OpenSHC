#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BBD0
    void GameCore::removeJesterAndLadyUnitsInCertainMissions()
    {
        if (this->missionNumber < 7) {
            DAT_GameState::instance.mapAndTime.jesterEnabled = 0;
            int const jesterID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .jesterUnitID;
            if (jesterID != 0
                && DAT_UnitsState::instance.units[jesterID].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .jesterUnitUID) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .jesterUnitID = 0;
                DAT_UnitsState::instance.units[jesterID].logicalState = Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .jesterUnitUID = 0;
            }
        } else {
            DAT_GameState::instance.mapAndTime.jesterEnabled = 1;
        }

        if (this->missionNumber < 11) {
            DAT_GameState::instance.mapAndTime.ladyEnabled = 0;
            int const ladyID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .ladyUnitID;
            if (ladyID != 0
                && DAT_UnitsState::instance.units[ladyID].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .ladyUnitUID) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ladyUnitID
                    = 0;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ladyUnitUID = 0;
                DAT_UnitsState::instance.units[ladyID].logicalState = Map::Units::ULS_REMOVE;
            }
        } else {
            DAT_GameState::instance.mapAndTime.ladyEnabled = 1;
        }
    }

}
}
