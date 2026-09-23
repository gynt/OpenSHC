#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040E740
void BuildingsState::setTileRefsForOilSmelter(int buildingID)

{
int _index;
uint _y1;
uint _y2;
uint _y3;
uint _y4;
uint _x1;
uint _x2;
uint _x3;
uint _x4;

_index = 0;
do {
_x1 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index].x +
(int)(short)this->buildings[buildingID].x;
_y1 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index].y +
(int)(short)this->buildings[buildingID].y;
if (((_x1 < 400) && (_y1 < 400)) && (*(char *)(_x1 + 0x21aec98 + _y1 * 400) != '\0')) {
*(uint *)(this->buildings[buildingID].workers + _index * 2 + 8) =
DAT_ViewportRenderState::instance.translationMatrix[_y1].addXgetTile + _x1;
}
_x2 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 1].x +
(int)(short)this->buildings[buildingID].x;
_y2 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 1].y +
(int)(short)this->buildings[buildingID].y;
if (((_x2 < 400) && (_y2 < 400)) && (*(char *)(_x2 + 0x21aec98 + _y2 * 400) != '\0')) {
*(uint *)(this->buildings[buildingID].workers + _index * 2 + 10) =
DAT_ViewportRenderState::instance.translationMatrix[_y2].addXgetTile + _x2;
}
_x3 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 2].x +
(int)(short)this->buildings[buildingID].x;
_y3 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 2].y +
(int)(short)this->buildings[buildingID].y;
if (((_x3 < 400) && (_y3 < 400)) && (*(char *)(_x3 + 0x21aec98 + _y3 * 400) != '\0')) {
*(uint *)(this->buildings[buildingID].workers + _index * 2 + 0xc) =
DAT_ViewportRenderState::instance.translationMatrix[_y3].addXgetTile + _x3;
}
_x4 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 3].x +
(int)(short)this->buildings[buildingID].x;
_y4 = (int)DAT_BuildingDefinedData::instance.field412_0xa00c[_index + 3].y +
(int)(short)this->buildings[buildingID].y;
if (((_x4 < 400) && (_y4 < 400)) && (*(char *)(_x4 + 0x21aec98 + _y4 * 400) != '\0')) {
*(uint *)(this->buildings[buildingID].workers + _index * 2 + 0xe) =
DAT_ViewportRenderState::instance.translationMatrix[_y4].addXgetTile + _x4;
}
_index = _index + 4;
} while (_index < 16);
return;
}


}
}
}