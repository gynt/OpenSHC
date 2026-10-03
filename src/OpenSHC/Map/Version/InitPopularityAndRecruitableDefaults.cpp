#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Initialises default values for all 8 players after a map version upgrade. Copies each player's
      storedPopularityPercent into someCount44, and sets all euro and merc recruitable flags to 1   (enabled) across
      both the primary and copy arrays in mapAndTime. Called as part of the map   versioning/upgrade pipeline. renamed
      by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AD10
    void Version::InitPopularityAndRecruitableDefaults()
    {
        DAT_GameState::instance.playerDataArray[1].someCount44
            = (short)DAT_GameState::instance.playerDataArray[1].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[2].someCount44
            = (short)DAT_GameState::instance.playerDataArray[2].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[4].someCount44
            = (short)DAT_GameState::instance.playerDataArray[4].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[3].someCount44
            = (short)DAT_GameState::instance.playerDataArray[3].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[5].someCount44
            = (short)DAT_GameState::instance.playerDataArray[5].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[7].someCount44
            = (short)DAT_GameState::instance.playerDataArray[7].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[6].someCount44
            = (short)DAT_GameState::instance.playerDataArray[6].storedPopularityPercent;
        DAT_GameState::instance.playerDataArray[8].someCount44
            = (short)DAT_GameState::instance.playerDataArray[8].storedPopularityPercent;
        DAT_GameState::instance.mapAndTime.euroRecruitable[0] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[0] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[1] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[1] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[2] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[2] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[3] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[3] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[4] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[4] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[5] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[5] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[6] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[6] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
        DAT_GameState::instance.mapAndTime.field2257_0xda8 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
    }

}
}
