#include "../Helpers.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using Audio::MSS::enums::SHC_SoundStream;
    using DE::SHCDE::eTextSections;

    // FUNCTION: STRONGHOLDCRUSADER 0x004DC1C0
    void Helpers::BuildExtremeDemoIntroScript()
    {
        char* textToStore;
        int iVar1;
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
            DAT_TextureRenderCoreObject::ptr)("bullet2.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("p4.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("p3.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("p1.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("p2.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("demo1.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("demo2.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("demo3.tgx");
        MACRO_CALL_MEMBER(
            UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("demo4.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
            DAT_TextureRenderCoreObject::ptr)("logo_280x100.tgx");
        for (iVar1 = 0; iVar1 < 5; iVar1++) {
            /*
              'Cut a path through an increasingly tough extreme trail. As the numbers of   opponents go up, so does the
              challenge!'   'Relive the Crusades from both sides, with the original Stronghold Crusader   and all the
              additional content ever released.'   '16 AI characters to fight against, 1000\u2019s of troops to battle,
              months   of game play to keep you hooked!'   'Battle your friends and enemies alike, online, in Extreme
              multiplayer.'   'Make and distribute new play maps, with a fully featured map editor.'
             */
            textToStore = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_EXTREME_DEMO, iVar1 + 8);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(textToStore);
        }
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 5);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x2c, ((SHC_SoundStream)0xb4));
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x13);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 6);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x2c, ((SHC_SoundStream)0xb4));
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x13);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 7);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x2c, ((SHC_SoundStream)0xb4));
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x13);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 8);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x14, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x2c, ((SHC_SoundStream)0xb4));
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(0x2b);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 9, 0x104, 10, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(2, ((SHC_SoundStream)9));
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x28));
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 0x5f, 0x80, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0x12, 0, 0x87, 0x8c, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            3, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x28));
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 0x5f, 0xd0, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 1, 0x12, 0, 0x87, 0xdc, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            3, Audio::MSS::enums::SND_STR_SFX_1Unk);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x28));
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 0x5f, 0x120, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 2, 0x12, 0, 0x87, 300, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            3, Audio::MSS::enums::SND_STR_SFX_2Unk);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x28));
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 0x5f, 0x170, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 3, 0x12, 0, 0x87, 0x17c, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            3, Audio::MSS::enums::SND_STR_SPEECH_1);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x28));
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 0x5f, 0x1c0, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 4, 0x12, 0, 0x87, 0x1cc, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            3, Audio::MSS::enums::SND_STR_SPEECH_2);
        MACRO_CALL(UI::Credits_Func::AppendCreditsFixedImageCommand)(1, 0x2ac, 0x226);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x16, Audio::MSS::enums::SND_STR_MUSIC);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(
            0x19, Audio::MSS::enums::SND_STR_MUSIC);
    }

}
}
