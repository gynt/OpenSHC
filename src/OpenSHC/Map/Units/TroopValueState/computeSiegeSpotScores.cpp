#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519990
        void TroopValueState::computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID)
        {
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.id == 0) {
                return;
            }
            // playerInfo is 1-based: the original indexes the records from the non-existent record 0
            AttackInfoSubElement* const playerRecords = DAT_TroopValueState::instance.attackInfo.playerInfo - 1;

            // hack (wall-breaching) points
            playerRecords[attackingPlayerID].minHackLayerValue = 10000;
            for (int i = 0; i < playerRecords[attackingPlayerID].hack2; ++i) {
                int value = DAT_TileMapState::instance
                                .aiZoneDistanceLayers[attackedPlayerID][playerRecords[attackingPlayerID].field4_0x10[i * 4]];
                if (value < playerRecords[attackingPlayerID].minHackLayerValue) {
                    playerRecords[attackingPlayerID].minHackLayerValue = value;
                }
            }
            playerRecords[attackingPlayerID].hack3 = 0;
            for (int i = 0; i < playerRecords[attackingPlayerID].hack2; ++i) {
                int tile = playerRecords[attackingPlayerID].field4_0x10[i * 4];
                int value = DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile];
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadderInRightDirection,
                        DAT_UnitsState::ptr)(tile, DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile])
                    != 0) {
                    playerRecords[attackingPlayerID].field4_0x10[i * 4 + 2] = 9999;
                }
                else if (value <= 0) {
                    playerRecords[attackingPlayerID].field4_0x10[i * 4 + 2] = 9999;
                }
                else if (playerRecords[attackingPlayerID].minHackLayerValue >= 50) {
                    playerRecords[attackingPlayerID].field4_0x10[i * 4 + 2] = 9999;
                }
                else if (value >= playerRecords[attackingPlayerID].minHackLayerValue + 15) {
                    playerRecords[attackingPlayerID].field4_0x10[i * 4 + 2] = 9999;
                }
                else {
                    playerRecords[attackingPlayerID].hack3++;
                    playerRecords[attackingPlayerID].field4_0x10[i * 4 + 2] = value;
                }
            }

            // scale (ladder) points
            for (int i = 0; i < playerRecords[attackingPlayerID].scale2; ++i) {
                if (DAT_TileMapState::instance.aiZoneDistanceLayers
                        [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                        [playerRecords[attackingPlayerID].field31_0x3ebc[i][0]]
                    > 5) {
                    playerRecords[attackingPlayerID].field31_0x3ebc[i][2] = 9999;
                }
                else {
                    playerRecords[attackingPlayerID].field31_0x3ebc[i][2] = 0;
                }
            }

            // town (building) points
            for (int i = 0; i < playerRecords[attackingPlayerID].some1000ArrayIndex; ++i) {
                int value = DAT_TileMapState::instance.aiZoneDistanceLayers
                                [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                                [playerRecords[attackingPlayerID].some1000Array[i].tile];
                if (value <= 0) {
                    playerRecords[attackingPlayerID].some1000Array[i].field2_0x8 = 100;
                }
                else {
                    playerRecords[attackingPlayerID].some1000Array[i].field2_0x8 = value;
                }
            }

            // gate points
            playerRecords[attackingPlayerID].minGateLayerValue = 10000;
            for (int i = 0; i < playerRecords[attackingPlayerID].some1000ArrayIndex_2; ++i) {
                int value = DAT_TileMapState::instance.aiZoneDistanceLayers
                                [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                                [playerRecords[attackingPlayerID].field71_0xbbf4[i][0]];
                if (value < playerRecords[attackingPlayerID].minGateLayerValue) {
                    playerRecords[attackingPlayerID].minGateLayerValue = value;
                }
            }
            for (int i = 0; i < playerRecords[attackingPlayerID].some1000ArrayIndex_2; ++i) {
                int value = DAT_TileMapState::instance.aiZoneDistanceLayers
                                [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                                [playerRecords[attackingPlayerID].field71_0xbbf4[i][0]];
                if (playerRecords[attackingPlayerID].minGateLayerValue > 10) {
                    playerRecords[attackingPlayerID].field71_0xbbf4[i][2] = value > 20 ? 9999 : 0;
                }
                else {
                    playerRecords[attackingPlayerID].field71_0xbbf4[i][2] = value > 10 ? 9999 : 0;
                }
            }

            // wide points
            for (int i = 0; i < playerRecords[attackingPlayerID].wide2; ++i) {
                if (DAT_TileMapState::instance.aiZoneDistanceLayers
                        [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                        [playerRecords[attackingPlayerID].wideEntries[i][0]]
                    > 5) {
                    playerRecords[attackingPlayerID].wideEntries[i][2] = 9999;
                }
                else {
                    playerRecords[attackingPlayerID].wideEntries[i][2] = 0;
                }
            }

            // moat points
            for (int i = 0; i < playerRecords[attackingPlayerID].field89_0xfa88; ++i) {
                int value = DAT_TileMapState::instance.aiZoneDistanceLayers
                                [playerRecords[attackingPlayerID].currentPlayerID_OR_attackedPlayerID_OR_one]
                                [playerRecords[attackingPlayerID].moatEntries[i][0]];
                if (value <= 0) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = 9999;
                }
                else if (value <= 10) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value;
                }
                else if (value <= 15) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value * 2;
                }
                else if (value <= 20) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value * 3;
                }
                else if (value <= 25) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value * 4;
                }
                else if (value <= 50) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value * 5;
                }
                else if (value <= 70) {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = value * 6;
                }
                else {
                    playerRecords[attackingPlayerID].moatEntries[i][2] = 9999;
                }
            }
        }

    }
}
}
