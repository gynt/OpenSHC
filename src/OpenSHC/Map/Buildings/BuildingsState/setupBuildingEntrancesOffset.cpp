#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/PTR_ARRAY_0040bc20.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BA10
void BuildingsState::setupBuildingEntrancesOffset(int buildingSize,int nudge,int try,int offset)

{
switch(buildingSize) {
case 1:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field193_0x8da8[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field193_0x8da8[try].y;
break;
case 2:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field198_0x8dcc[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field198_0x8dcc[try].y;
break;
case 3:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field199_0x8e0c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field199_0x8e0c[try].y;
break;
case 4:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field200_0x8e6c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field200_0x8e6c[try].y;
break;
case 5:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field201_0x8eec[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field201_0x8eec[try].y;
break;
case 6:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field202_0x8f8c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field202_0x8f8c[try].y;
break;
case 7:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field203_0x904c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field203_0x904c[try].y;
break;
case 8:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field204_0x912c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field204_0x912c[try].y;
break;
case 9:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field205_0x922c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field205_0x922c[try].y;
break;
case 10:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field206_0x934c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field206_0x934c[try].y;
break;
case 0xb:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field207_0x948c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field207_0x948c[try].y;
break;
case 0xc:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field208_0x95ec[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field208_0x95ec[try].y;
break;
case 0xd:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field209_0x976c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field209_0x976c[try].y;
break;
default:
this->DAT_TempYOffset = 0;
this->DAT_TempXOffset = 0;
}
if ((uint)((try / buildingSize) * 2) < 7) {
/* 
  WARNING: Switch is manually overridden
 */

switch(PTR_ARRAY_0040bc20::instance[(try / buildingSize) * 2]) {
case (undefined *)0x40bb7e:
this->DAT_TempYOffset = this->DAT_TempYOffset - offset;
break;
case (undefined *)0x40bb8a:
this->DAT_TempYOffset = this->DAT_TempYOffset + offset;
break;
case (undefined *)0x40bb96:
this->DAT_TempXOffset = this->DAT_TempXOffset + offset;
break;
case (undefined *)0x40bba2:
this->DAT_TempXOffset = this->DAT_TempXOffset - offset;
}
}
if ((this->DAT_TempXOffset < buildingSize) &&
(this->DAT_TempYOffset < buildingSize)) {
if (0x7fffffff < (uint)this->DAT_TempXOffset) {
this->DAT_TempXOffset = (this->DAT_TempXOffset - nudge) + 1;
return;
}
if (0x7fffffff < (uint)this->DAT_TempYOffset) {
this->DAT_TempYOffset = (this->DAT_TempYOffset - nudge) + 1;
}
}
return;
}


}
}
}