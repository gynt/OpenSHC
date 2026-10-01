#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004174E0
    void Buildings::UpdateStables()
    {
        short* psVar1;
        byte* pbVar2;
        int* piVar3;
        int buildingID;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits,
            DAT_BuildingsState::ptr)(buildingID);
        if (((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x04')
            && (psVar1 = &DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4, *psVar1 = *psVar1 + 1,
                0x226 < DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4)) {
            pbVar2 = &DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals;
            *pbVar2 = *pbVar2 + 1;
            DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses, DAT_GameState::ptr)();
            buildingID = DAT_CurrentBuildingID::instance;
        }
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].field28_0x58;
        *piVar3 = *piVar3 + 1;
        if (5 < DAT_BuildingsState::instance.buildings[buildingID].field28_0x58) {
            DAT_BuildingsState::instance.buildings[buildingID].field28_0x58 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].field28_0x58 < 1) {
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].field20_0x38 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x01') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].field20_0x38
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].field20_0x38 = 0x2a;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x02') {
                DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x02') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].field25_0x4c;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field25_0x4c]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].field25_0x4c = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field25_0x4c];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c = 0x29;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x03') {
                DAT_BuildingsState::instance.buildings[buildingID].field22_0x40 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x03') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].field26_0x50;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field26_0x50]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].field26_0x50 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].field22_0x40
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field26_0x50];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].field22_0x40 = 0x28;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x04') {
                DAT_BuildingsState::instance.buildings[buildingID].field23_0x44 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x04') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].field27_0x54;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field27_0x54]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].field27_0x54 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].field23_0x44
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field147_0x715c[DAT_BuildingsState::instance.buildings[buildingID].field27_0x54];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].field23_0x44 = 0x27;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .field177_0x7e1c[DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame / 2]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].field39_0x84
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field177_0x7e1c[DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame / 2];
            }
            DAT_BuildingsState::instance.buildings[buildingID].field39_0x84 = 0;
        }
    }

}
}
