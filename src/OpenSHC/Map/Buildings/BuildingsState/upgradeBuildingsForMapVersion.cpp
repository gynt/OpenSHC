#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00420BF0
void BuildingsState::upgradeBuildingsForMapVersion(PackagedFileMagicNum receivedMapVersion,PackagedFileMagicNum packagerMapVersion)

{
MACRO_CALL(OpenSHC::Map::Version_Func::SetUndamagedBuildingHealthToValue)();
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingProperties1)(receivedMapVersion);
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeFirst9Buildings)();
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeKillingPitField)();
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::rebuildTileLogicLayerForGatesAndWalls, this)();
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::rebuildTileLogicLayerForKeeps, this)();
this->pathLinkageKeepWasUpdatedUnk = 1;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageForGatesKeepsSiegeTowers, this)();
if (receivedMapVersion != packagerMapVersion) {
if ((int)receivedMapVersion < 0x67) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
}
if ((int)receivedMapVersion < 0x74) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings, this)();
}
if ((int)receivedMapVersion < 0x77) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
}
if ((int)receivedMapVersion < 0x79) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField1)();
}
if ((int)receivedMapVersion < 0x82) {
MACRO_CALL(OpenSHC::Map::Version_Func::SetDairyCheeseToZero)();
}
if ((int)receivedMapVersion < 0x85) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeTowerLogicLayer)();
}
if ((int)receivedMapVersion < 0x8c) {
MACRO_CALL(OpenSHC::Map::Version_Func::SetHovelBuildOrder)();
}
if ((int)receivedMapVersion < 0x8f) {
MACRO_CALL(OpenSHC::Map::Version_Func::SetBuildingsEmployeeCountToValue)();
}
if ((int)receivedMapVersion < 0x92) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField2)();
}
if ((int)receivedMapVersion < 0x95) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeSolitaryMapBuildingField3)();
}
if ((int)receivedMapVersion < 0x96) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeLogicAndDisplayLayerForDairyFarms)();
}
if ((int)receivedMapVersion < 0x97) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeDestroyDrawbridgesInFirst10Buildings)();
}
if ((int)receivedMapVersion < 0x98) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradePitchDitchBuildingIntoPitchDitchObject)();
}
if ((int)receivedMapVersion < 0x9c) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField4)();
}
if ((int)receivedMapVersion < 0xa1) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeClearBuildings1000AndHigher)();
}
if ((int)receivedMapVersion < 0xa7) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeKnightsAndStables)();
}
if ((int)receivedMapVersion < 0xac) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeOutpostField)();
}
}
return;
}


}
}
}