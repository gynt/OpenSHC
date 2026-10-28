#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/currentlyRenderedGmID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E26D0
    void ViewportRenderState::scheduleUnitForBatchedRendering(undefined4 unitIDOrStatus, undefined4 drawX,
        undefined4 drawY, undefined4 imageID, undefined4 blendStrength, undefined4 gmID, int param_7)
    {
        int batch;
        if (param_7 == 1) {
            batch = this->unitBatchedRenderCounterUntil6 + 4;
            if (5 < batch) {
                batch = batch - 5;
            }
        } else {
            batch = this->unitBatchedRenderCounterUntil6;
            if (param_7 == 2) {
                batch = this->unitBatchedRenderCounterUntil6 + 3;
                if (5 < batch) {
                    batch = batch - 5;
                }
            }
        }

        switch (batch) {
        case 1:
            if (this->unitRender1 < 500) {
                this->unitBatch1[this->unitRender1].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch1[this->unitRender1].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch1[this->unitRender1].spriteID = currentlyRenderedGmID::instance;
                this->unitBatch1[this->unitRender1].drawX = drawX;
                this->unitBatch1[this->unitRender1].drawY = drawY;
                this->unitBatch1[this->unitRender1].imageIDOrWidth = imageID;
                this->unitBatch1[this->unitRender1].blendOrHeight = blendStrength;
                this->unitBatch1[this->unitRender1].gmIDOrPixelPtr = gmID;
                this->unitRender1 = this->unitRender1 + 1;
            }
            break;
        case 2:
            if (this->unitRender2 < 500) {
                this->unitBatch2[this->unitRender2].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch2[this->unitRender2].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch2[this->unitRender2].spriteID = currentlyRenderedGmID::instance;
                this->unitBatch2[this->unitRender2].drawX = drawX;
                this->unitBatch2[this->unitRender2].drawY = drawY;
                this->unitBatch2[this->unitRender2].imageIDOrWidth = imageID;
                this->unitBatch2[this->unitRender2].blendOrHeight = blendStrength;
                this->unitBatch2[this->unitRender2].gmIDOrPixelPtr = gmID;
                this->unitRender2 = this->unitRender2 + 1;
            }
            break;
        case 3:
            if (this->unitRender3 < 500) {
                this->unitBatch3[this->unitRender3].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch3[this->unitRender3].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch3[this->unitRender3].spriteID = currentlyRenderedGmID::instance;
                this->unitBatch3[this->unitRender3].drawX = drawX;
                this->unitBatch3[this->unitRender3].drawY = drawY;
                this->unitBatch3[this->unitRender3].imageIDOrWidth = imageID;
                this->unitBatch3[this->unitRender3].blendOrHeight = blendStrength;
                this->unitBatch3[this->unitRender3].gmIDOrPixelPtr = gmID;
                this->unitRender3 = this->unitRender3 + 1;
            }
            break;
        case 4:
            if (this->unitRender4 < 500) {
                this->unitBatch4[this->unitRender4].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch4[this->unitRender4].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch4[this->unitRender4].spriteID = currentlyRenderedGmID::instance;
                this->unitBatch4[this->unitRender4].drawX = drawX;
                this->unitBatch4[this->unitRender4].drawY = drawY;
                this->unitBatch4[this->unitRender4].imageIDOrWidth = imageID;
                this->unitBatch4[this->unitRender4].blendOrHeight = blendStrength;
                this->unitBatch4[this->unitRender4].gmIDOrPixelPtr = gmID;
                this->unitRender4 = this->unitRender4 + 1;
            }
            break;
        case 5:
            if (this->unitRender5 < 500) {
                this->unitBatch5[this->unitRender5].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch5[this->unitRender5].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch5[this->unitRender5].spriteID = currentlyRenderedGmID::instance;
                this->unitBatch5[this->unitRender5].drawX = drawX;
                this->unitBatch5[this->unitRender5].drawY = drawY;
                this->unitBatch5[this->unitRender5].imageIDOrWidth = imageID;
                this->unitBatch5[this->unitRender5].blendOrHeight = blendStrength;
                this->unitBatch5[this->unitRender5].gmIDOrPixelPtr = gmID;
                this->unitRender5 = this->unitRender5 + 1;
            }
            break;
        }
    }

}
}
