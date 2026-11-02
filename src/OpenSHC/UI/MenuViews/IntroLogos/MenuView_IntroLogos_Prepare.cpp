#include "../IntroLogos.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424720
        void IntroLogos::MenuView_IntroLogos_Prepare()
        {
            char* tgxFileName;
            if (!DAT_IntroStep::instance) {
                tgxFileName = S_LOGO1_TGX_005A1F74;
            } else {
                if (DAT_IntroStep::instance != 1)
                    goto LAB_0042474e;
                tgxFileName = S_LOGO2_TGX_005A1F68;
            }
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                tgxFileName);
        LAB_0042474e:
            DAT_IntroBlendStrength::instance = 0;
            DAT_IntroTimestamp::instance = timeGetTime();
        }

    }
}
}
