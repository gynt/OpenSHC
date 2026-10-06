#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_00ed316c.hpp"
#include "OpenSHC/Globals/DAT_00ed3170.hpp"
#include "OpenSHC/Globals/DAT_00ed317c.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00453B00
void Rendering::BlitMapImageWithVerticalClip()
{
    undefined2 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    void* pvVar4;
    int iVar5;
    uint uVar6;
    undefined4* puVar7;
    undefined2* puVar8;
    ushort* puVar9;
    undefined2* puVar10;
    undefined2* puVar11;
    int local_1c;
    int local_10;
    int local_8;
    pvVar4 = DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    uVar6 = (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9 + DAT_RenderMap_DrawSomeY::instance;
    iVar5 = DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height + -7;
    local_1c = 0;
    local_8 = 0;
    if (DAT_00ed3170::instance < 1) {}
    if ((int)uVar6 < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
        local_1c = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - uVar6;
        local_8 = (DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - iVar5) - uVar6;
        DAT_00ed3170::instance = DAT_00ed3170::instance - local_1c;
        iVar5 = iVar5 - local_1c;
        local_1c = local_1c * 0x3c;
        uVar6 = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
    }
    if (DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end <= (int)(DAT_00ed3170::instance + uVar6)) {
        DAT_00ed3170::instance = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - uVar6;
        iVar5 = iVar5
            + ((DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - DAT_00ed3170::instance) - uVar6);
    }
    local_10 = DAT_00ed3170::instance;
    if (iVar5 < 1) {
        local_8 = local_8 * 0x3c;
        local_10 = 0;
    } else if (iVar5 < DAT_00ed3170::instance) {
        DAT_00ed3170::instance = DAT_00ed3170::instance - iVar5;
        local_8 = 0;
        local_10 = iVar5;
    } else {
        DAT_00ed3170::instance = 0;
    }
    iVar5 = DAT_GMImageOffsets::instance[DAT_00ed316c::instance];
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        local_1c = local_1c + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
        puVar9 = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame + DAT_RenderMap_DrawSomeX::instance
            + uVar6 * 0xfd8;
        if (local_10 < 1)
            goto LAB_00453db7;
        while (true) {
            puVar7 = (undefined4*)((int)pvVar4 + local_1c);
            if (DAT_00ed317c::instance == 1) {
                do {
                    uVar2 = puVar7[8];
                    *(undefined4*)(puVar9 + 0x6ef6) = puVar7[7];
                    *(undefined4*)(puVar9 + 0x5f20) = uVar2;
                    uVar2 = puVar7[10];
                    uVar3 = puVar7[0xb];
                    *(undefined4*)(puVar9 + 0x4f4a) = puVar7[9];
                    *(undefined4*)(puVar9 + 0x3f74) = uVar2;
                    *(undefined4*)(puVar9 + 0x2f9e) = uVar3;
                    uVar2 = puVar7[0xd];
                    uVar3 = puVar7[0xe];
                    *(undefined4*)(puVar9 + 0x1fc8) = puVar7[0xc];
                    *(undefined4*)(puVar9 + 0xff2) = uVar2;
                    *(undefined4*)(puVar9 + 0x1c) = uVar3;
                    puVar7 = puVar7 + 0xf;
                    puVar9 = puVar9 + 0xfd8;
                    local_10 = local_10 + -1;
                } while (0 < local_10);
            } else if (DAT_00ed317c::instance == 2) {
                do {
                    uVar2 = puVar7[1];
                    uVar3 = puVar7[2];
                    *(undefined4*)puVar9 = *puVar7;
                    *(undefined4*)(puVar9 + 0xfda) = uVar2;
                    *(undefined4*)(puVar9 + 0x1fb4) = uVar3;
                    uVar2 = puVar7[4];
                    uVar3 = puVar7[5];
                    *(undefined4*)(puVar9 + 0x2f8e) = puVar7[3];
                    *(undefined4*)(puVar9 + 0x3f68) = uVar2;
                    *(undefined4*)(puVar9 + 0x4f42) = uVar3;
                    uVar2 = puVar7[7];
                    *(undefined4*)(puVar9 + 0x5f1c) = puVar7[6];
                    *(undefined4*)(puVar9 + 0x6ef6) = uVar2;
                    puVar7 = puVar7 + 0xf;
                    puVar9 = puVar9 + 0xfd8;
                    local_10 = local_10 + -1;
                } while (0 < local_10);
            } else if (DAT_00ed317c::instance == 3) {
                do {
                    *(undefined4*)(puVar9 + 0x6ef6) = puVar7[7];
                    puVar7 = puVar7 + 0xf;
                    puVar9 = puVar9 + 0xfd8;
                    local_10 = local_10 + -1;
                } while (0 < local_10);
            } else {
                do {
                    uVar2 = puVar7[1];
                    uVar3 = puVar7[2];
                    *(undefined4*)puVar9 = *puVar7;
                    *(undefined4*)(puVar9 + 0xfda) = uVar2;
                    *(undefined4*)(puVar9 + 0x1fb4) = uVar3;
                    uVar2 = puVar7[4];
                    uVar3 = puVar7[5];
                    *(undefined4*)(puVar9 + 0x2f8e) = puVar7[3];
                    *(undefined4*)(puVar9 + 0x3f68) = uVar2;
                    *(undefined4*)(puVar9 + 0x4f42) = uVar3;
                    uVar2 = puVar7[7];
                    uVar3 = puVar7[8];
                    *(undefined4*)(puVar9 + 0x5f1c) = puVar7[6];
                    *(undefined4*)(puVar9 + 0x6ef6) = uVar2;
                    *(undefined4*)(puVar9 + 0x5f20) = uVar3;
                    uVar2 = puVar7[10];
                    uVar3 = puVar7[0xb];
                    *(undefined4*)(puVar9 + 0x4f4a) = puVar7[9];
                    *(undefined4*)(puVar9 + 0x3f74) = uVar2;
                    *(undefined4*)(puVar9 + 0x2f9e) = uVar3;
                    uVar2 = puVar7[0xd];
                    uVar3 = puVar7[0xe];
                    *(undefined4*)(puVar9 + 0x1fc8) = puVar7[0xc];
                    *(undefined4*)(puVar9 + 0xff2) = uVar2;
                    *(undefined4*)(puVar9 + 0x1c) = uVar3;
                    puVar7 = puVar7 + 0xf;
                    puVar9 = puVar9 + 0xfd8;
                    local_10 = local_10 + -1;
                } while (0 < local_10);
            }
        LAB_00453db7:
            local_10 = DAT_00ed3170::instance;
            if (DAT_00ed3170::instance < 1)
                break;
            DAT_00ed3170::instance = 0;
            local_1c = local_8 + iVar5;
        }
    }
    local_1c = local_1c + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
    puVar10 = (undefined2*)((int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame + (uVar6 >> 1) * 0x1fb0
        + (DAT_RenderMap_DrawSomeX::instance & 0xfffffffe));
    if (local_10 < 1)
        goto LAB_00454049;
    do {
        puVar8 = (undefined2*)((int)pvVar4 + local_1c);
        puVar11 = puVar10;
        if (DAT_00ed317c::instance == 1) {
            do {
                while ((uVar6 & 1)) {
                    puVar10 = puVar11 + 0xfd8;
                    uVar1 = puVar8[0x12];
                    puVar11[0x3f67] = puVar8[0xe];
                    puVar11[0x2f91] = uVar1;
                    uVar1 = puVar8[0x1a];
                    puVar11[0x1fbb] = puVar8[0x16];
                    puVar11[0xfe5] = uVar1;
                    puVar8 = puVar8 + 0x1e;
                    uVar6 = uVar6 + 1;
                    local_10 = local_10 + -1;
                    puVar11 = puVar10;
                    if (local_10 < 1)
                        goto LAB_00454049;
                }
                uVar1 = puVar8[0x14];
                puVar11[0x2f90] = puVar8[0x10];
                puVar11[0x1fba] = uVar1;
                uVar1 = puVar8[0x1c];
                puVar11[0xfe4] = puVar8[0x18];
                puVar11[0xe] = uVar1;
                puVar8 = puVar8 + 0x1e;
                uVar6 = uVar6 + 1;
                local_10 = local_10 + -1;
                puVar10 = puVar11;
            } while (0 < local_10);
        } else if (DAT_00ed317c::instance == 2) {
            do {
                while ((uVar6 & 1)) {
                    uVar1 = puVar8[6];
                    puVar11[0xfd9] = puVar8[2];
                    puVar11[0x1fb3] = uVar1;
                    uVar1 = puVar8[0xe];
                    puVar11[0x2f8d] = puVar8[10];
                    puVar11[0x3f67] = uVar1;
                    puVar8 = puVar8 + 0x1e;
                    uVar6 = uVar6 + 1;
                    local_10 = local_10 + -1;
                    puVar10 = puVar11 + 0xfd8;
                    puVar11 = puVar11 + 0xfd8;
                    if (local_10 < 1)
                        goto LAB_00454049;
                }
                uVar1 = puVar8[4];
                *puVar11 = *puVar8;
                puVar11[0xfda] = uVar1;
                uVar1 = puVar8[0xc];
                puVar11[0x1fb4] = puVar8[8];
                puVar11[0x2f8e] = uVar1;
                puVar8 = puVar8 + 0x1e;
                uVar6 = uVar6 + 1;
                local_10 = local_10 + -1;
                puVar10 = puVar11;
            } while (0 < local_10);
        } else if (DAT_00ed317c::instance == 3) {
            do {
                while ((uVar6 & 1)) {
                    puVar11[0x3f67] = puVar8[0xe];
                    puVar8 = puVar8 + 0x1e;
                    uVar6 = uVar6 + 1;
                    local_10 = local_10 + -1;
                    puVar10 = puVar11 + 0xfd8;
                    puVar11 = puVar11 + 0xfd8;
                    if (local_10 < 1)
                        goto LAB_00454049;
                }
                puVar8 = puVar8 + 0x1e;
                uVar6 = uVar6 + 1;
                local_10 = local_10 + -1;
                puVar10 = puVar11;
            } while (0 < local_10);
        } else {
            do {
                while ((uVar6 & 1)) {
                    uVar1 = puVar8[6];
                    puVar11[0xfd9] = puVar8[2];
                    puVar11[0x1fb3] = uVar1;
                    uVar1 = puVar8[0xe];
                    puVar11[0x2f8d] = puVar8[10];
                    puVar11[0x3f67] = uVar1;
                    uVar1 = puVar8[0x16];
                    puVar11[0x2f91] = puVar8[0x12];
                    puVar11[0x1fbb] = uVar1;
                    puVar11[0xfe5] = puVar8[0x1a];
                    puVar8 = puVar8 + 0x1e;
                    uVar6 = uVar6 + 1;
                    local_10 = local_10 + -1;
                    puVar10 = puVar11 + 0xfd8;
                    puVar11 = puVar11 + 0xfd8;
                    if (local_10 < 1)
                        goto LAB_00454049;
                }
                uVar1 = puVar8[4];
                *puVar11 = *puVar8;
                puVar11[0xfda] = uVar1;
                uVar1 = puVar8[0xc];
                puVar11[0x1fb4] = puVar8[8];
                puVar11[0x2f8e] = uVar1;
                uVar1 = puVar8[0x14];
                puVar11[0x2f90] = puVar8[0x10];
                puVar11[0x1fba] = uVar1;
                uVar1 = puVar8[0x1c];
                puVar11[0xfe4] = puVar8[0x18];
                puVar11[0xe] = uVar1;
                puVar8 = puVar8 + 0x1e;
                uVar6 = uVar6 + 1;
                local_10 = local_10 + -1;
                puVar10 = puVar11;
            } while (0 < local_10);
        }
    LAB_00454049:
        local_10 = DAT_00ed3170::instance;
        if (DAT_00ed3170::instance < 1) {}
        DAT_00ed3170::instance = 0;
        local_1c = local_8 + iVar5;
    } while (true);
}

}
