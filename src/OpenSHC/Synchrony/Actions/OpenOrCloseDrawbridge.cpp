#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // drawbridgeCommand is written as a byte (0x4653CC). 10 raises the bridge (apply(id, FALSE, TRUE) at 0x4653E1),
    // any other value lowers it (apply(id, TRUE, TRUE) at 0x4653EA). playerID is unused.
    // FUNCTION: STRONGHOLDCRUSADER 0x004653B0
    void Actions::OpenOrCloseDrawbridge(undefined4 playerID, int buildingID, int value, int buildingUID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].drawbridgeCommand = (byte)value;
            if (value == 10) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, FALSE, TRUE);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, TRUE, TRUE);
            }
        }
    }

}
}
