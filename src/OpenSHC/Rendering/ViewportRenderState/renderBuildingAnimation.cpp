#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/currentlyRenderedGmID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E3870
    void ViewportRenderState::renderBuildingAnimation(
        int buildingID, int screenX, int screenY, undefined4 param_4, int clipToBuilding)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].renderAnimation == 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame == 0) {
            return;
        }
        if (DAT_TileMapState::instance.flatViewMode != 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].drawbridgePhase != 0) {
            return;
        }

        if (clipToBuilding != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::saveMapSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)
            ();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)
            ((screenY - 0x27 < 0) ? 0 : screenY - 0x27, 0x81c);
        }

        DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].ownerColorIndex;
        currentlyRenderedGmID::instance = DAT_BuildingsState::instance.buildings[buildingID].spriteID2;
        if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)
            ((OpenSHC::IO::Graphics::GmID)currentlyRenderedGmID::instance,
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY,
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha);
        } else {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)
            ((OpenSHC::DE::SHCDE::eGM)currentlyRenderedGmID::instance,
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY);
        }
        if (clipToBuilding != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::restoreMapSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)
            ();
        }
    }

}
}
