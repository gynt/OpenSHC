#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
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

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D070
    void BuildingMenus::RenderBuildingMenu_Marketplace_Food()
    {
        char* textAddress;
        int iVar2;
        BOOLEnum BVar4;
        BVar4 = FALSE;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d4;
        iVar2 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Trade Food"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 2),
            iVar2, iVar1, OpenSHC::Text::TTA_LEFT, 0, 0x11, BVar4, 0);
        iVar1 = 0;
        for (int i = 0; i < 8; i++) {
            ResourceType resourceType = (OpenSHC::Game::Resources::ResourceType)(
                DAT_RenderingDefinedData::instance.FoodTypes[i]);
            iVar2 = DAT_MenuHandlerState::instance.x + iVar1 + 0x78;
            BVar4 = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(resourceType);
            if (BVar4 != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[resourceType],
                    iVar2, DAT_MenuHandlerState::instance.y + 0x232, OpenSHC::Text::TTA_CENTER, 0, 0x11, FALSE,
                    0);
            }
            iVar1 = iVar1 + 0x34;
        }
    }

}
}
