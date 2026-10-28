#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D2B0
        void TroopValueState::decideAndExecuteTribeAttackAction(int tribeID)
        {
            int const leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            int const buildingID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findNearestEnemyBuildingWithinDistance,
                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                DAT_UnitsState::instance.units[leaderUnitID].x, DAT_UnitsState::instance.units[leaderUnitID].y, 15);
            int const unitID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findNearestEnemyUnitWithinDistance, DAT_PathFindingState::ptr)(
                DAT_TribesState::instance.tribes[tribeID].owner, DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, 10);
            if (buildingID != 0 && (SEC_RNG::instance.currentNumber2 & 1) != 0) {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    UIT_ATTACK_BUILDING, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
                return;
            }
            if (unitID != 0 && (SEC_RNG::instance.currentNumber2 & 1) != 0) {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    tribeID, UIT_UNIT_ATTACK_UNIT, unitID, DAT_UnitsState::instance.units[unitID].uid, 0);
                return;
            }
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, UIT_NO_INSTRUCTION_OR_MOVE, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            int tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, DAT_UnitsState::instance.units[leaderUnitID].owner, 6);
            if (tile <= 0) {
                tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                    DAT_UnitsState::instance.units[leaderUnitID].y, DAT_UnitsState::instance.units[leaderUnitID].owner,
                    30);
                if (tile <= 0) {
                    tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                        DAT_UnitsState::instance.units[leaderUnitID].y,
                        DAT_UnitsState::instance.units[leaderUnitID].owner, 50);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (tile > 0) {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 0, 0,
                    Instructions::UMSE_0);
            }
        }

    }
}
}
