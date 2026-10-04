#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Game::GameMode;
        using Map::Entities::EntityType;
        using Map::Units::States::UnitState;
        using Map::Units::States::UnitStateShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x004016E0
        int EntityState::somethingWithSeparateAreas1(int unitID)
        {
            short sVar1;
            UnitStateShort UVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            Entity* pEVar6;
            int local_8;
            ushort _separateAreaNumber;
            _separateAreaNumber
                = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            iVar4 = 1;
            local_8 = 0;
            iVar5 = 10000;
            iVar3 = 0;
            if (1 < this->maxEntityCount) {
                pEVar6 = &this->entityArray[1];
                do {
                    if ((((pEVar6->logicalState == 2)
                             && (pEVar6->entityType == Map::Entities::ET_COW_POISON_CLOUD))
                            && (pEVar6->unknownAnimationFrameRelated < 0x3e9))
                        && (pEVar6->unknownDistanceRelatedValue == 0)) {
                        sVar1 = pEVar6->unitID_healer;
                        if (sVar1 != 0) {
                            if ((pEVar6->unitUID == DAT_UnitsState::instance.units[sVar1].uid)
                                && ((UVar2 = DAT_UnitsState::instance.units[sVar1].state.generic,
                                    UVar2 == Map::Units::States::US_AIM_WEAPONUnk
                                        || (UVar2 == Map::Units::States::US_FIRE_WEAPONUnk))))
                                goto LAB_0040184d;
                            pEVar6->unitID_healer = 0;
                        }
                        if (((((int)(short)DAT_TileMapState::instance.PathConnectionLayer[pEVar6->tile]
                                  == (int)(short)_separateAreaNumber)
                                 || (iVar3 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                         DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[unitID].owner,
                                         (dword)((int)((int)(short)_separateAreaNumber)),
                                         (dword)((int)((
                                             int)(short)DAT_TileMapState::instance.PathConnectionLayer[pEVar6->tile])),
                                         0),
                                     iVar3 != 0))
                                && ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                                    || ((iVar3 = (int)DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1,
                                        iVar3 == 0
                                            || (MACRO_CALL_MEMBER(
                                                    Map::Navigation::DirectionAlgorithmState_Func::
                                                        setAxisBasedDistanceResult,
                                                    DAT_DirectionAlgorithmState::ptr)(
                                                    (int)(short)DAT_BuildingsState::instance.buildings[iVar3].x,
                                                    (int)((
                                                        int)((short)DAT_BuildingsState::instance.buildings[iVar3].y)),
                                                    (int)((int)(pEVar6->xPosition)), (int)((int)(pEVar6->yPosition))),
                                                DAT_DirectionAlgorithmState::instance.distanceHigh < 0x1f))))))
                            && (MACRO_CALL_MEMBER(
                                    Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                                    (int)((int)(DAT_UnitsState::instance.units[unitID].y)),
                                    (int)((int)(pEVar6->xPosition)), (int)((int)(pEVar6->yPosition))),
                                DAT_DirectionAlgorithmState::instance.distanceHigh < iVar5)) {
                            iVar5 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            local_8 = iVar4;
                        }
                    }
                LAB_0040184d:
                    iVar4 = iVar4 + 1;
                    pEVar6 = pEVar6 + 0x74;
                    iVar3 = local_8;
                } while (iVar4 < this->maxEntityCount);
            }
            return iVar3;
        }

    }
}
}
