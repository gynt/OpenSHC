#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // The move speech gets DAT_TribesState::instance.DAT_CurrentTribeID (read at 0x5220F2), the selection sound
        // the argument's value from before getMajoritySelectedUnitType overwrote it (ebx, 0x5220A1).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522090
        void TribesState::playAttackCommandFeedback(int unusedOrMajorityTypeCount)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getRepresentativeSelectedUnitID, DAT_UnitsState::ptr)(
                1);
            int const selectionID = unusedOrMajorityTypeCount;
            UnitType const unitType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                unusedOrMajorityTypeCount, &unusedOrMajorityTypeCount);
            if (unitType == UT_S_BATTERINGRAM || unitType == UT_S_CATAPULT || unitType == UT_S_TREBUCHET
                || unitType == UT_S_MANGONEL || unitType == UT_S_BALLISTA || unitType == UT_S_FBALLISTA) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::playUnitMoveSpeech, this)(
                    DAT_TribesState::instance.DAT_CurrentTribeID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::playUnitSelectionSound, this)(selectionID);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    unitType, 0x15);
                if (unitType != UT_E_ENGINEER) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::playUnitSelectionSound, this)(
                        selectionID);
                }
            }
        }

    }
}
}
