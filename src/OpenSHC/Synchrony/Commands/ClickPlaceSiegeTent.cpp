#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::UnitType;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x004827E0
    void Commands::ClickPlaceSiegeTent()
    {
        int BVar1;
        MappersEnum commandBuildingType;
        int iVar2;
        int _unitID;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 7;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_GameSynchronyState::instance.DAT_CommandActionPlan;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = ((UnitType)0);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 1,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL) {
                commandBuildingType = OpenSHC::Commands::M_MAPPER_MANGONEL;
            } else {
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 != OpenSHC::Map::Units::UT_S_BALLISTA)
                    goto LAB_0048290e;
                commandBuildingType = OpenSHC::Commands::M_MAPPER_BALLISTA;
            }
            iVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                DAT_GameState::ptr)(
                commandBuildingType, (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)), FALSE);
            if (iVar2 == 0) {
                return;
            }
        }
    LAB_0048290e:
        if ((DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL)
            || (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA)) {
            iVar2 = (int)DAT_TileMapState::instance
                        .BuildingLayer[DAT_ViewportRenderState::instance
                                           .translationMatrix[(int)DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                                               / 8]
                                           .addXgetTile
                            + (int)DAT_GameSynchronyState::instance.DAT_GameCommandParam0 / 8];
            if ((iVar2 != 0) && (DAT_BuildingsState::instance.buildings[iVar2].containsSiegeMangonel1OrBallista2 != 0)) {
                return;
            }
        }
        _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
            (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)),
            (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0)),
            (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)),
            (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam2)),
            (UnitType)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam3)));
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
                DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                OpenSHC::Map::Buildings::BT_TOWER1_RUIN_OR_MANGONEL, 0);
        } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
                DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                OpenSHC::Map::Buildings::BT_TOWER2_RUIN_OR_BALLISTA, 0);
        }
        if (((DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL)
                || (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA))
            && ((iVar2 = (int)DAT_TileMapState::instance
                             .BuildingLayer[DAT_ViewportRenderState::instance
                                                .translationMatrix[(int)DAT_GameSynchronyState::instance
                                                                       .DAT_GameCommandParam1
                                                    / 8]
                                                .addXgetTile
                                 + (int)DAT_GameSynchronyState::instance.DAT_GameCommandParam0 / 8],
                iVar2 != 0)
                && ((BVar1 = DAT_BuildingsState::instance.buildings[iVar2].buildingType,
                    BVar1 == OpenSHC::Map::Buildings::BT_TOWER1 || (BVar1 == OpenSHC::Map::Buildings::BT_TOWER4))))) {
            DAT_BuildingsState::instance.buildings[iVar2].hasUnitsOntop = 1;
            DAT_BuildingsState::instance.buildings[iVar2].unitsOnTopRecheckCountdown = 100;
        }
        if (DAT_GameSynchronyState::instance.protocolInvokerPlayerID
            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::startUnitPlacementUndoWindow,
                DAT_WallAndPitchState::ptr)(_unitID);
        }
    }

}
}
