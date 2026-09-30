#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::Building;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0041A520
    void Version::UpgradePitchDitchBuildingIntoPitchDitchObject()
    {
        ushort uVar1;
        uint uVar2;
        Building* puVar3;
        puVar3 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if ((puVar3->logicalState != ((BuildingLogicalState)0))
                && (puVar3->buildingType == OpenSHC::Map::Buildings::BT_PITCHDITCH)) {
                uVar2 = puVar3->currentTilePositionAdjusted;
                uVar1 = puVar3->y;
                DAT_TileMapState::instance.BuildingLayer[uVar2] = 0;
                DAT_TileMapState::instance.LogicLayer[uVar2]
                    = DAT_TileMapState::instance.LogicLayer[uVar2] & 0xfffffbff;
                DAT_TileMapState::instance.BuildingWasLayer[uVar2] = '\0';
                DAT_TileMapState::instance.HeightLayer[uVar2] = DAT_TileMapState::instance.DefaultHeightLayer[uVar2];
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePitchDitch, DAT_TileMapState::ptr)(
                    (int)puVar3->owner, (uint)((int)((int)(short)puVar3->x)), (uint)((int)((int)(short)uVar1)));
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(
                    4, (uint)((int)((int)(short)puVar3->x)), (uint)((int)((int)(short)puVar3->y)));
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    812, '\0', puVar3);
            }
            puVar3 = puVar3 + 0xcb;
        } while ((int)puVar3 < 0x1124de8);
    }

}
}
