#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // OrganismLayer of each of the 8 neighbour tiles is read once (movzx, then movsx for treeID < maxTreeCount,
    // signed jge 0x4F31B6). Keep distance = max(|dx|, |dy|) (cdq/xor/sub), closer only when < best (signed jge).
    // Jitter uses signed currentNumber2 % 5 - 2 and (currentNumber2 >> 8) % 5 - 2 (movsx/sar/idiv); without any
    // keep the target is unit +-50 from % 100 and the RNG is advanced. Player loop 1..8 is unrolled 4x in the
    // original (0x4F3216..0x4F343C).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3150
    void LandscapeState::spawnCrowFromNearbyTree(int unitID)
    {
        BOOL sfxPlayed = FALSE;
        for (int direction = 0; direction < 8; direction++) {
            int const unitY = DAT_UnitsState::instance.units[unitID].y;
            short const organismID = DAT_TileMapState::instance.OrganismLayer
                                         [DAT_TileMapState::instance.directionTranslationMatrix[unitY][direction]
                                             + DAT_UnitsState::instance.units[unitID].tile];
            if (organismID == 0) {
                continue;
            }
            int const treeID = organismID;
            if (treeID >= this->maxTreeCount) {
                continue;
            }
            if (this->trees[treeID].state != 2) {
                continue;
            }
            if (this->trees[treeID].hasCrows == 0) {
                continue;
            }
            if (this->trees[treeID].crowCooldown != 0) {
                continue;
            }
            int const ownerID = DAT_UnitsState::instance.units[unitID].owner;
            int targetX = 0;
            int targetY = 0;
            int bestDistance = 10000;
            for (int playerID = 1; playerID < 9; playerID++) {
                if (playerID == ownerID) {
                    continue;
                }
                if (DAT_GameState::instance.playerDataArray[playerID].keep.id == 0) {
                    continue;
                }
                int const keepX = DAT_GameState::instance.playerDataArray[playerID].keep.xEntry;
                int const keepY = DAT_GameState::instance.playerDataArray[playerID].keep.yEntry;
                int const distanceX = abs(DAT_UnitsState::instance.units[unitID].x - keepX);
                int const distanceY = abs(unitY - keepY);
                int const distance = distanceX > distanceY ? distanceX : distanceY;
                if (distance < bestDistance) {
                    targetX = SEC_RNG::instance.currentNumber2 % 5 - 2 + keepX;
                    targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 5 - 2 + keepY;
                    bestDistance = distance;
                }
            }
            if (bestDistance == 10000) {
                targetX = DAT_UnitsState::instance.units[unitID].x + SEC_RNG::instance.currentNumber2 % 100 - 50;
                targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 100 - 50 + unitY;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(unitID,
                DAT_UnitsState::instance.units[unitID].owner, 0, (short)this->trees[treeID].xPosition * 8,
                (short)this->trees[treeID].yPosition * 8, DAT_TileMapState::instance.HeightLayer[this->trees[treeID].tile] + 30, targetX * 8,
                targetY * 8, 250, OpenSHC::Map::Entities::ET_CROW, 0);
            this->trees[treeID].crowCooldown = SEC_RNG::instance.currentNumber2 % 100 + 200;
            if (!sfxPlayed) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (short)this->trees[treeID].xPosition, (short)this->trees[treeID].yPosition, OpenSHC::DE::SHCDE::FX_CROW);
                sfxPlayed = TRUE;
            }
        }
    }

}
}
