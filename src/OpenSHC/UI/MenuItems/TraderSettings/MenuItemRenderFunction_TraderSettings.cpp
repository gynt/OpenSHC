#include "../TraderSettings.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004C1070
        void TraderSettings::MenuItemRenderFunction_TraderSettings(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (param_1 < 0) {
                int const traderIndex = -1 - param_1;
                DAT_ButtonCurrentlyInteracting::instance
                    = (BOOLEnum)(DAT_MapPropertiesState::instance.SEC_Section1065
                                     .tradeabilityArray[((int*)((int)DAT_MissionAestheticsDefinedData::ptr
                                         + 0x345c))[traderIndex]]
                        != FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar2 = ((int*)((int)DAT_MissionAestheticsDefinedData::ptr + 0x345c))[traderIndex];
                iVar1 = iVar2 * 2 + 0x8d;
                if (iVar1 == 0x9d) {
                    iVar1 = 0x9b;
                }
                int const imhIndex = iVar1 + GMTotalPicturesProcessed::instance[0x2e] + -1;
                if (DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[iVar2] != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1,
                        (int)(DAT_ButtonX::instance + 10),
                        (int)((DAT_ButtonY::instance - DAT_GMImageHeaders::instance.imh[imhIndex].height / 2) + 0xf));
                    /*
                      added by script: "On"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                        DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xac),
                        DAT_ButtonW::instance + -10 + DAT_ButtonX::instance, (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0x12, FALSE, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar1,
                        (int)(DAT_ButtonX::instance + 10),
                        (int)((DAT_ButtonY::instance - DAT_GMImageHeaders::instance.imh[imhIndex].height / 2) + 0xf),
                        0x10);
                    /*
                      added by script: "On"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                        DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xad),
                        DAT_ButtonW::instance + -10 + DAT_ButtonX::instance, (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_RIGHT, 0x7caaaf, 0x12, FALSE, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
            }
            if (param_1 < 1000) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (param_1 == 0x44c) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                    /*
                      added by script: "Trader 1"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TRADER_NAMES, 1,
                        (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_CENTER, 0xa2ff, 0x3e66, 0x12, FALSE);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                    /*
                      added by script: "Trader 1"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TRADER_NAMES, 1,
                        (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_CENTER, 0xffffff, 0, 0x12, FALSE);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
            }
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                OpenSHC::UI::Enums::RBERL_SLIGHT);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }

    }
}
}
