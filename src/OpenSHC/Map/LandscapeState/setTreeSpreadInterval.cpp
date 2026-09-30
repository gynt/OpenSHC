#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2CC0
    void LandscapeState::setTreeSpreadInterval()
    {
        if (this->DAT_TotalOrganisms < 0xb) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 0x14;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x65) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 0xf;
            return;
        }

        if (this->DAT_TotalOrganisms < 0xc9) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 10;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x12d) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 9;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x191) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 8;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x259) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 7;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x321) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 6;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x3e9) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 5;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x4b1) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 4;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x579) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 3;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x641) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 2;
            return;
        }

        if (this->DAT_TotalOrganisms < 0x709) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 1;
            return;
        }

        DAT_GameState::instance.mapAndTime.treeSpreadInterval = 0;
    }

}
}
