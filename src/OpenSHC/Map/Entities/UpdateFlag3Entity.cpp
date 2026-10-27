#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402A20
    void Entities::UpdateFlag3Entity()
    {
        int frameOffset;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if ((int)((byte)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime
                = (short)DAT_LandscapeState::instance.wind.value;
        }
        switch (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState) {
        case 0:
            frameOffset = DAT_EntityDefinedData::instance
                              .flag3WaveFramesState0[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                         .animFrameCounter];
            if (frameOffset <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime;
                return;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameOffset - 1;
            return;
        case 1:
        case 2:
            frameOffset
                = DAT_EntityDefinedData::instance
                      .flag3WaveFramesState12[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                  .animFrameCounter];
            if (frameOffset <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime;
                return;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameOffset - 1;
            return;
        }
    }

}
}
