#include "../HistoricCampaignOutro.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/SFX/AmbientSFXType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"


namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Audio::MSS::enums::SHC_SoundStream;
        using Audio::SFX::AmbientSFXType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DBF00
        void HistoricCampaignOutro::MenuView_HistoricCampaignOutro_DoEveryFrame()
        {
            BOOLEnum BVar1;
            int iVar2;
            BVar1 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SFX_1Unk);
            if (!BVar1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playAmbientSoundStreamUnk, DAT_SFXState::ptr)(
                    Audio::SFX::ASFXT_WIND_0);
            }
            if (DAT_MouseState::instance.leftClickStart) {
                if (!DAT_00ed2780::instance) {
                    FLOAT_00ec0834::instance = 0.0;
                } else {
                    if (DAT_00ed2780::instance != 1)
                        goto LAB_004dbf52;
                    FLOAT_00ec0834::instance = 31.0 - FLOAT_00ec0834::instance;
                }
                DAT_00ed2780::instance = 2;
            }
        LAB_004dbf52:
            iVar2 = MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar2) {
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
                MACRO_CALL(UI::Rendering_Func::RenderHistoryBookEdgeUnk)();
                iVar2 = 0;
                if (DAT_00ed2780::instance == 1) {
                    iVar2 = (long)((double)FLOAT_00ec0834::instance);
                    iVar2 = 0x1f - iVar2;
                } else if (DAT_00ed2780::instance == 2) {
                    iVar2 = (long)((double)FLOAT_00ec0834::instance);
                }
                MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(0, 300, 0x96, 600, 0, 0xf, FALSE, iVar2);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_ArrayOfStoredMenuStrings::instance[1],
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x118, 0x2e4, 0, 0x11, iVar2);
                if ((((DAT_00ed2780::instance)
                         || (MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                             DAT_00eb0b20::instance, 0x2b, 0x3f, DAT_00ed2780::instance != 0)))
                        && (MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(
                            DAT_00eb0b20::instance, 0x2b, 0x3f, iVar2, DAT_00ed2780::instance != 0)))
                    && (FLOAT_00ec0834::instance = FLOAT_Between1And5::instance + FLOAT_00ec0834::instance,
                        32.0 < FLOAT_00ec0834::instance != (FLOAT_00ec0834::instance == 32.0))) {
                    if (DAT_00ed2780::instance == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_MAIN_MENU, 0);
                        FLOAT_00ec0834::instance = 31.0;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream,
                            DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SFX_1Unk);
                        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
                        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream,
                            DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_1);
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream,
                            DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_2);
                        return;
                    }
                    DAT_00ed2780::instance = 0;
                    switch (DAT_GameCore::instance.historicCampaignNumber) {
                    case 1:
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)("fx\\speech\\after_01.wav", 1);
                        return;
                    case 2:
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)("fx\\speech\\after_02.wav", 1);
                        return;
                    case 3:
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)("fx\\speech\\after_03.wav", 1);
                        return;
                    case 4:
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)("fx\\speech\\after_04.wav", 1);
                    }
                }
            }
            return;
        }

    }
}
}
