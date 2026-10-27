#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    /* destroy command: param0 = building ID (or minus a pitch ditch ID), param1 = refund percent, param2 = uid.
       A building also takes down the drawbridges at its footprint (at most two are looked up). */
    // FUNCTION: STRONGHOLDCRUSADER 0x00481F40
    void Commands::ClickDestroyBuilding()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 7;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            short receivedBuildingID;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&receivedBuildingID, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = receivedBuildingID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);

            if ((int)DAT_GameSynchronyState::instance.DAT_GameCommandParam0 > 0) {
                int buildingID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
                if (DAT_BuildingsState::instance.buildings[buildingID].uid
                    == DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                    int drawbridgeID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                        DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y,
                        DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                    if (drawbridgeID != 0) {
                        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                            DAT_BuildingsState::ptr)(drawbridgeID, DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                            drawbridgeID);
                        drawbridgeID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                            DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y,
                            DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                            OpenSHC::Map::Buildings::BT_DRAWBRIDGE, drawbridgeID);
                        if (drawbridgeID != 0) {
                            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                                DAT_BuildingsState::ptr)(drawbridgeID, DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                                DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                                DAT_BuildingsState::ptr)(drawbridgeID);
                        }
                    }
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                    if (DAT_BuildingsState::instance.buildings[buildingID].noRefundOnDestroy == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                            DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                            DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
                    }
                    /* the original tests buildingID != 0 again although it is > 0 here (0x482114) */
                    if (buildingID != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                        case OpenSHC::Map::Buildings::BT_TOWER1:
                        case OpenSHC::Map::Buildings::BT_TOWER2:
                        case OpenSHC::Map::Buildings::BT_TOWER3:
                        case OpenSHC::Map::Buildings::BT_TOWER4:
                        case OpenSHC::Map::Buildings::BT_TOWER5:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_BuildingsState::instance.buildings[buildingID].x,
                                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                            break;
                        default:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "buildingwreck_01.wav");
                            break;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                }
            } else {
                /* zero or negative: minus the pitch ditch ID */
                int pitchDitchID = -(int)DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
                if (DAT_TileMapState::instance.pitchDitches[pitchDitchID].uid
                    == DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::destroyPitchDitch, DAT_TileMapState::ptr)(
                        pitchDitchID);
                }
            }
        }
    }

}
}
