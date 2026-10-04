#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2E00
    undefined4 LandscapeState::setupBabyTreeLocation(uint treeID, int treeType, uint x, uint y)
    {
        XYPair* pXVar1;
        byte bVar2;
        int iVar3;
        XYPair* pXVar4;
        int _treeID;
        uint _randomNumber;
        uint _newX;
        uint uVar5;
        uint _newY;
        int _newTile;
        int local_8;
        int _attempts;
        _randomNumber = (byte)SEC_RNG::instance.currentNumber2 & 7;
        local_8 = 3;
        if ((treeID & 1) != 0) {
            local_8 = 4;
        }
        DAT_PathFindingState::instance.ALG_ResultTile = 0;
        DAT_PathFindingState::instance.ALG_ResultY = 0;
        DAT_PathFindingState::instance.ALG_ResultX = 0;
        if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
            return (undefined4)(0);
        }
        uVar5 = (uint) * (byte*)(DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + 0x1d32c38 + x);
        _attempts = 0;
        do {
            pXVar1 = DAT_OrganismDefinedData::instance.TreeSpreadOffsets + _randomNumber;
            pXVar4 = DAT_OrganismDefinedData::instance.TreeSpreadOffsets + _randomNumber;
            _randomNumber = _randomNumber + 1;
            _newX = pXVar1->x + x;
            _newY = pXVar4->y + y;
            if (7 < (int)_randomNumber) {
                _randomNumber = 0;
            }
            if (((_newX < 400) && (_newY < 400)) && (*(char*)(_newY * 400 + 0x21aec98 + _newX) != '\0')) {
                iVar3 = DAT_ViewportRenderState::instance.translationMatrix[_newY].addXgetTile;
                bVar2 = *(byte*)(iVar3 + 0x1c471e8 + _newX);
                _newTile = iVar3 + _newX;
                if (((DAT_TileMapState::instance.OrganismLayer[_newTile] == 0)
                        && ((DAT_TileMapState::instance.LogicLayer[_newTile] & 0x703e25b5U) == 0))
                    && ((DAT_TileMapState::instance.UnitLayer[_newTile] == 0
                        && (DAT_TileMapState::instance.BuildingLayer[_newTile] == 0)))) {
                    if (treeType == 1) {
                        if ((bVar2 & 0x90) == 0) {
                        LAB_004f2f32:
                            if ((((uint)DAT_TileMapState::instance.HeightLayer[_newTile] <= uVar5 + 0x40)
                                    && ((int)(uVar5 - 0x40)
                                        <= (int)(uint)DAT_TileMapState::instance.HeightLayer[_newTile]))
                                && (_treeID = MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::setupBabyTreeLocationInfo,
                                        DAT_PathFindingState::ptr)(local_8, treeType, _newX, _newY),
                                    _treeID != 0)) {
                                DAT_PathFindingState::instance.ALG_ResultTile = _newTile;
                                DAT_PathFindingState::instance.ALG_ResultX = _newX;
                                DAT_PathFindingState::instance.ALG_ResultY = _newY;
                                return (undefined4)(1);
                            }
                        }
                    } else if ((bVar2 & 0x90) != 0)
                        goto LAB_004f2f32;
                }
            }
            _attempts = _attempts + 1;
            if (7 < _attempts) {
                return (undefined4)(0);
            }
        } while (true);
    }

}
}
