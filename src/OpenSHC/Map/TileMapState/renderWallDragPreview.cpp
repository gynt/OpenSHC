#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8BD0
    void TileMapState::renderWallDragPreview(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command)
    {
        bool bVar1;
        ushort uVar2;
        int iVar3;
        int iVar4;
        uint uVar5;
        int iVar6;
        uint uVar7;
        int* local_14;
        int local_10;
        int local_c;
        uint local_8;
        int local_4;
        local_4 = 0;
        if ((((x1 < 400) && (y1 < 400)) && (*(char*)(y1 * 400 + 0x21aec98 + x1) != '\0'))
            && (((x2 < 400 && (y2 < 400)) && (*(char*)(x2 + 0x21aec98 + y2 * 400) != '\0')))) {
            this->DAT_WallTileCountCurrentDrag = 0;
            local_c = 2;
            if (((short)command == 0x1b) && (local_4 = this->maxWallHeightInPath, !this->field118_0x554920)) {
                this->ConstructionGFXLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1]
                    = (short)GMTotalPicturesProcessed::instance[6] + 0x13;
            }
            iVar4 = y1 - y2;
            local_10 = y2 - y1;
            local_8 = x1;
            uVar5 = x2 - x1;
            local_14 = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
            uVar7 = y1;
            x1 = x1 - x2;
            y1 = uVar5;
            do {
                if ((((short)command == 0x1b) && (local_4 < 0x18))
                    || (((iVar6 = *local_14 + local_8, (short)command == 0x1b && ((this->LogicLayer[iVar6] & 0x100U)))
                        || (this->constructionTileCount <= this->DAT_WallTileCountCurrentDrag))))
                    break;
                bVar1 = false;
                if (((short)command == 0x19) && ((this->LogicLayer[iVar6] & 0x200U))) {
                    bVar1 = true;
                }
                if ((!(this->LogicLayer[iVar6] & 0x100U)) || (this->DamageLayer[iVar6] != 0)) {
                    iVar3 = this->DAT_WallTileCountCurrentDrag + 1;
                    if (bVar1)
                        goto LAB_004f8d6c;
                LAB_004f8d75:
                    this->DAT_WallTileCountCurrentDrag = iVar3;
                    if (!this->illegalBuild) {
                        if ((short)command == 0x19) {
                            this->ConstructionGFXLayer[iVar6] = (ushort)GMTotalPicturesProcessed::instance[6];
                        } else {
                            if ((short)command == 0x2e) {
                                uVar2 = (ushort)GMTotalPicturesProcessed::instance[6] + 1;
                                goto LAB_004f8e61;
                            }
                            if ((short)command == 0x1a) {
                                this->ConstructionGFXLayer[iVar6] = (ushort)GMTotalPicturesProcessed::instance[6] + 4;
                            } else if ((short)command == 0x1b) {
                                iVar3 = local_4 - (uint)this->HeightLayer[iVar6];
                                iVar3 = ((int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3) + -1;
                                if (0 < iVar3) {
                                    if (10 < iVar3) {
                                        iVar3 = 10;
                                    }
                                    uVar2 = (short)iVar3 + 8 + (ushort)GMTotalPicturesProcessed::instance[6];
                                    goto LAB_004f8e61;
                                }
                                this->DAT_WallTileCountCurrentDrag = this->DAT_WallTileCountCurrentDrag + -1;
                            }
                        }
                    } else if ((short)command == 0x19) {
                        this->ConstructionGFXLayer[iVar6] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                    } else if ((short)command == 0x2e) {
                        uVar2 = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                    LAB_004f8e61:
                        this->ConstructionGFXLayer[iVar6] = uVar2;
                    } else if ((short)command == 0x1a) {
                        this->ConstructionGFXLayer[iVar6] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x14;
                    } else if ((short)command == 0x1b) {
                        uVar2 = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                        goto LAB_004f8e61;
                    }
                } else if (bVar1) {
                LAB_004f8d6c:
                    iVar3 = this->DAT_WallTileCountCurrentDrag;
                    goto LAB_004f8d75;
                }
                uVar5 = x1;
                if ((int)local_8 < (int)x2) {
                    uVar5 = y1;
                }
                iVar6 = iVar4;
                if ((int)uVar7 < (int)y2) {
                    iVar6 = local_10;
                }
                if ((short)command == 0x1b) {
                    if (iVar6 < (int)uVar5) {
                        if ((int)local_8 < (int)x2) {
                            x1 = x1 + 1;
                            local_8 = local_8 + 1;
                            y1 = y1 - 1;
                        } else {
                            x1 = x1 - 1;
                            local_8 = local_8 - 1;
                            y1 = y1 + 1;
                        }
                    } else {
                        if (iVar6 < 1)
                            goto LAB_004f8f54;
                        if ((int)uVar7 < (int)y2) {
                            local_14 = local_14 + 3;
                            uVar7 = uVar7 + 1;
                            iVar4 = iVar4 + 1;
                            local_10 = local_10 + -1;
                        } else {
                            local_14 = local_14 + -3;
                            uVar7 = uVar7 - 1;
                            iVar4 = iVar4 + -1;
                            local_10 = local_10 + 1;
                        }
                    }
                } else {
                    if (uVar5) {
                        if ((int)local_8 < (int)x2) {
                            x1 = x1 + 1;
                            local_8 = local_8 + 1;
                            y1 = y1 - 1;
                        } else {
                            x1 = x1 - 1;
                            local_8 = local_8 - 1;
                            y1 = y1 + 1;
                        }
                    }
                    if (iVar6) {
                        if ((int)uVar7 < (int)y2) {
                            local_14 = local_14 + 3;
                            uVar7 = uVar7 + 1;
                            iVar4 = iVar4 + 1;
                            local_10 = local_10 + -1;
                        } else {
                            local_14 = local_14 + -3;
                            uVar7 = uVar7 - 1;
                            iVar4 = iVar4 + -1;
                            local_10 = local_10 + 1;
                        }
                    }
                    if ((local_8 == x2) && (uVar7 == y2)) {
                    LAB_004f8f54:
                        local_c = local_c + -1;
                    }
                }
                if ((0x10 < local_4) && (local_c == 2)) {
                    local_4 = local_4 + -0x10;
                }
            } while (((local_8 != x2) || (uVar7 != y2)) || (local_c));
            if (this->illegalBuild) {
                this->DAT_WallTileCountCurrentDrag = 0;
            }
            if (!this->wallDragButtonUp) {
                if ((short)command == 0x2e) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                        DAT_BuildingsState::ptr)(playerID, 0, this->DAT_WallTileCountCurrentDrag, 1);
                }
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                    DAT_BuildingsState::ptr)(playerID, this->DAT_WallTileCountCurrentDrag, 0, 1);
            }
        }
    }

}
}
