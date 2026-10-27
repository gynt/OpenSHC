#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BC70
        void TroopValueState::addUnitToNewTribe(
            undefined4 unitID, int attackWave, AITribeType tribeType, undefined4 playerID)
        {
            int tribeID;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                tribeID = MACRO_CALL_MEMBER(TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            } else {
                int playerIDForWave
                    = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
                if (playerIDForWave == 0) {
                    playerIDForWave = 2;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    playerIDForWave = 2;
                }
                tribeID = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(playerIDForWave, 0);
                DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_6;
            }
            DAT_TribesState::instance.tribes[tribeID].tribeType = tribeType;
            DAT_TribesState::instance.tribes[tribeID].attackWave = attackWave;
            DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1 = 0;
            MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
        }

    }
}
}
