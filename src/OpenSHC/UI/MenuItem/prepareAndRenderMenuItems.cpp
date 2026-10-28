#include "../MenuItem.func.hpp"

#include "OpenSHC/UI/Enums/MenuItemRenderFunctionType.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonDisabled.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemRenderFunctionType;
    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F49D0
    void MenuItem::prepareAndRenderMenuItems()
    {
        int* piVar1;
        int* piVar2;
        MenuItemRenderFunctionTypeInt MVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        if (this->isDeactivatedInUCLayout == 0) {
            if (this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_GM_DATA_IMAGE) {
                iVar7 = GMFirstPictureIndex::instance[DAT_UIButtonDefinedData::instance
                        .ButtonGmDataArray[(this->firstItemTypeData).gmDataIndex]
                        .gmId_0x0];
                iVar5 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[(this->firstItemTypeData).gmDataIndex]
                            .pictureInGm_0x4;
                this->itemWidth = (int)DAT_GMImageHeaders::instance.imh[iVar5 + iVar7 + -1].width;
                this->itemHeight = (int)DAT_GMImageHeaders::instance.imh[iVar5 + iVar7 + -1].height;
            }
            DAT_ButtonX::instance
                = (this->menuPointer->xPosition - this->menuPointer->currentBuildMenuButtonShift)
                + (this->position).position.x;
            DAT_ButtonY::instance = this->menuPointer->yPosition + (this->position).position.y;
            DAT_ButtonW::instance = this->itemWidth;
            DAT_ButtonH::instance = this->itemHeight;
            DAT_CurrentButtonGmDataIndex::instance = (this->firstItemTypeData).gmDataIndex & 0x7fffff;
            DAT_ButtonCurrentlyInteracting::instance = (BOOLEnum)(short)(this->clicked | this->hovering);
            DAT_ButtonBlendStrength::instance = 0;
            DAT_ButtonDisabled::instance = (int)this->isHidden;
            if (DAT_GameCore::instance.menuFadeInProgress != 0) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            iVar7 = this->menuPointer->currentBuildMenuButtonShift;
            if (iVar7 != 0) {
                iVar5 = (this->position).position.x;
                if (iVar5 - iVar7 < (int)DAT_MenuHandlerState::instance.buildMenuClipLeft) {
                    DAT_ButtonBlendStrength::instance = 0;
                }
                if ((int)DAT_MenuHandlerState::instance.buildMenuClipRight < (iVar5 - iVar7) + this->itemWidth) {
                    DAT_ButtonBlendStrength::instance = 0;
                }
                if ((0x2d < DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38)
                    && (DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38 < 0x37)) {
                    DAT_ButtonBlendStrength::instance = 0;
                }
                if (DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38 < 0x32) {
                    DAT_ButtonBlendStrength::instance
                        = (DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38 * 0x20) / 0x2d;
                } else {
                    DAT_ButtonBlendStrength::instance
                        = ((100 - DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38) * 0x20) / 0x2d;
                }
            }
            MVar3 = this->menuItemRenderFunctionType;
            if (MVar3 == OpenSHC::UI::Enums::MIRFT_SLIDER_OR_SCROLLBAR) {
                if (this->menuPointer->isFirstFrame != 0) {
                    piVar1 = &(this->secondItemTypeData).buttonState.repeatCountOrValue;
                    piVar2 = &(this->secondItemTypeData).buttonState.clickTimeOrMaxValue;
                    (*(this->menuItemActionHandler).slider)(
                        (this->callbackParameter).parameter, 1, (int*)&this->secondItemTypeData, piVar2, piVar1);
                    iVar7 = (this->secondItemTypeData).buttonState.lastRepeatTimeOrMinValue;
                    (this->secondItemTypeData).buttonState.pictureOrDragOffset = -1000;
                    if (*piVar1 < iVar7) {
                        *piVar1 = iVar7;
                    }
                    iVar7 = *piVar2;
                    if (iVar7 < *piVar1) {
                        *piVar1 = iVar7;
                    }
                }
                iVar7 = this->itemWidth;
                iVar5 = 0;
                if ((this->menuItemType & OpenSHC::UI::Enums::MIT_TYPE_ID_MASK)
                    == OpenSHC::UI::Enums::MIT_VERTICAL_SCROLLBAR) {
                    iVar7 = this->itemHeight;
                }
                iVar4 = (this->secondItemTypeData).buttonState.lastRepeatTimeOrMinValue;
                iVar8 = (this->secondItemTypeData).buttonState.clickTimeOrMaxValue - iVar4;
                iVar6 = iVar7;
                if (0 < iVar8) {
                    iVar6 = iVar7 / (iVar8 + 1);
                    if (iVar6 <= (this->firstItemTypeData).itemsToSkip) {
                        iVar6 = (this->firstItemTypeData).itemsToSkip;
                    }
                    iVar5 = (((this->secondItemTypeData).buttonState.repeatCountOrValue - iVar4) * (iVar7 - iVar6)) / iVar8;
                }
                (*(this->menuItemRenderFunction).slider)((this->callbackParameter).parameter, iVar5,
                    (this->secondItemTypeData).buttonState.repeatCountOrValue, iVar6,
                    -1000 < (this->secondItemTypeData).buttonState.pictureOrDragOffset);
            } else if (MVar3 == OpenSHC::UI::Enums::MIRFT_SIMPLE_RENDER) {
                (*(this->menuItemRenderFunction).simple)((this->callbackParameter).parameter);
            } else if (MVar3 == OpenSHC::UI::Enums::MIRFT_GM_DATA_IMAGE) {
                (*(this->menuItemRenderFunction).gmDataImage)((this->callbackParameter).parameter);
                (this->secondItemTypeData).buttonState.pictureOrDragOffset
                    = DAT_CurrentButtonPictureInGm::instance;
            }
            if ((this->menuPointer->hoveredItem == this)
                && (DAT_ButtonCurrentlyInteracting::instance != (int)(short)(this->clicked | this->hovering))) {
                this->menuPointer->tooltipState = 0;
            }
            this->isHidden = (short)DAT_ButtonDisabled::instance;
        }
    }

}
}
