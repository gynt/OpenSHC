#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DC140
    undefined4 Helpers::FindCampaignMapHotspotAtMouse()
    {
        CreditsRelatedStructure* pCVar1;
        int iVar2;
        iVar2 = 0;
        pCVar1 = DAT_ARRAY_00ec0348::instance;
        do {
            if ((pCVar1->isValid == 3) || (pCVar1->isValid == 1)) {
                if ((pCVar1->ySpace <= DAT_MouseState::instance.screenSpaceX
                            - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth)
                    && (DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < pCVar1->someY + pCVar1->ySpace)) {
                    if ((pCVar1->someX <= DAT_MouseState::instance.screenSpaceY
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight)
                        && (DAT_MouseState::instance.screenSpaceY
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                            < pCVar1->field5_0x14 + pCVar1->someX)) {
                        return (undefined4)(DAT_ARRAY_00ec0348::instance[iVar2].xSpace);
                    }
                }
            }
            pCVar1 = pCVar1 + 1;
            iVar2 = iVar2 + 1;
            if (0xec0827 < (int)pCVar1) {
                return (undefined4)(0xffffffff);
            }
        } while (true);
    }

}
}
