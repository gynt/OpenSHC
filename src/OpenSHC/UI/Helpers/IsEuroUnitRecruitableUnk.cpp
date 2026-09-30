#include "../Helpers.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Map::Units::EuroRecruitableState;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00464DA0
    EuroRecruitableState Helpers::IsEuroUnitRecruitableUnk(int barrackUnitIdUnk)
    {
        int* _unitResourceCostPtr;
        int _loopCounterUnk;
        bool _noResourceUnk;
        int _resourceCost;
        ResourceTypeInt _unitGoldCost = DAT_TroopDefinedData::instance.MarketResourceCycleArray[barrackUnitIdUnk + -1];
        if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0)) {
            _unitGoldCost = ((ResourceType)0);
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[barrackUnitIdUnk + -0x16] == 0) {
            return OpenSHC::Map::Units::ERS_NOT_ALLOWED_TO_RECRUIT;
        }
        if (DAT_GameState::instance.mapAndTime.armySizeLimit
            <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].count_2
                + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .armySize) {
            return OpenSHC::Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentResources[0xf]
            < (int)_unitGoldCost) {
            return OpenSHC::Map::Units::ERS_CAN_NOT_RECRUIT;
        }
        _loopCounterUnk = 0;
        _unitResourceCostPtr = DAT_UnitPropertiesDefinedData::instance.MELEE_DAMAGE[0x4e] + barrackUnitIdUnk * 4 + 0x48;
        do {
            _resourceCost = *_unitResourceCostPtr;
            if (_resourceCost == -1) {
                _noResourceUnk
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .availableHorses
                    == 0;
            LAB_00464e3f:
                if (_noResourceUnk) {
                    return OpenSHC::Map::Units::ERS_CAN_NOT_RECRUIT;
                }
            } else if (_resourceCost != 0) {
                _noResourceUnk
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[_resourceCost]
                    == 0;
                goto LAB_00464e3f;
            }
            _loopCounterUnk = _loopCounterUnk + 1;
            _unitResourceCostPtr = _unitResourceCostPtr + 1;
            if (3 < _loopCounterUnk) {
                _loopCounterUnk
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .availablePeasantsOrHousedPeasants;
                _resourceCost
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .count;
                if (_resourceCost < _loopCounterUnk) {
                    return OpenSHC::Map::Units::ERS_CAN_RECRUITUnk;
                }
                return OpenSHC::Map::Units::ERS_UNABLE_MISSING_PEASANTS;
            }
        } while (true);
    }

}
}
