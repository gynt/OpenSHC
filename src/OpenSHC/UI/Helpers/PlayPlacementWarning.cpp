#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004380E0
    void Helpers::PlayPlacementWarning(BuildingFailReasonEnum param_1)
    {
        switch (param_1) {
        case Map::Buildings::BFRE_NOT_ADJ_STOCKPILE:
            /*
              "Needs to be placed adjacent to the stockpile"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning2.wav");
            return;
        case Map::Buildings::BFRE_NOT_ADJ_ARMORY:
            /*
              "Needs to be placed adjacent to the armory"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning3.wav");
            return;
        case Map::Buildings::BFRE_NOT_IRON_ORE:
            /*
              "Iron mine must be built on iron ore"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning4.wav");
            return;
        case Map::Buildings::BFRE_NOT_OIL_MARSH:
            /*
              "Pitch rig must be built on oil in the marsh"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning5.wav");
            return;
        case Map::Buildings::BFRE_NOT_ADJ_GRANARY:
            /*
              "Needs to be placed adjacent to the granary"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning6.wav");
            return;
        case Map::Buildings::BFRE_MISSING5:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning20.wav");
            return;
        case Map::Buildings::BFRE_MISSING4:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning19.wav");
            return;
        case Map::Buildings::BFRE_MUST_BE_PLACED_ON_OASES:
            /*
              "Farms must be placed on oases"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning18.wav");
            return;
        case Map::Buildings::BFRE_MISSING2:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning21.wav");
            return;
        default:
            /*
              "Can't place that there my lord"
             */
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                "placement_warning16.wav");
        }
    }

}
}
