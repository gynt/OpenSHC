#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004660F0
    void Actions::ProcessBuildingSleepUpdate(int playerID, int buildingType)
    {
        undefined1* puVar1;
        bool bVar2;
        char* wav_filename;
        if (0x5a < buildingType) {}
        puVar1 = (undefined1*)(playerID * 0x39f4 + 0x115df8c + buildingType);
        if (*(char*)(playerID * 0x39f4 + 0x115df8c + buildingType) == '\0') {
            /*
              if building type is not snoozed:
             */
            bVar2 = playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID;
            *puVar1 = 1;
            if (bVar2)
                goto LAB_00466144;
            /*
              work halted my lord
             */
            wav_filename = "other_warning12.wav";
        } else {
            bVar2 = playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID;
            *puVar1 = 0;
            if (bVar2)
                goto LAB_00466144;
            /*
              "this building is currently function my lord"
             */
            wav_filename = "other_warning7.wav";
        }
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(wav_filename);
    LAB_00466144:
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateAllBuildingsSnoozedState,
            DAT_BuildingsState::ptr)(playerID, buildingType);
    }

}
}
