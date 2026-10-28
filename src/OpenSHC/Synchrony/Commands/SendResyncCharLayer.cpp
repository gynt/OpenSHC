#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00483A00
    void Commands::SendResyncCharLayer()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x9d8;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
            case 10:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.DamageOrCropStageLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0xb:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.LuminesenceLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0xc:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.WallOwnerLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0xd:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.PathLinkageLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0xe:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.OccupancyLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0xf:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.HeightLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x10:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.AIInfoLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x11:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.AIZoneLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x12:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.SEC_TileMap1104
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512,
                    (size_t)((int)(2512)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x13:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.unitDeathHeatMap
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x14:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[0]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x15:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[1]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x16:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[2]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x17:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[3]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x18:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[4]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x19:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[5]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x1a:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[6]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x1b:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[7]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
                return;
            case 0x1c:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[8]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            }
            return;
        } else if ((DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE)
            && (DAT_GameSynchronyState::instance.isHost == FALSE)) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
            case 10:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.DamageOrCropStageLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0xb:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.LuminesenceLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0xc:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.WallOwnerLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0xd:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.PathLinkageLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0xe:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.OccupancyLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0xf:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.HeightLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x10:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.AIInfoLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x11:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.AIZoneLayer
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x12:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.SEC_TileMap1104
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512,
                    (size_t)((int)(2512)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x13:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.unitDeathHeatMap
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x14:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[0]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x15:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[1]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x16:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[2]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x17:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[3]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x18:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[4]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x19:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[5]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x1a:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[6]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x1b:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[7]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                return;
            case 0x1c:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_TileMapState::instance.aiZoneDistanceLayers[8]
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 0x9d0,
                    0x9d0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            }
        }
    }

}
}
