#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // The argument is only forwarded to getMajoritySelectedUnitType (which ignores it) and then holds the count.
        // FUNCTION: STRONGHOLDCRUSADER 0x005217E0
        void TribesState::playUnitSelectionSound(int selectionIdOrCount)
        {
            int const selectedUnitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::getRepresentativeSelectedUnitID, DAT_UnitsState::ptr)(1);
            UnitType const unitType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                selectionIdOrCount, &selectionIdOrCount);
            switch (unitType) {
            case UT_E_SWORD:
                if (selectionIdOrCount == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xad);
                } else if (selectionIdOrCount == 2) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xae);
                } else if (selectionIdOrCount >= 3) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xaf);
                }
                break;
            case UT_E_KNIGHT: {
                int const count = selectionIdOrCount;
                if (count == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x56);
                } else {
                    if (count == 2 || count == 3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[selectedUnitID].x,
                            DAT_UnitsState::instance.units[selectedUnitID].y, 0x57);
                    }
                    if (count >= 4) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[selectedUnitID].x,
                            DAT_UnitsState::instance.units[selectedUnitID].y, 0x58);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[selectedUnitID].x, DAT_UnitsState::instance.units[selectedUnitID].y,
                    0x59);
                break;
            }
            case UT_A_HARCHER:
                if (selectionIdOrCount == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xea);
                } else if (selectionIdOrCount <= 4) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xeb);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xec);
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[selectedUnitID].x, DAT_UnitsState::instance.units[selectedUnitID].y,
                    0x59);
                break;
            case UT_S_CATAPULT:
            case UT_S_TOWER:
            case UT_S_BATTERINGRAM: {
                int const missingEngineers = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers, DAT_UnitsState::ptr)(
                    selectedUnitID);
                if (missingEngineers > 0) {
                    if (DAT_UnitsState::instance.units[selectedUnitID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            == 0
                        || missingEngineers > 3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xe);
                    } else if (missingEngineers == 1) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xb);
                    } else if (missingEngineers == 2) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xc);
                    } else if (missingEngineers == 3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xd);
                    }
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x68);
                }
                break;
            }
            case UT_E_ENGINEER:
                if (DAT_UnitsState::instance.units[selectedUnitID].unitType == UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[selectedUnitID].resourceToDeposit != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                        0x24);
                }
                break;
            }
        }

    }
}
}
