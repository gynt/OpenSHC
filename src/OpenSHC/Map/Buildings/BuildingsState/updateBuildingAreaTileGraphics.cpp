#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040EFD0
ushort * BuildingsState::updateBuildingAreaTileGraphics(int param_1)

{
int iVar1;
int iVar2;
ushort *puVar3;
int iVar4;
int *piVar5;

piVar5 = &this->buildings[param_1].tileRef5;
iVar4 = 0x17;
do {
iVar1 = *piVar5;
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getRubbleGraphicStageForDamageLevel, DAT_TileMapState::ptr)((int)(char)DAT_TileMapState::instance.DamageLayer[iVar1]);
puVar3 = (ushort *)(GMTotalPicturesProcessed::instance[0xe] + 0x37 + iVar2);
if (puVar3 != (ushort *)(uint)DAT_TileMapState::instance.GfxLayer[iVar1]) {
DAT_TileMapState::instance.GfxLayer[iVar1] = (ushort)puVar3;
DAT_TileMapState::instance.MiscDisplayLayer[iVar1] = DAT_TileMapState::instance.MiscDisplayLayer[iVar1] &0xfff3;
puVar3 = DAT_TileMapState::instance.MiscDisplayLayer + iVar1;
}
piVar5 = piVar5 + 1;
iVar4 = iVar4 + -1;
} while (iVar4 != 0);
return puVar3;
}


}
}
}