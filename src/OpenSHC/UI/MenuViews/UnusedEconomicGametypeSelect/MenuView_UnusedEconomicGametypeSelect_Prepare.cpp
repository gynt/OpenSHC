#include "../UnusedEconomicGametypeSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LastHoveredMenuButtonId.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004259D0
        void UnusedEconomicGametypeSelect::MenuView_UnusedEconomicGametypeSelect_Prepare()
        {
            DWORD _currentTime;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_economics.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_economics2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            _currentTime = timeGetTime();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x168].animationStartTime_0x18
                = _currentTime - 0x12c0;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x169].animationStartTime_0x18
                = _currentTime - 0xc80;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16a].animationStartTime_0x18
                = _currentTime - 0x640;
            DAT_LastHoveredMenuButtonId::instance = -1;
            DAT_GameCore::instance.isTimeHalted2 = 0;
        }

    }
}
}
