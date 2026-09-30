#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051BC70
        void TroopValueState::addUnitToNewTribe(
            undefined4 unitID, int attackWave, AITribeType tribeType, undefined4 playerID)
        {
            int _tribe;
            int _playerID;
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                _playerID = (int)(char)this->attackInfo.attackWavePlayerIDArray[attackWave];
                if (_playerID == 0) {
                    _playerID = 2;
                }
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                    && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
                    _playerID = 2;
                }
                _tribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                    _playerID, 0);
                DAT_TribesState::instance.tribes[_tribe].tribeBehaviorType = OpenSHC::Map::Units::STBT_6;
            } else {
                _tribe = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            }
            DAT_TribesState::instance.tribes[_tribe].tribeType = (undefined2)tribeType;
            DAT_TribesState::instance.tribes[_tribe].attackWave = (short)attackWave;
            DAT_TribesState::instance.tribes[_tribe].attackInfo_someCounter1 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                unitID, _tribe);
        }

    }
}
}
