#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // gateState is written as a byte (0x46550F). 10 closes (timer -1, apply(id, FALSE, FALSE) at 0x465533),
    // 11 opens (timer 600, apply(id, TRUE, FALSE) at 0x465551); other states only store gateState.
    // FUNCTION: STRONGHOLDCRUSADER 0x004654F0
    void Actions::GateOpenOrClose(undefined4 playerID, int buildingID, int newGateState, int buildingUID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].gateState = (byte)newGateState;
            DAT_BuildingsState::instance.buildings[buildingID].enemyNearbyHoldTimer = 0;
            if (newGateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = -1;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, FALSE, FALSE);
            } else if (newGateState == 11) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = 600;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, TRUE, FALSE);
            }
        }
    }

}
}
