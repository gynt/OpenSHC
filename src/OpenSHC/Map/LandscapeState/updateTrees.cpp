#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/g_treeUpdateTime.hpp"

namespace OpenSHC {
namespace Map {

    // The loop counter is the global DAT_CurrentTreeID (signed compares jl 0x4F3DE6 / 0x4F3FFA). gameTicks % 10 and
    // % 8 are signed. Growth runs on tick % 8 == 4 unless gameMode_2 is the editor (the flag is cleared at 0x4F3E1A);
    // the tree ID is restored after updateTreeStage (0x4F3F99). Animation interval test is signed (jl 0x4F3F3A).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3D60
    void LandscapeState::updateTrees()
    {
        int growthTick = 0;
        uint growthRng = 0;
        DAT_GameState::instance.mapAndTime.treesLitThisPass = 0;
        g_treeUpdateTime::instance = timeGetTime();
        if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 8) {
            this->maxTreeCount = 0;
            for (DAT_CurrentTreeID::instance = 1; (int)DAT_CurrentTreeID::instance < 2000;
                 DAT_CurrentTreeID::instance++) {
                if (this->trees[DAT_CurrentTreeID::instance].state != 0) {
                    this->maxTreeCount = DAT_CurrentTreeID::instance + 1;
                }
            }
        }
        if (DAT_GameState::instance.gameTicksLoadBalancer % 8 == 4) {
            growthTick = 1;
            growthRng = SEC_RNG::instance.currentNumber2 & 0x3f;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            growthTick = 0;
        }
        this->treeAnimFrozen = 0;
        if (DAT_TileMapState::instance.fullHeightViewActive == 0 || DAT_TileMapState::instance.flatViewToggleValue1 != 0) {
            this->treeAnimFrozen = 1;
        }
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        this->DAT_TotalOrganisms = 0;
        for (DAT_CurrentTreeID::instance = 1; (int)DAT_CurrentTreeID::instance < this->maxTreeCount;
             DAT_CurrentTreeID::instance++) {
            switch (this->trees[DAT_CurrentTreeID::instance].state) {
            case 0:
                break;
            case 1:
                this->trees[DAT_CurrentTreeID::instance].state = 2;
                break;
            case 4:
                if (this->treeAnimFrozen != 0) {
                    this->trees[DAT_CurrentTreeID::instance].currentGmFrame = 0;
                }
                else {
                    this->trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = this->trees[DAT_CurrentTreeID::instance].fixedGmFrame;
                }
                break;
            case 3:
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, this)(DAT_CurrentTreeID::instance);
                break;
            default:
                this->DAT_TotalOrganisms++;
                if ((this->trees[DAT_CurrentTreeID::instance].yPosition & 0x1f) >= this->wind.countdown) {
                    this->trees[DAT_CurrentTreeID::instance].windState = (short)this->wind.value;
                }
                if (this->trees[DAT_CurrentTreeID::instance].windState == 3
                    && this->trees[DAT_CurrentTreeID::instance].fellState == 0) {
                    this->trees[DAT_CurrentTreeID::instance].fellState = 1;
                    this->trees[DAT_CurrentTreeID::instance].animationFrameIndex = 1;
                    this->trees[DAT_CurrentTreeID::instance].lastFrameTimeMs = g_treeUpdateTime::instance;
                }
                if ((int)(g_treeUpdateTime::instance - this->trees[DAT_CurrentTreeID::instance].lastFrameTimeMs)
                    >= this->trees[DAT_CurrentTreeID::instance].animFrameIntervalMs) {
                    this->trees[DAT_CurrentTreeID::instance].lastFrameTimeMs = g_treeUpdateTime::instance;
                    if (this->trees[DAT_CurrentTreeID::instance].windState != 0) {
                        this->trees[DAT_CurrentTreeID::instance].animationFrameIndex++;
                    }
                }
                if (this->trees[DAT_CurrentTreeID::instance].crowCooldown != 0) {
                    this->trees[DAT_CurrentTreeID::instance].crowCooldown--;
                }
                if (growthTick) {
                    uint const treeID = DAT_CurrentTreeID::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::updateTreeStage, this)(treeID, growthRng);
                    DAT_CurrentTreeID::instance = treeID;
                }
                DAT_OrganismDefinedData::instance.UpdateTree[this->trees[DAT_CurrentTreeID::instance].treeType]();
                if (this->trees[DAT_CurrentTreeID::instance].burnTimer != 0) {
                    if (this->trees[DAT_CurrentTreeID::instance].treeType != OpenSHC::Map::Trees::TT_APPLE) {
                        DAT_GameState::instance.mapAndTime.treesLitThisPass++;
                    }
                    if (this->trees[DAT_CurrentTreeID::instance].burnTimer > 1) {
                        this->trees[DAT_CurrentTreeID::instance].burnTimer--;
                    }
                }
                break;
            }
        }
    }

}
}
