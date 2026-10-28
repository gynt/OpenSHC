#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521EF0
        void TribesState::playUnitMoveSpeech(undefined4 selectionIdOrCount)
        {
            int const selectedUnitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::getRepresentativeSelectedUnitID, DAT_UnitsState::ptr)(1);
            UnitType const unitType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                selectionIdOrCount, (int*)&selectionIdOrCount);
            switch (unitType) {
            case UT_E_ARCHER:
            case UT_E_XBOW:
            case UT_A_ARCHER:
            case UT_A_SLINGER:
            case UT_A_HARCHER:
            case UT_A_FIRETHROWER:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    unitType, 0x1d);
                break;
            case UT_S_CATAPULT:
                if (DAT_UnitsState::instance.units[selectedUnitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[selectedUnitID].stoneAmmunition < 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                            unitType, 0x10);
                    }
                }
                break;
            case UT_S_TREBUCHET:
                if (DAT_UnitsState::instance.units[selectedUnitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[selectedUnitID].stoneAmmunition < 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                            unitType, 0x11);
                    }
                }
                break;
            case UT_S_MANGONEL:
                if (DAT_UnitsState::instance.units[selectedUnitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0xf);
                }
                break;
            case UT_S_BATTERINGRAM:
                if (DAT_UnitsState::instance.units[selectedUnitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x13);
                }
                break;
            case UT_S_BALLISTA:
            case UT_S_FBALLISTA:
                if (DAT_UnitsState::instance.units[selectedUnitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x12);
                }
                break;
            }
        }

    }
}
}
