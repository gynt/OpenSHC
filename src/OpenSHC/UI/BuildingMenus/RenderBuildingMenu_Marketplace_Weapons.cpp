#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Game::Resources::ResourceType;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D1D0
    void BuildingMenus::RenderBuildingMenu_Marketplace_Weapons()
    {
        char* textAddress;
        int iVar2;
        int* piVar3;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum BVar4;
        int blendStrength;
        blendStrength = 0;
        BVar4 = FALSE;
        fontSize = 0x11;
        color = 0;
        alignment = Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d4;
        iVar2 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Trade Weapons"
         */
        textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TRADEPOST, 4);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, iVar2, iVar1, alignment, color, fontSize, BVar4, blendStrength);
        iVar1 = 0;
        piVar3 = DAT_RenderingDefinedData::instance.field1047_0x555e4;
        do {
            ResourceType resourceType = (Game::Resources::ResourceType)(*piVar3);
            iVar2 = DAT_MenuHandlerState::instance.x + 0x78;
            BVar4 = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(resourceType);
            if (BVar4 != FALSE) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[resourceType],
                    iVar2 + iVar1, DAT_MenuHandlerState::instance.y + 0x232, Text::TTA_CENTER, 0, 0x11, FALSE,
                    0);
            }
            piVar3 = piVar3 + 1;
            iVar1 = iVar1 + 0x34;
        } while ((int)piVar3 < 0x618070);
    }

}
}
