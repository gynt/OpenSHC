#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519850
        void TroopValueState::initializeAttackZoneSearch(int attackID)
        {
            DAT_TroopValueState::instance.attackInfo.biggestZone = 0;
            // attackWaveSignpostIndex is a per-wave int[50] (declared as a single int in AttackInfo)
            int startTile = DAT_GameState::instance.mapAndTime
                                .signpostEntryData[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[attackID]]
                                .tile;
            DAT_TroopValueState::instance.attackInfo.startZone = (char)DAT_TileMapState::instance.AIZoneLayer[startTile];
            DAT_TroopValueState::instance.attackInfo.startCon
                = (short)DAT_TileMapState::instance.PathConnectionLayer[startTile];
            DAT_TroopValueState::instance.attackInfo.zoneSize
                = DAT_PathFindingState::instance.zoneSizesArray[DAT_TroopValueState::instance.attackInfo.startCon];
            DAT_TroopValueState::instance.attackInfo.unknownOne_0x20f90 = 1;
            DAT_TroopValueState::instance.attackInfo.keepCon = (short)DAT_TileMapState::instance.PathConnectionLayer
                [DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .campground.tileEntry];
        }

    }
}
}
