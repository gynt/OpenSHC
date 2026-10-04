#include "../../Game.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1700
    BOOLEnum Skirmish::StoreCurrentGameIntoTemporarySKMasterEntry(int score)
    {
        char cVar1;
        int iVar2;
        DAT_SkMasterDataEntry::instance.score = score;
        iVar2 = 0;
        do {
            cVar1 = DAT_GameSynchronyState::instance.mapName[iVar2];
            DAT_SkMasterDataEntry::instance.mapName[iVar2] = cVar1;
            iVar2 = iVar2 + 1;
        } while (cVar1 != '\0');
        DAT_SkMasterDataEntry::instance.skMasterScore = MACRO_CALL(
            UI::GreatestLord_Func::ComputeSkMasterScore)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        DAT_SkMasterDataEntry::instance.activePlayerCount = 0;
        iVar2 = 1;
        do {
            if (DAT_GameSynchronyState::instance.finalResults.active[iVar2] == 0)
                break;
            iVar2 = iVar2 + 1;
            DAT_SkMasterDataEntry::instance.activePlayerCount = DAT_SkMasterDataEntry::instance.activePlayerCount + 1;
        } while (iVar2 < 9);
        DAT_SkMasterDataEntry::instance.array1[1] = DAT_GameState::instance.mapAndTime.playerGroupArray[1];
        DAT_SkMasterDataEntry::instance.array1[2] = DAT_GameState::instance.mapAndTime.playerGroupArray[2];
        DAT_SkMasterDataEntry::instance.array1[3] = DAT_GameState::instance.mapAndTime.playerGroupArray[3];
        DAT_SkMasterDataEntry::instance.array1[4] = DAT_GameState::instance.mapAndTime.playerGroupArray[4];
        DAT_SkMasterDataEntry::instance.array1[5] = DAT_GameState::instance.mapAndTime.playerGroupArray[5];
        DAT_SkMasterDataEntry::instance.array1[6] = DAT_GameState::instance.mapAndTime.playerGroupArray[6];
        DAT_SkMasterDataEntry::instance.array1[7] = DAT_GameState::instance.mapAndTime.playerGroupArray[7];
        DAT_SkMasterDataEntry::instance.array1[8] = DAT_GameState::instance.mapAndTime.playerGroupArray[8];
        DAT_SkMasterDataEntry::instance.aiArray[1] = DAT_GameSynchronyState::instance.currentAIArray[1];
        DAT_SkMasterDataEntry::instance.aiArray[2] = DAT_GameSynchronyState::instance.currentAIArray[2];
        DAT_SkMasterDataEntry::instance.aiArray[3] = DAT_GameSynchronyState::instance.currentAIArray[3];
        DAT_SkMasterDataEntry::instance.aiArray[4] = DAT_GameSynchronyState::instance.currentAIArray[4];
        DAT_SkMasterDataEntry::instance.aiArray[5] = DAT_GameSynchronyState::instance.currentAIArray[5];
        DAT_SkMasterDataEntry::instance.aiArray[6] = DAT_GameSynchronyState::instance.currentAIArray[6];
        DAT_SkMasterDataEntry::instance.aliveArray[1] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[1];
        DAT_SkMasterDataEntry::instance.aiArray[7] = DAT_GameSynchronyState::instance.currentAIArray[7];
        DAT_SkMasterDataEntry::instance.aliveArray[2] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[2];
        DAT_SkMasterDataEntry::instance.aiArray[8] = DAT_GameSynchronyState::instance.currentAIArray[8];
        DAT_SkMasterDataEntry::instance.aliveArray[3] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[3];
        DAT_SkMasterDataEntry::instance.aliveArray[4] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[4];
        DAT_SkMasterDataEntry::instance.aliveArray[5] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[5];
        DAT_SkMasterDataEntry::instance.aliveArray[6] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[6];
        DAT_SkMasterDataEntry::instance.aliveArray[7] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[7];
        DAT_SkMasterDataEntry::instance.aliveArray[8] = (int)DAT_GameState::instance.mapAndTime.playerIsAlive[8];
        DAT_SkMasterDataEntry::instance.lordType = DAT_GameCore::instance.selectedLordTypeUnk;
        MACRO_CALL(Game::Skirmish_Func::StoreLocalTime)();
        int const* _src = (int const*)&DAT_GameSynchronyState::instance.finalResults;
        int* _dst = (int*)&DAT_SkMasterDataEntry::instance.results;
        for (int i = 0; i < 478; ++i) {
            _dst[i] = _src[i];
        }
        return TRUE;
    }

}
}
