#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using Commands::GameCommandType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00429710
    void Skirmish::SetupSkirmishBalanceAndOrIntensity()
    {
        int _index;
        switch (DAT_GameSynchronyState::instance.skirmishTechLevel) {
        case 0:
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = 1;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 0;
            break;
        case 1:
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = 1;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 1;
            break;
        case 2:
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = 2;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 1;
            break;
        case 3:
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = 2;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 2;
            break;
        case 4:
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = 3;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 3;
            break;
        default:
            goto switchD_00429720_caseD_5;
        }
        DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
        DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
        DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
        DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
    switchD_00429720_caseD_5:
        if (DAT_GameSynchronyState::instance.skirmishGameIntensityType == 1) {
            _index = 0;
            do {
                DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[_index]
                    = DAT_RenderingDefinedData::instance
                          .SkirmishIntensityRelatedArray[0][DAT_GameSynchronyState::instance.skirmishTechLevel][_index];
                _index = _index + 1;
            } while (_index < 0x14);
        } else if (DAT_GameSynchronyState::instance.skirmishGameIntensityType == 2) {
            _index = 0;
            do {
                DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[_index]
                    = DAT_RenderingDefinedData::instance
                          .SkirmishIntensityRelatedArray[1][DAT_GameSynchronyState::instance.skirmishTechLevel][_index];
                _index = _index + 1;
            } while (_index < 0x14);
        } else if (DAT_GameSynchronyState::instance.skirmishGameIntensityType == 3) {
            _index = 0;
            do {
                DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[_index]
                    = DAT_RenderingDefinedData::instance
                          .SkirmishIntensityRelatedArray[2][DAT_GameSynchronyState::instance.skirmishTechLevel][_index];
                _index = _index + 1;
            } while (_index < 20);
        }
        switch (DAT_GameSynchronyState::instance.skirmishGameIntensityType2) {
        case 0:
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[0] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[1] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[2] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[3] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[4] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[5] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[6] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[7] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[8] = 0;
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[9] = 0;
            break;
        case 1:
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[0]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][0];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[1]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][1];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[2]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][2];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[3]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][3];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[4]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][4];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[5]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][5];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[6]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][6];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[7]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][7];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[8]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][8];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[9]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][9];
            break;
        case 2:
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[0]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][0];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[1]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][1];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[2]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][2];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[3]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][3];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[4]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][4];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[5]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][5];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[6]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][6];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[7]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][7];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[8]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][8];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[9]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 5][9];
            break;
        case 3:
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[0]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][0];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[1]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][1];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[2]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][2];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[3]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][3];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[4]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][4];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[5]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][5];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[6]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][6];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[7]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][7];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[8]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][8];
            DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[9]
                = DAT_RenderingDefinedData::instance
                      .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel + 10][9];
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        DAT_GameSynchronyState::instance.field235_0x1072e8 = -1;
        DAT_GameSynchronyState::instance.field236_0x1072ec = -1;
    }

}
}
