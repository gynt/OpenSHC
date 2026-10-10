#include "../GreatestLord.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AE720
        void GreatestLord::MenuItemRenderFunction_GreatestLord_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int drawX;
            int drawY;
            /*
              the original branches straight off each comparison into the shared block
              (`cmp [data], ecx; je L5` at 0x4ae734) rather than materialising a flag
             */
            if (((param_1 == 0xb) && (DAT_GreatestLordDefinedData::instance.tableSortBy == 1))
                || (((param_1 == 0xc) && (DAT_GreatestLordDefinedData::instance.tableSortBy == 0))
                    || ((param_1 == 10) && (DAT_GreatestLordDefinedData::instance.tableSortBy == -1)))) {
                iVar2 = 0xe;
                if (param_1 == 0xc) {
                    iVar2 = 1;
                }
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                drawX = DAT_ButtonX::instance;
                drawY = DAT_ButtonY::instance;
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                    &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(TRUE);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    iVar1 + iVar2, drawX, drawY);
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
        }

    }
}
}
