#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F1E0
void BuildingsState::setSignpostDataForBuildings()

{
MapAndTimeState * piVar1;
int iVar1;
Building * _ptrBuilding;
int _buildingID;

_buildingID = 0;
_ptrBuilding = &this->buildings[0];
do {
if ((_ptrBuilding->logicalState != ((BuildingLogicalState)0)) && (_ptrBuilding->buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST))
{
piVar1 = (MapAndTimeState *)DAT_GameState::instance.mapAndTime;
do {
/* 
  if signpost1 is already set to this buildingID, then go to the next building.
   
 */

if (piVar1->signpostIDs[0] == _buildingID) goto LAB_0040f22b;
piVar1 = (MapAndTimeState *)(piVar1->signpostIDs + 1);
} while ((int)piVar1 < 0x117f0c4);
/* 
  bug: ? because a break is missing from the above while loop, it actually
   assigns that last signpost id first !?
 */

iVar1 = 0;
do {
if (DAT_GameState::instance.mapAndTime.signpostIDs[iVar1] < 1) {
DAT_GameState::instance.mapAndTime.signpostIDs[iVar1] = _buildingID;
break;
}
iVar1 = iVar1 + 1;
} while (iVar1 < 8);
}
LAB_0040f22b:
_buildingID = _buildingID + 1;
_ptrBuilding = _ptrBuilding + 0x196;
if (1999 < _buildingID) {
return;
}
} while( true );
}


}
}
}