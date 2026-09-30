#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00519850
        void TroopValueState::initializeAttackZoneSearch(int param_1)
        {
            int _tile;
            this->attackInfo.biggestZone = 0;
            _tile = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[(&this->attackInfo.unknownSignpostRelatedArray)[param_1]]
                        .tile;
            this->attackInfo.startCon = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
            this->attackInfo.startZone = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
            this->attackInfo.zoneSize
                = DAT_PathFindingState::instance
                      .zoneSizesArray[(short)DAT_TileMapState::instance.PathConnectionLayer[_tile]];
            this->attackInfo.unknownOne_0x20f90 = 1;
            this->attackInfo.keepCon
                = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[DAT_GameState::instance
                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .campground.tileEntry];
        }

    }
}
}
