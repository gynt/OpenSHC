#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Audio::SFX::SpeechEffectID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521EF0
        void TribesState::playUnitMoveSpeech(undefined4 param_1)
        {
            int _unitID;
            UnitType _unitTypeID;
            _unitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            /*
              bug: the second argument ("stack") does not want to be renamed, but is   sfxToPlay again.
             */
            _unitTypeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                (Ghidra::undefined4)(param_1), (int*)(&param_1));
            switch (_unitTypeID) {
            case OpenSHC::Map::Units::UT_E_ARCHER:
            case OpenSHC::Map::Units::UT_E_XBOW:
            case OpenSHC::Map::Units::UT_A_ARCHER:
            case OpenSHC::Map::Units::UT_A_SLINGER:
            case OpenSHC::Map::Units::UT_A_HARCHER:
            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                /*
                  Any other ranged unit
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    _unitTypeID, 0x1d);
                return;
            case OpenSHC::Map::Units::UT_S_CATAPULT:
                /*
                  Catapult
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[_unitID].stoneAmmunition < 1) {
                        param_1 = 0x2e;
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x10);
                }
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                /*
                  Trebuchet
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[_unitID].stoneAmmunition < 1) {
                        param_1 = 0x2e;
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x11);
                }
                break;
            case OpenSHC::Map::Units::UT_S_MANGONEL:
                /*
                  Mangonel
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0xf);
                }
                break;
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                /*
                  Battering ram
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x13);
                }
                break;
            case OpenSHC::Map::Units::UT_S_BALLISTA:
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                /*
                  Ballista and fire ballista
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x12);
                }
            }
        }

    }
}
}
