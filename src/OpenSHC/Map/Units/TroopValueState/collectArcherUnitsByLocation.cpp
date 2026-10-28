#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CA50
        void TroopValueState::collectArcherUnitsByLocation()
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                2000, '\0', DAT_TroopValueState::instance.attackInfo.reserveArcherUnitIDs);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                800, '\0', DAT_TroopValueState::instance.attackInfo.wallArcherPostTiles);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                400, '\0', DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitIDs);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                800, '\0', DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitUIDs);
            DAT_TroopValueState::instance.attackInfo.reserveArcherCount = 0;
            DAT_TroopValueState::instance.attackInfo.wallArcherPostCount = 0;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_INVISIBLE
                    || MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        == FALSE
                    || (DAT_UnitsState::instance.units[unitID].unitType != UT_E_ARCHER
                        && DAT_UnitsState::instance.units[unitID].unitType != UT_E_XBOW)) {
                    continue;
                }
                if ((DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile] & 0x10000100)
                    != 0) {
                    // on a wall or tower: record as a wall post if not rallying or not part of a tribe
                    if (DAT_TroopValueState::instance.attackInfo.wallArcherPostCount < 200) {
                        int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
                        if (tribeID == 0 || DAT_TribesState::instance.tribes[tribeID].rallyMode == 0) {
                            DAT_TroopValueState::instance.attackInfo
                                .wallArcherPostTiles[DAT_TroopValueState::instance.attackInfo.wallArcherPostCount]
                                = DAT_UnitsState::instance.units[unitID].tile;
                            DAT_TroopValueState::instance.attackInfo
                                .wallArcherPostUnitUIDs[DAT_TroopValueState::instance.attackInfo.wallArcherPostCount]
                                = DAT_UnitsState::instance.units[unitID].uid;
                            DAT_TroopValueState::instance.attackInfo
                                .wallArcherPostUnitIDs[DAT_TroopValueState::instance.attackInfo.wallArcherPostCount]
                                = unitID;
                            ++DAT_TroopValueState::instance.attackInfo.wallArcherPostCount;
                        }
                    }
                } else if (DAT_TroopValueState::instance.attackInfo.reserveArcherCount < 1000) {
                    // not on a wall or tower: keep as reserve
                    MACRO_CALL_MEMBER(TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].tribeID);
                    DAT_TroopValueState::instance.attackInfo
                        .reserveArcherUnitIDs[DAT_TroopValueState::instance.attackInfo.reserveArcherCount] = unitID;
                    ++DAT_TroopValueState::instance.attackInfo.reserveArcherCount;
                }
            }
        }

    }
}
}
