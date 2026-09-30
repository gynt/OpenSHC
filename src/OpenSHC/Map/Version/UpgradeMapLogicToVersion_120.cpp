#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005014F0
    void Version::UpgradeMapLogicToVersion_120()
    {
        short sVar1;
        uint uVar2;
        byte bVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        uint uVar7;
        int _tile;
        int iVar8;
        _tile = 0;
        do {
            bVar3 = DAT_TileMapState::instance.HeightLayer[_tile];
            DAT_TileMapState::instance.DefaultHeightLayer[_tile] = bVar3;
            uVar2 = DAT_TileMapState::instance.LogicLayer[_tile];
            if ((uVar2 & 0x200) == 0) {
                if ((uVar2 & 0x800) == 0) {
                    if ((uVar2 & 0x100) != 0) {
                        bVar3 = bVar3 + 0xa6;
                        goto LAB_005016a8;
                    }
                } else {
                    sVar1 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                    iVar8 = 0;
                    iVar4 = 0;
                    iVar6 = 0;
                    do {
                        iVar5 = iVar6;
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix
                                    [sVar1][DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[iVar5]]
                            + iVar5;
                        uVar2 = DAT_TileMapState::instance.LogicLayer[iVar6];
                        if ((uVar2 & 0x800) == 0) {
                            uVar7 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6];
                            if ((uVar2 & 0x200) == 0) {
                                if ((uVar2 & 0x100) == 0) {
                                    iVar4 = iVar4 + uVar7;
                                } else {
                                    iVar4 = iVar4 + -0x5a + uVar7;
                                }
                            } else {
                                iVar4 = iVar4 + -0x62 + uVar7;
                            }
                            iVar8 = iVar8 + 1;
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix
                                    [sVar1][DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[iVar5 + 1]];
                        uVar2 = DAT_TileMapState::instance.LogicLayer[iVar5 + iVar6 + 1];
                        if ((uVar2 & 0x800) == 0) {
                            uVar7 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6 + 1 + iVar5];
                            if ((uVar2 & 0x200) == 0) {
                                if ((uVar2 & 0x100) == 0) {
                                    iVar4 = iVar4 + uVar7;
                                } else {
                                    iVar4 = iVar4 + -0x5a + uVar7;
                                }
                            } else {
                                iVar4 = iVar4 + -0x62 + uVar7;
                            }
                            iVar8 = iVar8 + 1;
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix
                                    [sVar1][DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[iVar5 + 2]];
                        uVar2 = DAT_TileMapState::instance.LogicLayer[iVar5 + iVar6 + 2];
                        if ((uVar2 & 0x800) == 0) {
                            uVar7 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6 + 2 + iVar5];
                            if ((uVar2 & 0x200) == 0) {
                                if ((uVar2 & 0x100) == 0) {
                                    iVar4 = iVar4 + uVar7;
                                } else {
                                    iVar4 = iVar4 + -0x5a + uVar7;
                                }
                            } else {
                                iVar4 = iVar4 + -0x62 + uVar7;
                            }
                            iVar8 = iVar8 + 1;
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix
                                    [sVar1][DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[iVar5 + 3]];
                        uVar2 = DAT_TileMapState::instance.LogicLayer[iVar5 + iVar6 + 3];
                        if ((uVar2 & 0x800) == 0) {
                            uVar7 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6 + 3 + iVar5];
                            if ((uVar2 & 0x200) == 0) {
                                if ((uVar2 & 0x100) == 0) {
                                    iVar4 = iVar4 + uVar7;
                                } else {
                                    iVar4 = iVar4 + -0x5a + uVar7;
                                }
                            } else {
                                iVar4 = iVar4 + -0x62 + uVar7;
                            }
                            iVar8 = iVar8 + 1;
                        }
                        iVar6 = iVar5 + 4;
                    } while (iVar5 + 4 < 8);
                    if (iVar8 == 0) {
                        DAT_TileMapState::instance.DefaultHeightLayer[iVar5 + 4] = 8;
                    } else {
                        DAT_TileMapState::instance.DefaultHeightLayer[iVar5 + 4] = (byte)(iVar4 / iVar8);
                    }
                }
            } else {
                bVar3 = bVar3 + 0x9e;
            LAB_005016a8:
                DAT_TileMapState::instance.DefaultHeightLayer[_tile] = bVar3;
            }
            _tile = _tile + 1;
            if (0x13a0f < _tile) {}
        } while (true);
    }

}
}
