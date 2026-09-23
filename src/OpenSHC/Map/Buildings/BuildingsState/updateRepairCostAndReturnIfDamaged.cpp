#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410320
BOOLEnum BuildingsState::updateRepairCostAndReturnIfDamaged(int buildingIndex)

{
BuildingTypeShort BVar1;
int iVar2;
short _currentHealth;
int _stoneRequiredToBuild;
int _woodRequiredToBuild;

_currentHealth = this->buildings[buildingIndex].currentHealth;
if (_currentHealth == this->buildings[buildingIndex].maxHealth) {
return FALSE;
}
BVar1 = this->buildings[buildingIndex].buildingType;
_stoneRequiredToBuild = this->buildingCosts[(short)BVar1].requiredStone_0x4;
_woodRequiredToBuild = this->buildingCosts[(short)BVar1].requiredWood;
if (_woodRequiredToBuild == 0) {
this->INT_SelectedBuildingStoneWoodCost = 0;
}
else {
iVar2 = (int)this->buildings[buildingIndex].maxHealth;
if (((iVar2 - _currentHealth) * _woodRequiredToBuild) / iVar2 < 1) {
this->INT_SelectedBuildingStoneWoodCost = 1;
}
else {
iVar2 = (int)this->buildings[buildingIndex].maxHealth;
this->INT_SelectedBuildingStoneWoodCost =
((iVar2 - _currentHealth) * _woodRequiredToBuild) / iVar2;
}
}
if (_stoneRequiredToBuild != 0) {
iVar2 = (int)this->buildings[buildingIndex].maxHealth;
_woodRequiredToBuild = (int)this->buildings[buildingIndex].currentHealth;
if (((iVar2 - _woodRequiredToBuild) * _stoneRequiredToBuild) / iVar2 < 1) {
this->INT_SelectedBuildingStoneRepairCost = 1;
return TRUE;
}
iVar2 = (int)this->buildings[buildingIndex].maxHealth;
this->INT_SelectedBuildingStoneRepairCost =
((iVar2 - _woodRequiredToBuild) * _stoneRequiredToBuild) / iVar2;
return TRUE;
}
this->INT_SelectedBuildingStoneRepairCost = 0;
return TRUE;
}


}
}
}