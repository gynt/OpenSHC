#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    /* recruit command: only while the army (plus peasants already walking to be recruited) is below the map limit.
       Engineers and laddermen come from the engineer's guild, tunnelers from the tunneler's guild, monks from the
       given building, Arabian units from the mercenary post; everything else is a European unit from the
       barracks. */
    // FUNCTION: STRONGHOLDCRUSADER 0x00464EF0
    void Actions::ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].peasantsBeingRecruitedAsTroops
                + DAT_GameState::instance.playerDataArray[playerID].armySize
            < DAT_GameState::instance.mapAndTime.armySizeLimit) {
            if (unitType == 0x1e) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_E_ENGINEER,
                    DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id, playerID, 0);
                return;
            }
            if (unitType == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_TUNNELER,
                    DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.id, playerID, 0);
                return;
            }
            if (unitType == 0x1d) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_E_LADDER,
                    DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id, playerID, 0);
                return;
            }
            if (unitType == 0x25) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_E_MONK, recruitmentBuildingID, playerID, 0);
                return;
            }
            if (unitType == 0x46) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_ARCHER,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x47) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_SLAVE,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x48) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_SLINGER,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x49) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_ASSASSIN,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x4a) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_HARCHER,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x4b) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_SWORDSMAN,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            if (unitType == 0x4c) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    OpenSHC::Map::Units::UT_A_FIRETHROWER,
                    DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id, playerID, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(
                unitType, DAT_GameState::instance.playerDataArray[playerID].barracks.id, playerID, 0);
        }
    }

}
}
