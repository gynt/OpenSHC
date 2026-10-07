#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Game/ScenarioEvents/IngameScenarioEventItemContent.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::ScenarioEvents::IngameScenarioEventItemContent;
    using Map::MapType2;
    using Map::Units::Unit;
    using Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7980
    void MapPropertiesState::determineScenarioMissionTypeAndResetEvents()
    {
        int iVar1;
        bool bVar2;
        byte bVar3;
        Unit* psVar5;
        Unit* psVar4;
        SiegeUnitCounts* pSVar4;
        SiegeGameModeRelatedSection* pSVar5;
        int iVar6;
        bVar2 = false;
        bVar3 = 0;
        for (int _eventID = 0; _eventID < this->eventsCount; _eventID++) {
            if (this->scenarioEvents[_eventID].header.tl_type == 1) {
                bVar2 = true;
            } else if ((this->scenarioEvents[_eventID].header.tl_type == 3)
                && (iVar1 = this->scenarioEvents[_eventID].data.scenario.ScenarioEventType, -1 < iVar1)
                && ((iVar1 < 2) || (iVar1 == 0x1a))) {
                bVar3 = 1;
            }
        }
        psVar5 = &DAT_UnitsState::instance.units[1];
        do {
            if ((psVar5->logicalState != Map::Units::ULS_INVISIBLE) && (1 < psVar5->owner)) {
                bVar2 = true;
                break;
            }
            psVar5 = psVar5 + 0x248;
        } while ((int)psVar5 < 0x1651422);
        if (this->SEC_U3_MapType2_1 == Map::MT_SIEGE) {
            iVar6 = 0;
            pSVar4 = &this->SEC_SiegeInformation;
            do {
                if (pSVar4->archers) {
                    bVar2 = true;
                    break;
                }
                iVar6 = iVar6 + 1;
                pSVar4 = (SiegeUnitCounts*)&pSVar4->crossbowmen;
            } while (iVar6 < 0x14);
            iVar6 = 0;
            pSVar5 = &this->SEC_Section1067;
            do {
                if (pSVar5->field0_0x0)
                    goto LAB_004b7a45;
                iVar6 = iVar6 + 1;
                pSVar5 = (SiegeGameModeRelatedSection*)&pSVar5->field1_0x4;
            } while (iVar6 < 6);
        }
        if (bVar2) {
        LAB_004b7a45:
            this->scenarionMissionType = (this->SEC_U3_MapType2_1 != Map::MT_SIEGE) + 2;
        } else {
            this->scenarionMissionType = (int)bVar3;
        }
        DAT_GameState::instance.mapAndTime.month = this->SEC_StartingMonth;
        DAT_GameState::instance.mapAndTime.year = this->SEC_StartingYear;
        iVar6 = 0;
        if (0 < this->eventsCount) {
            psVar4 = (Map::Units::Unit*)(&this->scenarioEvents[0].header.pre_done);
            do {
                psVar4->moveRelatedFlag = 0;
                psVar4->owner = 0;
                iVar6 = iVar6 + 1;
                psVar4 = (Unit*)(psVar4->pathPlanStart + 0x7c);
            } while (iVar6 < this->eventsCount);
        }
    }

}
}
