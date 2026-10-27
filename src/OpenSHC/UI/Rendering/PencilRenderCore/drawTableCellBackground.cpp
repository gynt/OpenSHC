#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004692E0
        void PencilRenderCore::drawTableCellBackground(BOOLEnum isSelected, int indexToGetStripes, int blendStrength)
        {
            int iVar1;
            uint imageID;
            iVar1 = DAT_ButtonX::instance;
            imageID = ((int)(char)indexToGetStripes & 1U) * 2 | 0x45;
            if (isSelected == FALSE) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    if ((int)(DAT_ButtonW::instance + DAT_ButtonX::instance) <= (int)DAT_ButtonX::instance) {
                        return; // 0x46945A jge (signed) -> 0x46949C ret
                    }
                    iVar1 = DAT_ButtonX::instance;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                            (int)((int)(imageID)), iVar1, (int)((int)(DAT_ButtonY::instance)),
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, (int)((int)(imageID + 1)), blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < (int)(DAT_ButtonW::instance + DAT_ButtonX::instance)); // 0x469496 jl
                    return; // 0x46949C ret
                }
                if ((int)DAT_ButtonW::instance < 0x15) { // 0x4693A9 jle (signed)
                    DAT_ButtonW::instance = DAT_ButtonW::instance + 1;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x49,
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4c, blendStrength);
                    iVar1 = iVar1 + 0x14;
                }
                if (iVar1 < (int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)) { // 0x4693EA jge
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4a, iVar1,
                            (int)((int)(DAT_ButtonY::instance)), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d,
                            blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < (int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance));
                }
            } else {
                if ((int)DAT_ButtonW::instance < 0x15) { // 0x46930E jle (signed)
                    DAT_ButtonW::instance = DAT_ButtonW::instance + 1;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x49,
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4c, blendStrength);
                    iVar1 = iVar1 + 0x14;
                }
                if (iVar1 < (int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)) { // 0x46934E jge
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4a, iVar1,
                            (int)((int)(DAT_ButtonY::instance)), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d,
                            blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < (int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance));
                }
            }
            if ((int)DAT_ButtonW::instance < 0x16) {
                return; // 0x469429 jle (signed) -> 0x46949C ret
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4b, iVar1,
                (int)((int)(DAT_ButtonY::instance)), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d, blendStrength);
        }

    }
}
}
