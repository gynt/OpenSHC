#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Commands::MappersEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409F50
int BuildingsState::getSpriteID(MappersEnum commandBuildingType)

{
BuildingType BVar1;

if (commandBuildingType - OpenSHC::Commands::M_MAPPER_GARDEN1 < 0xc) {
return (&DAT_BuildingDefinedData::instance.field209_0x976c[0x2f].y)[commandBuildingType] +
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[0x42];
}
if (commandBuildingType - OpenSHC::Commands::M_MAPPER_CESS_PIT1 < 4) {
return (&DAT_BuildingDefinedData::instance.field208_0x95ec[0x29].x)[commandBuildingType] +
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[0x5b];
}
if (commandBuildingType - OpenSHC::Commands::M_MAPPER_STATUE1 < 5) {
return (&DAT_BuildingDefinedData::instance.field208_0x95ec[0x25].x)[commandBuildingType] +
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[100];
}
if (commandBuildingType - OpenSHC::Commands::M_MAPPER_SHRINE1 < 5) {
return (&DAT_BuildingDefinedData::instance.field208_0x95ec[0x25].x)[commandBuildingType] +
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[0x65];
}
if (commandBuildingType - OpenSHC::Commands::M_MAPPER_POND1 < 4) {
return (&DAT_BuildingDefinedData::instance.field208_0x95ec[0x24].x)[commandBuildingType] +
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[0x68];
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(commandBuildingType);
return DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BVar1];
}


}
}
}