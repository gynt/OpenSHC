#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // The original stores scriptTriggerYear again in every mission case (0x4BC149, 0x4BC15E, 0x4BC178, 0x4BC194).
    // Mission 18 returns without the month wrap; the wrap tests the live month, not scriptTriggerMonth.
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC110
    void MapPropertiesState::adjustEventMonthAndYearForSection1047()
    {
        DAT_GameState::instance.mapAndTime.scriptTriggerMonth = (short)DAT_GameState::instance.mapAndTime.month;
        DAT_GameState::instance.mapAndTime.militaryMissionScriptStage = 0;
        DAT_GameState::instance.mapAndTime.militaryMissionScriptStage2 = 0;
        DAT_GameState::instance.mapAndTime.militaryMissionScriptFlags = 0;
        DAT_GameState::instance.mapAndTime.scriptTriggerYear = (short)DAT_GameState::instance.mapAndTime.year;
        if (DAT_GameCore::instance.missionNumber == 0x11) {
            DAT_GameState::instance.mapAndTime.scriptTriggerYear = (short)DAT_GameState::instance.mapAndTime.year;
            DAT_GameState::instance.mapAndTime.scriptTriggerMonth
                = (short)(DAT_GameState::instance.mapAndTime.month + 1);
        }
        else if (DAT_GameCore::instance.missionNumber == 0x12) {
            DAT_GameState::instance.mapAndTime.scriptTriggerYear = (short)DAT_GameState::instance.mapAndTime.year;
            DAT_GameState::instance.mapAndTime.scriptTriggerMonth
                = (short)(DAT_GameState::instance.mapAndTime.month + 1);
            return;
        }
        else if (DAT_GameCore::instance.missionNumber == 0x13) {
            DAT_GameState::instance.mapAndTime.scriptTriggerYear = (short)DAT_GameState::instance.mapAndTime.year;
            DAT_GameState::instance.mapAndTime.scriptTriggerMonth
                = (short)(DAT_GameState::instance.mapAndTime.month + 6);
        }
        else if (DAT_GameCore::instance.missionNumber == 0x14) {
            DAT_GameState::instance.mapAndTime.scriptTriggerYear = (short)DAT_GameState::instance.mapAndTime.year;
            DAT_GameState::instance.mapAndTime.scriptTriggerMonth
                = (short)(DAT_GameState::instance.mapAndTime.month + 3);
        }
        else {
            return;
        }
        if (DAT_GameState::instance.mapAndTime.month >= 12) {
            DAT_GameState::instance.mapAndTime.month -= 12;
            DAT_GameState::instance.mapAndTime.year += 1;
        }
    }

}
}
