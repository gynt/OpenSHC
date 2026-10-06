#include "../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

#include "OpenSHC/Globals/DAT_00ed31a0.hpp"
#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using Map::Trees::TreeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3D60
    void LandscapeState::updateTrees()
    {
        short* psVar1;
        uint uVar2;
        uint _loadBalanceValue;
        bool isItNOTScenarioGameMode;
        uint _balanceRNG;
        _balanceRNG = 0;
        DAT_GameState::instance.mapAndTime.burningTreeCount = 0;
        DAT_00ed31a0::instance = timeGetTime();
        if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 8) {
            this->maxTreeCount = 0;
            DAT_CurrentTreeID::instance = 1;
            do {
                if (this->trees[DAT_CurrentTreeID::instance].state != 0) {
                    this->maxTreeCount = DAT_CurrentTreeID::instance + 1;
                }
                DAT_CurrentTreeID::instance = DAT_CurrentTreeID::instance + 1;
            } while ((int)DAT_CurrentTreeID::instance < 2000);
        }
        /*
          0 to 7
         */
        _loadBalanceValue = DAT_GameState::instance.gameTicksLoadBalancer & 0x80000007;
        if ((int)_loadBalanceValue < 0) {
            /*
              -7 to 7
             */
            _loadBalanceValue = (_loadBalanceValue - 1 | 0xfffffff8) + 1;
        }
        if (_loadBalanceValue == 4) {
            _balanceRNG = (byte)SEC_RNG::instance.currentNumber2 & 0x3f;
        }
        isItNOTScenarioGameMode = DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR;
        this->field0_0x0 = 0;
        if ((!DAT_TileMapState::instance.refreshRelatedOne) || (DAT_TileMapState::instance.flatViewToggleValue1)) {
            this->field0_0x0 = 1;
        }
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        this->DAT_TotalOrganisms = 0;
        DAT_CurrentTreeID::instance = 1;
        if (1 < this->maxTreeCount) {
            do {
                switch (this->trees[DAT_CurrentTreeID::instance].state) {
                case 0:
                    break;
                case 1:
                    this->trees[DAT_CurrentTreeID::instance].state = 2;
                    break;
                default:
                    this->DAT_TotalOrganisms = this->DAT_TotalOrganisms + 1;
                    if (this->wind.countdown
                        <= (int)((byte)this->trees[DAT_CurrentTreeID::instance].yPosition & 0x1f)) {
                        this->trees[DAT_CurrentTreeID::instance].one = (short)this->wind.value;
                    }
                    if ((this->trees[DAT_CurrentTreeID::instance].one == 3)
                        && (this->trees[DAT_CurrentTreeID::instance].zeroUpTo2 == 0)) {
                        this->trees[DAT_CurrentTreeID::instance].zeroUpTo2 = 1;
                        this->trees[DAT_CurrentTreeID::instance].animationFrameIndex = 1;
                        this->trees[DAT_CurrentTreeID::instance].field8_0x14 = DAT_00ed31a0::instance;
                    }
                    if (this->trees[DAT_CurrentTreeID::instance].treeTypeRelated2
                        <= (int)(DAT_00ed31a0::instance - this->trees[DAT_CurrentTreeID::instance].field8_0x14)) {
                        this->trees[DAT_CurrentTreeID::instance].field8_0x14 = DAT_00ed31a0::instance;
                        if (this->trees[DAT_CurrentTreeID::instance].one != 0) {
                            psVar1 = &this->trees[DAT_CurrentTreeID::instance].animationFrameIndex;
                            *psVar1 = *psVar1 + 1;
                        }
                    }
                    psVar1 = &this->trees[DAT_CurrentTreeID::instance].rng200till300;
                    if (this->trees[DAT_CurrentTreeID::instance].rng200till300 != 0) {
                        *psVar1 = *psVar1 + -1;
                    }
                    uVar2 = DAT_CurrentTreeID::instance;
                    if (isItNOTScenarioGameMode && _loadBalanceValue == 4) {
                        MACRO_CALL_MEMBER(Map::LandscapeState_Func::updateTreeStage, this)(
                            DAT_CurrentTreeID::instance, _balanceRNG);
                    }
                    DAT_CurrentTreeID::instance = uVar2;
                    (*DAT_OrganismDefinedData::instance.UpdateTree[(short)this->trees[uVar2].treeType])();
                    if (this->trees[DAT_CurrentTreeID::instance].field92_0x98 != 0) {
                        if (this->trees[DAT_CurrentTreeID::instance].treeType != Map::Trees::TT_APPLEUnk) {
                            DAT_GameState::instance.mapAndTime.burningTreeCount
                                = DAT_GameState::instance.mapAndTime.burningTreeCount + 1;
                        }
                        if (1 < this->trees[DAT_CurrentTreeID::instance].field92_0x98) {
                            psVar1 = &this->trees[DAT_CurrentTreeID::instance].field92_0x98;
                            *psVar1 = *psVar1 + -1;
                        }
                    }
                    break;
                case 3:
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, this)(DAT_CurrentTreeID::instance);
                    break;
                case 4:
                    if (!this->field0_0x0) {
                        this->trees[DAT_CurrentTreeID::instance].animationFrameUnk
                            = this->trees[DAT_CurrentTreeID::instance].animationFrame2Unk;
                    } else {
                        this->trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0;
                    }
                }
                DAT_CurrentTreeID::instance = DAT_CurrentTreeID::instance + 1;
            } while ((int)DAT_CurrentTreeID::instance < this->maxTreeCount);
        }
    }

}
}
