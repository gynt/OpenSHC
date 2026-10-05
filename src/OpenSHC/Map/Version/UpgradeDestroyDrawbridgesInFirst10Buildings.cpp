#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingType;
    using WindowsHelper::Enums::BOOLEnum;
    using Map::Buildings::Building;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A460
    void Version::UpgradeDestroyDrawbridgesInFirst10Buildings()
    {
        short sVar1;
        ushort uVar2;
        ushort uVar3;
        short sVar4;
        Building* puVar5;
        int local_8;
        local_8 = 1;
        puVar5 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if ((puVar5->logicalState != ((BuildingLogicalState)0))
                && (puVar5->buildingType == Map::Buildings::BT_DRAWBRIDGE)) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::clearDrawBridgeWater, DAT_TileMapState::ptr)(
                    (int)(short)puVar5->x, (int)((int)((short)puVar5->y)));
                MACRO_CALL_MEMBER(Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities,
                    DAT_TileMapState::ptr)(local_8, 1);
                sVar1 = puVar5->owner;
                uVar2 = puVar5->x;
                uVar3 = puVar5->y;
                sVar4 = puVar5->buildingVariation;
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    812, '\0', puVar5);
                DAT_TileMapState::instance.buildingPlacementFail = FALSE;
                DAT_TileMapState::instance.skipPlacementCheck = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)((int)sVar1,
                    (int)((int)((short)uVar2)), (int)((int)((short)uVar3)), Commands::M_MAPPER_DRAWBRIDGE, 5,
                    (int)((int)(sVar4)));
            }
            local_8 = local_8 + 1;
            puVar5 = puVar5 + 0x196;
        } while ((int)puVar5 < 0x1124de2);
    }

}
}
