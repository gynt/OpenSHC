#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df3374.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00df3370.hpp"
#include "OpenSHC/Globals/DWORD_00df3378.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Audio::SFX::ResourceLackSFX;
        using Audio::SFX::SoundEffectID;
        using Commands::GameCommandType;
        using Game::GameMode;
        using Game::Resources::ResourceType;
        using Game::Resources::ResourceTypeInt;
        using Map::Units::EuroRecruitableState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004672F0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick(
            int barrackUnitIdUnk, ...)
        {
            DWORD DVar1;
            DWORD DVar2;
            EuroRecruitableState _recruitableState
                = MACRO_CALL(UI::Helpers_Func::IsEuroUnitRecruitableUnk)(barrackUnitIdUnk);
            if (_recruitableState != Map::Units::ERS_CAN_RECRUITUnk) {
                ResourceTypeInt _unitCost
                    = DAT_TroopDefinedData::instance.MarketResourceCycleArray[barrackUnitIdUnk + -1];
                if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                    && (!DAT_GameSynchronyState::instance.skirmishTroopsCostGold)) {
                    _unitCost = ((ResourceType)0);
                }
                if (_recruitableState == Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY) {
                    if (!DAT_GameCore::instance.genieVoiceActive) {}
                    /*
                      @TheRedDaemon: Army is Max Size Message
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                        "Genie_26.wav");
                }
                if (_recruitableState != Map::Units::ERS_UNABLE_MISSING_PEASANTS) {
                    if ((int)_unitCost
                        <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[0xf]) {
                        if (_recruitableState != Map::Units::ERS_CAN_NOT_RECRUIT) {}
                    LAB_004674a0:
                        /*
                          "Weapons needed sire"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "other_warning6.wav");
                    }
                LAB_00467488:
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_GOLD);
                }
            LAB_00467424:
                /*
                  "Recruits needed sire"
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning5.wav");
            }
            int _recruitSuccess = MACRO_CALL_MEMBER(
                Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(barrackUnitIdUnk,
                (undefined4)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .barracks.id)),
                (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID), 1);
            if (!_recruitSuccess) {
                if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 1)
                    goto LAB_00467488;
                if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 2)
                    goto LAB_004674a0;
                if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason != 3) {}
                goto LAB_00467424;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = barrackUnitIdUnk;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_RECRUIT_UNIT);
            MACRO_CALL(UI::Helpers_Func::SetEnoughGoldForRequestedUnitToTrueUnk)();
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                Audio::SFX::SEID_BUTTON_CLICK_01);
            DWORD _now = timeGetTime();
            if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].count_2
                        + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .armySize
                    < (DAT_GameState::instance.mapAndTime.armySizeLimit * 9) / 10)
                || (_now - DWORD_00df3378::instance < 0x7531)) {
                DVar1 = DWORD_00df3370::instance;
                DVar2 = DWORD_00df3378::instance;
                if (barrackUnitIdUnk != DAT_00df3374::instance)
                    goto LAB_004673e5;
            } else {
                barrackUnitIdUnk = DAT_00df3374::instance;
                DVar1 = _now;
                DVar2 = _now;
                if (DAT_GameCore::instance.genieVoiceActive) {
                    /*
                      "Your army is approaching its maximum size"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "Genie_27.wav");
                    barrackUnitIdUnk = DAT_00df3374::instance;
                }
            }
            DWORD_00df3378::instance = DVar2;
            DWORD_00df3370::instance = DVar1;
            if (_now - DWORD_00df3370::instance < 0x1f41) {}
        LAB_004673e5:
            /*
              Plays unit recruitment message
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                (char const*)((int)DAT_UIButtonDefinedData::instance.ButtonGmDataArray + barrackUnitIdUnk * 0x20
                    + 0x4458));
            DAT_00df3374::instance = barrackUnitIdUnk;
            DWORD_00df3370::instance = _now;
        }

    }
}
}
