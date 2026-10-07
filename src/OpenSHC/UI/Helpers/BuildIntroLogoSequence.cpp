#include "../Helpers.func.hpp"

#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using Audio::MSS::enums::SHC_SoundStream;

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB180
    void Helpers::BuildIntroLogoSequence(undefined4 param_1, undefined4 param_2)
    {
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("logo1.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("logo2.tgx");
        MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsListTerminator)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            1, (Audio::MSS::enums::SHC_SoundStream)0x3c);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x13);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsPauseCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            8, Audio::MSS::enums::SND_STR_MUSIC);
    }

}
}
