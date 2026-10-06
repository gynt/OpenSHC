#include "../../Synchrony.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_0053f088.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "../Commands.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00481F40
    void Commands::ClickDestroyBuilding()
    {
        int iVar1;
        short local_4[2];
        int _buildingID;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 7;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            /*
              write parameter in gamecommand entry in events queue
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            /*
              read the parameters back into the variables
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_4[0];
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            _buildingID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 1) {
                if (*(int*)(DAT_0053f088::ptr + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * -0x14
                        + (int)DAT_TileMapState::instance.directionTranslationMatrix)
                    == DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::destroyPitchDitch, DAT_TileMapState::ptr)(
                        -DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                    return;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                           .uid
                == DAT_GameSynchronyState::instance.DAT_GameCommandParam2) {
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .owner,
                    ((int)((short)DAT_BuildingsState::instance
                            .buildings[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                            .x)),
                    ((int)((short)DAT_BuildingsState::instance
                            .buildings[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                            .y)),
                    ((int)(DAT_BuildingsState::instance
                            .buildings[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                            .widthOrHeight)),
                    OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                if (iVar1) {
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(iVar1,
                        (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(iVar1);
                    iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[_buildingID].owner,
                        ((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].x)),
                        ((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].y)),
                        ((int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight)),
                        OpenSHC::Map::Buildings::BT_DRAWBRIDGE, iVar1);
                    if (iVar1) {
                        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                            DAT_BuildingsState::ptr)(iVar1,
                            (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)),
                            (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)));
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                            DAT_BuildingsState::ptr)(iVar1);
                    }
                }
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                if (DAT_BuildingsState::instance.buildings[_buildingID].field203_0x288 == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                        (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)));
                }
                if ((_buildingID)
                    && (DAT_BuildingsState::instance.buildings[_buildingID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                    switch (DAT_BuildingsState::instance.buildings[_buildingID].buildingType) {
                    case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    case OpenSHC::Map::Buildings::BT_TOWER1:
                    case OpenSHC::Map::Buildings::BT_TOWER2:
                    case OpenSHC::Map::Buildings::BT_TOWER3:
                    case OpenSHC::Map::Buildings::BT_TOWER4:
                    case OpenSHC::Map::Buildings::BT_TOWER5:
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[_buildingID].y)),
                            OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                        break;
                        default:
                            /*
                              Plays building destroy sound
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "buildingwreck_01.wav");
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            }
        }
        return;
    }

}
}
