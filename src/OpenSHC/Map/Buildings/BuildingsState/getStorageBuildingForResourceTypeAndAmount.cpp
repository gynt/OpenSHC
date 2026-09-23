#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BFE0
int BuildingsState::getStorageBuildingForResourceTypeAndAmount(ResourceType resourceType,int amount,int owner)

{
BuildingType _targetBuildingType;
int _buildingID;
int *_currentResourceOfTypeOfBuilding;
short *_buildingType;

_targetBuildingType = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
_buildingID = this->maxBuildingsCount + -1;
if (0 < _buildingID) {
_buildingType = (short *)((int)this + _buildingID * 0x32c + 0xe6);
_currentResourceOfTypeOfBuilding =
(int *)((int)this + (_buildingID * 0xcb + resourceType) * 4 + 0x134);
do {
if ((((_buildingType[-1] == 2) && ((int)*_buildingType == _targetBuildingType)) &&
(_buildingType[2] == owner)) && (amount <= *_currentResourceOfTypeOfBuilding)) {
return _buildingID;
}
_buildingID = _buildingID + -1;
_buildingType = _buildingType + -0x196;
_currentResourceOfTypeOfBuilding = _currentResourceOfTypeOfBuilding + -0xcb;
} while (0 < _buildingID);
}
return 0;
}


}
}
}