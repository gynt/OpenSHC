#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // The cage x/y are read (movsx) before the UID compare (0x466446). Four UT_CAGEDOG units are spawned at
    // (x*8, y*8), (x*8+8, y*8), (x*8, y*8+8), (x*8+8, y*8+8); each spawned dog (ID != 0) is linked to the cage.
    // The FX_DOG_CAGE sound re-reads the cage x/y (0x4665F5).
    // FUNCTION: STRONGHOLDCRUSADER 0x00466430
    void Actions::ProcessReleaseDogs(int playerID, int buildingID, int buildingUID)
    {
        int x = DAT_BuildingsState::instance.buildings[buildingID].x;
        int y = DAT_BuildingsState::instance.buildings[buildingID].y;
        if (DAT_BuildingsState::instance.buildings[buildingID].uid != buildingUID) {
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs = 1;
        for (int i = 0; i < 4; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[i] = 0;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[i] = 0;
        }

        int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0,
            playerID, x * 8, y * 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
            OpenSHC::Map::Units::UT_CAGEDOG);
        if (dogID != 0) {
            DAT_UnitsState::instance.units[dogID].workplaceOrHomeBuildingID = (short)buildingID;
            DAT_UnitsState::instance.units[dogID].workplaceBuildingOrTraderUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[0] = (short)dogID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[0]
                = DAT_UnitsState::instance.units[dogID].uid;
        }

        dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID,
            x * 8 + 8, y * 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
            OpenSHC::Map::Units::UT_CAGEDOG);
        if (dogID != 0) {
            DAT_UnitsState::instance.units[dogID].workplaceOrHomeBuildingID = (short)buildingID;
            DAT_UnitsState::instance.units[dogID].workplaceBuildingOrTraderUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[1] = (short)dogID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[1]
                = DAT_UnitsState::instance.units[dogID].uid;
        }

        dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID,
            x * 8, y * 8 + 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
            OpenSHC::Map::Units::UT_CAGEDOG);
        if (dogID != 0) {
            DAT_UnitsState::instance.units[dogID].workplaceOrHomeBuildingID = (short)buildingID;
            DAT_UnitsState::instance.units[dogID].workplaceBuildingOrTraderUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[2] = (short)dogID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[2]
                = DAT_UnitsState::instance.units[dogID].uid;
        }

        dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID,
            x * 8 + 8, y * 8 + 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
            OpenSHC::Map::Units::UT_CAGEDOG);
        if (dogID != 0) {
            DAT_UnitsState::instance.units[dogID].workplaceOrHomeBuildingID = (short)buildingID;
            DAT_UnitsState::instance.units[dogID].workplaceBuildingOrTraderUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[3] = (short)dogID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[3]
                = DAT_UnitsState::instance.units[dogID].uid;
        }

        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
            DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y,
            OpenSHC::DE::SHCDE::FX_DOG_CAGE);
    }

}
}
