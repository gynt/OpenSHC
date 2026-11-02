#include "../CrusadeEndscreen.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Audio::MSS::enums::SHC_SoundStream;
        using DE::SHCDE::eTextSections;
        using Game::TrailType;
        using Text::GameLanguage;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DF2E0
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_Prepare()
        {
            char* pcVar1;
            undefined4 uVar2;
            SHC_SoundStream SVar3;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_SKTRAIL_WIN_TGX_005AB768);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME1_TGX_005AB758);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME2_TGX_005AB748);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME3_TGX_005AB738);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME4_TGX_005AB728);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME5_TGX_005AB718);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME6_TGX_005AB708);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME7_TGX_005AB6F8);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_ENDFRAME8_TGX_005AB6E8);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                S_JESTERLAST_TGX_005AB6D8);
            MACRO_CALL(UI::Credits_Func::ResetCredits)();
            DAT_NumberOfStoredMenuStrings::instance = 0;
            /*
              added by script: "Congratulations!"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKTRAIL_WIN, 0);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            /*
              added by script: "Many have set out..."
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKTRAIL_WIN, 1);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            /*
              added by script: "...but few will have survived this journey."
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKTRAIL_WIN, 2);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            /*
              added by script: "You have bested the Crusader Trail!"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKTRAIL_WIN, 3);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            /*
              added by script: "You have bested the Crusader Extreme Trail!"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKTRAIL_WIN, 4);
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsShowImageCommand)(0x29, 0, 0xe6, 0xcb, 0x150, 0xa8, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 1, 0x192, 0xea, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 0, 400, 0xe8, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 1, 0x6a, 0x35, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, S_RT_VICT1_BIK_005A78FC, 0x6a, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_RT_ANGER_04_WAV_005AB6BC, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 2, 0x14b, 0x18, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_SN_VICT2_BIK_005A78EC, 0x14b, 0x18, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_SN_ADD_PLAYER_WAV_005AB6A0, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 3, 0x22d, 0x35, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_PG_TAUNT2_BIK_005A7C44, 0x22d, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_PG_ADD_PLAYER_WAV_005AB684, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 4, 0x280, 0xdf, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_WF_ANGER1_BIK_005A7B20, 0x280, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_WF_ANGER_04_WAV_005AB668, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 5, 0x22d, 0x18a, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_SALADIN_ANGRY_BIK_005A7B0C, 0x22d, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_SA_EXTRA_01_WAV_005AB64C, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 6, 0x14c, 0x1b4, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_SULTAN_NATURAL_BIK_005A78A4, 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_SU_CONGRATS_01_WAV_005AB62C, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 7, 0x6a, 0x18a, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_RICHARD_TAUNTING_BIK_005A7D00, 0x6a, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_RI_CONGRATS_01_WAV_005AB60C, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 8, 0x23, 0xdf, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_BAD_ARAB_TAUNT_BIK_005A7D2C, 0x23, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                S_FX_SPEECH_CA_ADD_PLAYER_01_WAV_005AB5EC, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            uVar2 = 0x10;
            if (DAT_TextManagerObject::instance.gameLanguage == Text::GL_ITALIAN) {
                uVar2 = 0x11;
            }
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x5a));
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x5a));
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_2Unk);
            if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
                SVar3 = Audio::MSS::enums::SND_STR_SPEECH_2;
            } else {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
                SVar3 = Audio::MSS::enums::SND_STR_SPEECH_1;
            }
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, SVar3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x6a, 0x35, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x6a, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x14b, 0x18, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x14b, 0x18, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x22d, 0x35, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x22d, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x280, 0xdf, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x280, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SFX_1Unk));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x22d, 0x18a, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x22d, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SFX_2Unk));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x14c, 0x1b4, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SPEECH_1));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x6a, 0x18a, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x6a, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, ((SHC_SoundStream)8));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x23, 0xdf, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x23, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageEndCommand)(0x2a, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x6a, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x14b, 0x18, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x22d, 0x35, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x280, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x22d, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x6a, 0x18a, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                0xc, S_ACTION_JESTER_BIK_005AA504, 0x23, 0xdf, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsClearImageCommand)();
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
