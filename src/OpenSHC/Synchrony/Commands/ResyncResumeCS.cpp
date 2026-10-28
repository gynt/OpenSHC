#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0048FCB0
    void Commands::ResyncResumeCS()
    {
        int _y10;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 64;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.uniqueGameObjectTracker, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            /*
              read into currentNumber2 RNG
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&SEC_RNG::instance.currentNumber2, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            /*
              read into index 2 RNG
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&SEC_RNG::instance.index2, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudTick, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudVariant1PauseCountdown, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudVariant0PauseCountdown, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.moatTileCount, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_LandscapeState::instance.wind, 0x1c,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.mapTimeInTicks, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameState::instance.gameTicksLoadBalancer, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.uniqueGameObjectTracker, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            /*
              set RNG currentNumber2
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&SEC_RNG::instance.currentNumber2, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            /*
              set RNG index 2
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&SEC_RNG::instance.index2, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudTick, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudVariant1PauseCountdown, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.dustCloudVariant0PauseCountdown, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_TileMapState::instance.moatTileCount, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_LandscapeState::instance.wind, (size_t)((int)(28)),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.mapTimeInTicks, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameState::instance.gameTicksLoadBalancer, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(
                OpenSHC::Map::TileMapState_Func::collectDustCloudSourceTiles, DAT_TileMapState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::generateDustClouds, DAT_TileMapState::ptr)();
            DAT_GameSynchronyState::instance.syncStatus = 3;
            DAT_PathFindingState::instance.searchGeneration = 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                160800, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            _y10 = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(_y10);
                _y10 = _y10 + 1;
            } while (_y10 < 0x28);
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
            DAT_EntityState::instance.maxEntityCount = 3000;
            DAT_BuildingsState::instance.maxBuildingsCount = 2000;
            DAT_LandscapeState::instance.maxTreeCount = 2000;
            DAT_UnitsState::instance.maxUnitCount = 2500;
            DAT_TileMapState::instance.maxMoatCount = 16000;
            DAT_TileMapState::instance.maxPitchDitchCount = 4000;
            MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::processPeasantsForBuildings, DAT_GameState::ptr)();
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            DAT_TileMapState::instance.terrainChangedDirty = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateAttackCandidateLayers, DAT_WildlifeState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
                DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
            }
            DAT_GameSynchronyState::instance.autosaveIntervalStartTime = timeGetTime();
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::computeStateHashesAndQueueSyncCheck,
                DAT_GameSynchronyState::ptr)(1);
            DAT_GameSynchronyState::instance.DAT_HashCountdown = 1;
            DAT_GameSynchronyState::instance.playerSlotOrder[0] = 0;
            DAT_GameSynchronyState::instance.playerSlotOrder[1] = 1;
            DAT_GameSynchronyState::instance.playerSlotOrder[2] = 2;
            DAT_GameSynchronyState::instance.playerSlotOrder[3] = 3;
            DAT_GameSynchronyState::instance.playerSlotOrder[4] = 4;
            DAT_GameSynchronyState::instance.playerSlotOrder[5] = 5;
            DAT_GameSynchronyState::instance.playerSlotOrder[6] = 6;
            DAT_GameSynchronyState::instance.playerSlotOrder[7] = 7;
            DAT_GameSynchronyState::instance.playerSlotOrder[8] = 8;
        }
    }

}
}
