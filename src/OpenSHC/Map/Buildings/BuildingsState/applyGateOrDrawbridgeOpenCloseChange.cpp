#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041C570
void BuildingsState::applyGateOrDrawbridgeOpenCloseChange(int buildingID,BOOLEnum param_2,BOOLEnum param_3)

{
int iVar1;
int iVar2;

if (this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, this)((int)this->buildings[buildingID].owner, (int)((int)(
(short)this->buildings[buildingID].x)), (int)((int)(
(short)this->buildings[buildingID].y)), (int)((int)(
this->buildings[buildingID].widthOrHeight)), OpenSHC::Map::Buildings::BT_GATEHOUSELARGE, 0);
if ((iVar1 != 0) ||
(iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, this)((int)this->buildings[buildingID].owner, (int)((int)(
(short)this->buildings[buildingID].x)), (int)((int)(
(short)this->buildings[buildingID].y)), (int)((int)(
this->buildings[buildingID].widthOrHeight)), OpenSHC::Map::Buildings::BT_GATEHOUSESMALL, 
0), iVar1 != 0)) {
if (param_2 == FALSE) {
if (this->buildings[iVar1].pathLinkageRelated2 == 0) {
if (param_3 != FALSE) {
this->buildings[iVar1].gateCloseOpenTimer = -1;
}
this->buildings[iVar1].gateState = 10;
return;
}
}
else if (this->buildings[iVar1].pathLinkageRelated2 == 2) {
if (param_3 != FALSE) {
this->buildings[iVar1].gateCloseOpenTimer = 600;
}
this->buildings[iVar1].gateState = 0xb;
return;
}
}
}
else {
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, this)((int)this->buildings[buildingID].owner, (int)((int)(
(short)this->buildings[buildingID].x)), (int)((int)(
(short)this->buildings[buildingID].y)), (int)((int)(
this->buildings[buildingID].widthOrHeight)), OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, this)((int)this->buildings[buildingID].owner, (int)((int)(
(short)this->buildings[buildingID].x)), (int)((int)(
(short)this->buildings[buildingID].y)), (int)((int)(
this->buildings[buildingID].widthOrHeight)), OpenSHC::Map::Buildings::BT_DRAWBRIDGE, iVar1);
while (iVar1 != 0) {
if (param_2 == FALSE) {
if (this->buildings[iVar1].drawBridgeState1 == 0) {
this->buildings[iVar1].drawbridgeState2 = 10;
}
}
else if (this->buildings[iVar1].drawBridgeState1 == 2) {
this->buildings[iVar1].drawbridgeState2 = 0xb;
}
iVar1 = iVar2;
iVar2 = 0;
}
}
return;
}


}
}
}