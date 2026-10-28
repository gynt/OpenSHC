#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C1A0
        void TroopValueState::lightPitchIfNecessary(int unitID, int unitID2)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                return;
            }
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] != -1
                || DAT_GameSynchronyState::instance.currentAIArray[owner] == 0) {
                return;
            }
            int const enemyTile = DAT_UnitsState::instance.units[unitID2].tile;
            if ((DAT_TileMapState::instance.LogicLayer[enemyTile] & 8) == 0) {
                return;
            }
            int const pitchDitchID
                = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(enemyTile);
            if (pitchDitchID == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(TroopValueState_Func::shouldLightPitchBasedOnTroopValue, this)(
                    enemyTile, owner, DAT_UnitsState::instance.units[unitID2].owner)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].shootTargetMicroX
                = DAT_TileMapState::instance.pitchDitches[pitchDitchID].x * 8 + 4;
            DAT_UnitsState::instance.units[unitID].shootTargetMicroY
                = DAT_TileMapState::instance.pitchDitches[pitchDitchID].y * 8 + 4;
            DAT_UnitsState::instance.units[unitID].shootTargetZ
                = DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance.pitchDitches[pitchDitchID].tile];
            DAT_UnitsState::instance.units[unitID].shootTargetedUnit = -1;
            DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = pitchDitchID;
            DAT_UnitsState::instance.units[unitID]
                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                = DAT_TileMapState::instance.pitchDitches[pitchDitchID].uid;
            DAT_UnitsState::instance.units[unitID].pendingTargetingType = UIT_LIGHT_PITCH;
            DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep = UIT_LIGHT_PITCH;
            DAT_UnitsState::instance.units[unitID].idleInterruptedForAttack = 0;
            DAT_UnitsState::instance.units[unitID].fireImmediately = true;
        }

    }
}
}
