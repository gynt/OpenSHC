#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // AI attack staging points: every cell marked siegeCampSuitable with validTileCount > 0 (signed jle 0x52E1F3)
    // whose centre tile (cell*10+5) is on the map and in the signpost's PathConnectionLayer region (read signed,
    // movsx) becomes an entry {x, y, 0, region, heightSum, routeBfsValue, (distance + 4) * 50 - heightSum};
    // nof_fpoints is not checked against the 100-entry capacity. The entries are then bubble-sorted by score
    // (signed short compare, jge 0x52E74E).
    // FUNCTION: STRONGHOLDCRUSADER 0x0052E120
    void WildlifeState::updateNofFpoints()
    {
        uint const signpostX = DAT_GameState::instance.mapAndTime
                                   .signpostEntryData[DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex]
                                   .x;
        uint const signpostY = DAT_GameState::instance.mapAndTime
                                   .signpostEntryData[DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex]
                                   .y;
        if (signpostX > 399 || signpostY > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[signpostY * 400 + signpostX] == 0) {
            return;
        }
        int const signpostRegion = (short)DAT_TileMapState::instance.PathConnectionLayer
                                       [DAT_ViewportRenderState::instance.translationMatrix[signpostY].addXgetTile
                                           + signpostX];
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        MACRO_CALL_MEMBER(WildlifeState_Func::floodFillCasDisFromSignpost, this)();
        DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
        for (int i = 0; i < 100; i++) {
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][0]
                = DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][1]
                = DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][2]
                = DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][3] = 0;
        }
        for (int cellY = 0; cellY < 40; cellY++) {
            for (int cellX = 0; cellX < 40; cellX++) {
                if (this->grid[cellX][cellY].siegeCampSuitable == 0 || this->grid[cellX][cellY].validTileCount <= 0) {
                    continue;
                }
                uint const tileX = cellX * 10 + 5;
                uint const tileY = cellY * 10 + 5;
                int const region = (short)DAT_TileMapState::instance.PathConnectionLayer
                                       [DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX];
                if (signpostRegion == region && tileX <= 399 && tileY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != 0) {
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][0]
                        = (short)tileX;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1]
                        = (short)tileY;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2]
                        = 0;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3]
                        = (short)region;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                        = (short)this->grid[cellX][cellY].heightSum;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                        = (short)this->grid[cellX][cellY].routeBfsValue;
                    DAT_TroopValueState::instance.attackInfo
                        .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                        = (DAT_TroopValueState::instance.attackInfo
                                  .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                              + 4)
                            * 50
                        - DAT_TroopValueState::instance.attackInfo
                              .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                    DAT_TroopValueState::instance.attackInfo.nof_fpoints++;
                }
            }
        }
        BOOL swapped;
        do {
            swapped = FALSE;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.nof_fpoints - 1; i++) {
                if (DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1][6]
                    < DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][6]) {
                    swapped = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(0x10,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy);
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(0x10,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i]);
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(0x10,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1]);
                }
            }
        } while (swapped);
    }

}
}
