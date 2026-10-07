#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_00eb0e40.hpp"
#include "OpenSHC/Globals/DAT_00eb1234.hpp"
#include "OpenSHC/Globals/DAT_00eb9af4.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedX.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/FLOAT_00eb0e2c.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb0e30.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"


namespace OpenSHC {

using Rendering::Enums::RenderTarget;

// FUNCTION: STRONGHOLDCRUSADER 0x004E12C0
void Rendering::RenderActiveCreditsElements()
{
    float fVar1;
    float fVar2;
    int iVar3;
    int blendStrengh;
    int top;
    int iVar4;
    int left;
    CreditsRelatedStructure* piVar5;
    uint color;
    int local_4;
    if (!INT_00ed27a4::instance) {
        MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
    }
    if (INT_00ed27a4::instance == 1) {
        MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb9af4::instance, 0, 0);
    }
    if (DAT_00eb0e40::instance == 5) {
        iVar3 = (long)((double)FLOAT_00eb0e2c::instance);
        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
            DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX + -1,
            DAT_WindowAndDirectDraw::instance.resolutionY + -1, iVar3);
        FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
        if (FLOAT_00eb0e2c::instance < 16.0) {
            FLOAT_00eb0e2c::instance = 16.0;
        }
    }
    local_4 = 0;
    do {
        piVar5 = DAT_ARRAY_00ec0348::ptr[0];
        do {
            iVar3 = piVar5.isValid;
            if ((iVar3) && (piVar5->field7_0x1c == local_4)) {
                if (iVar3 == 1) {
                    iVar3 = piVar5->xSpace;
                    if (piVar5->field11_0x2c != -1) {
                        if ((piVar5->ySpace <= DAT_MouseState::instance.screenSpaceX
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth)
                            && (DAT_MouseState::instance.screenSpaceX
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                                < piVar5->someY + piVar5->ySpace)) {
                            if ((piVar5->someX <= DAT_MouseState::instance.screenSpaceY
                                        - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight)
                                && (DAT_MouseState::instance.screenSpaceY
                                        - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                                    < piVar5->field5_0x14 + piVar5->someX)) {
                                iVar3 = piVar5->field11_0x2c;
                            }
                        }
                    }
                    if (!piVar5->fadeMode) {
                        MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(iVar3, piVar5->ySpace, piVar5->someX);
                    } else {
                        iVar4 = (long)((double)piVar5->blendStrength);
                        MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(iVar3, piVar5->ySpace, piVar5->someX, iVar4);
                        fVar1 = FLOAT_Between1And5::instance;
                        if ((piVar5->fadeMode != 1)
                            || (fVar2 = piVar5->blendStrength
                                    - (FLOAT_Between1And5::instance * 0.5 + FLOAT_Between1And5::instance * 0.5),
                                piVar5->blendStrength = fVar2, 1.0 <= fVar2)) {
                            if ((piVar5->fadeMode == 2)
                                && (fVar1 = fVar1 * 0.5 + fVar1 * 0.5 + piVar5->blendStrength, piVar5->blendStrength = fVar1,
                                    31.0 < fVar1)) {
                                piVar5.isValid = 0;
                            }
                        } else {
                        LAB_004e1692:
                            piVar5->fadeMode = 0;
                        }
                    }
                } else if (iVar3 == 4) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = Rendering::Enums::RT_SCREEN_MENU;
                    if (!piVar5->fadeMode) {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                            DAT_PencilRenderCore::ptr)(
                            piVar5->ySpace + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                            piVar5->someX + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, piVar5->someY,
                            piVar5->field5_0x14);
                    } else {
                        iVar3 = (long)((double)piVar5->blendStrength);
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                            DAT_PencilRenderCore::ptr)(
                            piVar5->ySpace + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                            piVar5->someX + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, piVar5->someY,
                            piVar5->field5_0x14, iVar3);
                    }
                    fVar1 = FLOAT_Between1And5::instance;
                    if ((piVar5->fadeMode != 1)
                        || (fVar2 = piVar5->blendStrength - FLOAT_Between1And5::instance * 0.5, piVar5->blendStrength = fVar2,
                            1.0 <= fVar2)) {
                        if ((piVar5->fadeMode == 2)
                            && (fVar1 = fVar1 * 0.5 + piVar5->blendStrength, piVar5->blendStrength = fVar1, 31.0 < fVar1)) {
                            piVar5.isValid = 0;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = Rendering::Enums::RT_MAP_GAME;
                            goto LAB_004e1696;
                        }
                    } else {
                        piVar5->fadeMode = 0;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = Rendering::Enums::RT_MAP_GAME;
                } else if (iVar3 == 2) {
                    if (piVar5->field10_0x28 == 1) {
                        color = 0;
                    } else {
                        color = 0xccfaff;
                    }
                    if (!piVar5->fadeMode) {
                        MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelper)(piVar5->xSpace,
                            piVar5->ySpace, piVar5->someX, piVar5->someY, color, piVar5->field8_0x20,
                            (BOOLEnum)((int)(piVar5->field9_0x24)));
                    } else {
                        iVar3 = (long)((double)piVar5->blendStrength);
                        MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(piVar5->xSpace,
                            piVar5->ySpace, piVar5->someX, piVar5->someY, color, piVar5->field8_0x20,
                            (BOOLEnum)((int)(piVar5->field9_0x24)), iVar3);
                        fVar1 = FLOAT_Between1And5::instance;
                        if ((piVar5->fadeMode == 1)
                            && (fVar2 = piVar5->blendStrength - FLOAT_Between1And5::instance * 0.5,
                                piVar5->blendStrength = fVar2, fVar2 < 1.0))
                            goto LAB_004e1692;
                        if ((piVar5->fadeMode == 2)
                            && (fVar1 = fVar1 * 0.5 + piVar5->blendStrength, piVar5->blendStrength = fVar1, 31.0 < fVar1)) {
                            piVar5.isValid = 0;
                        }
                    }
                } else if (iVar3 == 3) {
                    iVar3 = piVar5->ySpace;
                    if ((iVar3 <= DAT_MouseState::instance.screenSpaceX
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth)
                        && (DAT_MouseState::instance.screenSpaceX
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                            < piVar5->someY + iVar3)) {
                        iVar4 = piVar5->someX;
                        if ((iVar4 <= DAT_MouseState::instance.screenSpaceY
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight)
                            && (DAT_MouseState::instance.screenSpaceY
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                                < piVar5->field5_0x14 + iVar4)) {
                            MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                                piVar5->xSpace + 1, iVar3, iVar4);
                            goto LAB_004e1696;
                        }
                    }
                    MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(piVar5->xSpace, iVar3, piVar5->someX);
                }
            }
        LAB_004e1696:
            piVar5 = piVar5 + 0xd;
        } while ((int)piVar5 < 0xec0840);
        local_4 = local_4 + 1;
        if (7 < local_4) {
            if (DWORD_00eb9ac4::instance) {
                MACRO_CALL(UI::Rendering_Func::RenderTextPageProgressBar)();
            }
            if ((DAT_00eb0e40::instance) && (DAT_00eb0e40::instance != 5)) {
                if (DAT_00eb0e40::instance < 3) {
                    blendStrengh = (long)((double)FLOAT_00eb0e2c::instance);
                    iVar3 = DAT_WindowAndDirectDraw::instance.resolutionY + -1;
                    iVar4 = DAT_WindowAndDirectDraw::instance.resolutionX + -1;
                    top = 0;
                    left = 0;
                } else {
                    blendStrengh = (long)((double)FLOAT_00eb0e2c::instance);
                    iVar3 = INT_00eb0e30::instance + DAT_RenderRelatedY::instance + -1
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    iVar4 = DAT_00eb1234::instance + DAT_RenderRelatedX::instance + -1
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    top = DAT_RenderRelatedY::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    left = DAT_RenderRelatedX::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                }
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(left, top, iVar4, iVar3, blendStrengh);
                if ((DAT_00eb0e40::instance == 1) || (DAT_00eb0e40::instance == 3)) {
                    FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance + FLOAT_Between1And5::instance * 0.5;
                    if (DAT_00eb0e40::instance == 3) {
                        FLOAT_00eb0e2c::instance = FLOAT_Between1And5::instance * 0.5 + FLOAT_00eb0e2c::instance;
                    }
                    if (31.0 < FLOAT_00eb0e2c::instance) {
                        DAT_00eb0e40::instance = 0;
                        return;
                    }
                }
                if ((DAT_00eb0e40::instance == 2) || (DAT_00eb0e40::instance == 4)) {
                    FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
                    if (DAT_00eb0e40::instance == 4) {
                        FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
                    }
                    if (FLOAT_00eb0e2c::instance < 0.0) {
                        DAT_00eb0e40::instance = 0;
                        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(0, 0);
                        return;
                    }
                }
            }
            return;
        }
    } while (true);
}

}
