#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC110
    void MapPropertiesState::adjustEventMonthAndYearForSection1047()
    {
        DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month;
        DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 0;
        DAT_GameState::instance.mapAndTime.field3183_0x27dc = 0;
        DAT_GameState::instance.mapAndTime.field3180_0x27d6 = 0;
        DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
        if (DAT_GameCore::instance.missionNumber1to20 == 17) {
            DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 1;
        } else if (DAT_GameCore::instance.missionNumber1to20 == 18) {
            DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 1;
        } else if (DAT_GameCore::instance.missionNumber1to20 == 19) {
            DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 6;
        } else {
            if (DAT_GameCore::instance.missionNumber1to20 != 20) {
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 0;
                DAT_GameState::instance.mapAndTime.field3180_0x27d6 = 0;
                DAT_GameState::instance.mapAndTime.field3183_0x27dc = 0;
            }
            DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 3;
        }
        if (12 < DAT_GameState::instance.mapAndTime.month) {
            DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month - 12;
            DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
        }
    }

}
}
