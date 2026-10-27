#include "../TutorialBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df5564.hpp"
#include "OpenSHC/Globals/DAT_00df5644.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/INT_00df5648.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00df5598.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BCBA0
        void TutorialBox::MenuModalRenderFunction_TutorialBox(int x, int y, int width, int height)
        {
            if (0x20 <= (int)DAT_TutorialCurrentStep::instance) {
                return;
            }
            int textX = x + 0x10;
            int textWidth = width + -0x20;
            int tutorialTextOffset = INT_ARRAY_00df5598::instance[DAT_TutorialCurrentStep::instance];
            BOOLEnum keepOffsetX = FALSE;
            if (DAT_00df5540::instance != 0) {
                keepOffsetX = DAT_00df5544::instance;
            }
            int boxWidth = ((width + -1) / 0x18 + 1) * 0x18;
            int boxHeight = ((height + -1) / 0x18 + 1) * 0x18;
            for (int offsetY = 0; offsetY < boxHeight; offsetY = offsetY + 0x18) {
                int rowBaseIcon;
                if (offsetY == 0) {
                    rowBaseIcon = 1;
                } else if (offsetY == boxHeight + -0x18) {
                    rowBaseIcon = 0xd;
                } else {
                    rowBaseIcon = 7;
                }
                for (int offsetX = 0; offsetX < boxWidth; offsetX = offsetX + 0x18) {
                    int iconIndex = rowBaseIcon;
                    if (offsetX != 0) {
                        if (offsetX == boxWidth + -0x18) {
                            iconIndex = rowBaseIcon + 2;
                        } else if (rowBaseIcon == 7) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 8,
                                offsetX + x, offsetY + y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xb,
                                (int)(keepOffsetX));
                            continue;
                        } else {
                            iconIndex = rowBaseIcon + 1;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iconIndex,
                        offsetX + x, offsetY + y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iconIndex + 3,
                        (int)(keepOffsetX));
                }
            }
            if ((DAT_00df5564::instance != 0) && (INT_00df5648::instance == 0)) {
                DAT_00df5644::instance = DAT_00df5644::instance + 1;
                if (1 < (int)DAT_00df5644::instance) {
                    DAT_00df5644::instance = 0;
                }
                if ((MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                         DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1)
                        == FALSE)
                    && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                            DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2)
                        == FALSE)) {
                    char speechFileName[32];
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(speechFileName, "%s%s", "fx\\speech\\",
                        DAT_MissionAestheticsDefinedData::instance.field1248_0x41e4[DAT_00df5644::instance + 34][0]);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                        DAT_SoundSystemState::ptr)(speechFileName);
                }
            }
            int titleX = (width >> 1) + x;
            INT_00df5648::instance = DAT_00df5564::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL, tutorialTextOffset),
                titleX, y + 0xf, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, (int)(keepOffsetX));
            int bodyY = y + 0x26;
            if (DAT_00df5564::instance == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TUTORIAL, DAT_00df5558::instance + 1 + tutorialTextOffset),
                    textX, bodyY, textWidth, 0xc2f0eb, 0x13, (int)(keepOffsetX));
                bodyY = bodyY + DAT_TextManagerObject::instance.field1_0x4;
            }
            if (DAT_00df5564::instance != 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                        0, 0, textWidth, 0, 0, 1)
                    > 0x23) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                        textX, bodyY, textWidth, 0xff, 0x12, (int)(keepOffsetX));
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                        titleX, bodyY, OpenSHC::Text::TTA_CENTER, 0xff, 0x12, keepOffsetX, 0);
                }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTutorialFloatForUIElement)(DAT_TutorialCurrentStep::instance);
        }
    }
}
}
