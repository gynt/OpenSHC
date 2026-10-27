#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458990
    void GameStateStructures::setVariousGameStateToInitialValues()
    {
        this->mapAndTime.totalGameTicks = 0;
        this->mapAndTime.lightningCounter = 0;
        this->mapAndTime.lightningPower = 5;
        this->mapAndTime.gameOver = FALSE;
        this->mapAndTime.singlePlayerHasKeepAndGranary = FALSE;
        this->mapAndTime.eventCountdownRabbitInfestation = 0;
        this->mapAndTime.invasionNextMonthCountdown = 0;
        this->mapAndTime.signpostExclusionRadius = 30;
        this->mapAndTime.invasionImminent = 0;
    }

}
}
