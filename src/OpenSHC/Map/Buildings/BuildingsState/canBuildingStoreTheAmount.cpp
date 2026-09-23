#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::Resources::ResourceType;


/* 
  WARNING: Type propagation algorithm not settling
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BF40
int BuildingsState::canBuildingStoreTheAmount(int buildingID,ResourceType resourceType,int storageLimit)

{
Building * _ptrBuilding;
ResourceType _counter;
int _amount;

_amount = this->buildings[buildingID].resources[resourceType];
_counter = OpenSHC::Game::Resources::RT_LOGS;
_ptrBuilding = (Building *)this->buildings[buildingID];
while ((_ptrBuilding = (Building *)(_ptrBuilding->resources + 1),
_ptrBuilding->resources[0] == 0 || (_counter == resourceType))) {
_counter = _counter + OpenSHC::Game::Resources::RT_LOGS;
if (25 < (int)_counter) {
if (storageLimit <= _amount) {
return 0;
}
return storageLimit - _amount;
}
}
return 0;
}


}
}
}