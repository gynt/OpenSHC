#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_AmbientStreamFadeState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"
#include "OpenSHC/Globals/ambientLoopFadeLevel.hpp"
#include "OpenSHC/Globals/ambientLoopIdleTime.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044ABB0
        void SFXState::tweakVolume(int param_1, float param_2, int currentStreamID)
        {
            if (!MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::isInGameView, DAT_GameCore::ptr)()) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_AMBIENT_2);
                DAT_AmbientStreamFadeState::instance = 0;
                DAT_SpeechDefinedData::instance.stream2AmbientType = -1;
                return;
            }
            if (DAT_SpeechDefinedData::instance.stream2AmbientType == -1) {
                ambientLoopIdleTime::instance += param_2;
            } else {
                ambientLoopIdleTime::instance = 0.0f;
            }
            if (DAT_AmbientStreamFadeState::instance != 0 && DAT_SpeechDefinedData::instance.stream2AmbientType == -1) {
                DAT_AmbientStreamFadeState::instance = 0;
            } else {
                if (DAT_AmbientStreamFadeState::instance == 1) {
                    ambientLoopFadeLevel::instance += param_2 + param_2;
                    if (100.0 < ambientLoopFadeLevel::instance) {
                        DAT_AmbientStreamFadeState::instance = 100;
                    }
                    if (DAT_SpeechDefinedData::instance.stream2AmbientType == 7) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamFileVolume,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_AMBIENT_2,
                            (int)((DAT_SpeechDefinedData::instance.ambientSfxTable[5].variationVolumes
                                          [DAT_SpeechDefinedData::instance.ambientSfxTable[5].nextVariantIndex]
                                      * ambientLoopFadeLevel::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.stream2AmbientType == 8) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamFileVolume,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_AMBIENT_2,
                            (int)((DAT_SpeechDefinedData::instance.ambientSfxTable[6].variationVolumes
                                          [DAT_SpeechDefinedData::instance.ambientSfxTable[6].nextVariantIndex]
                                      * ambientLoopFadeLevel::instance)
                                / 100.0));
                    }
                    if (!(ambientLoopFadeLevel::instance >= 100.0f)) {
                        return;
                    }
                    DAT_AmbientStreamFadeState::instance = 0;
                    return;
                }
                if (DAT_AmbientStreamFadeState::instance == 2) {
                    ambientLoopFadeLevel::instance -= 2 * param_2;
                    if (ambientLoopFadeLevel::instance < 1.0) {
                        ambientLoopFadeLevel::instance = 1.0;
                    }
                    if (DAT_SpeechDefinedData::instance.stream2AmbientType == 7) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamFileVolume,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_AMBIENT_2,
                            (int)((DAT_SpeechDefinedData::instance.ambientSfxTable[5].variationVolumes
                                          [DAT_SpeechDefinedData::instance.ambientSfxTable[5].nextVariantIndex]
                                      * ambientLoopFadeLevel::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.stream2AmbientType == 8) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamFileVolume,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_AMBIENT_2,
                            (int)((DAT_SpeechDefinedData::instance.ambientSfxTable[6].variationVolumes
                                          [DAT_SpeechDefinedData::instance.ambientSfxTable[6].nextVariantIndex]
                                      * ambientLoopFadeLevel::instance)
                                / 100.0));
                    }
                    if (ambientLoopFadeLevel::instance <= 1.0) {
                        DAT_AmbientStreamFadeState::instance = 0;
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_AMBIENT_2);
                        DAT_SpeechDefinedData::instance.stream2AmbientType = -1;
                    }
                }
                if (DAT_SpeechDefinedData::instance.stream2AmbientType == -1
                    || MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_AMBIENT_2)) {
                    if (0 < DAT_SpeechDefinedData::instance.stream2AmbientType
                        && DAT_SpeechDefinedData::instance.stream2AmbientType != param_1) {
                        if (DAT_AmbientStreamFadeState::instance == 2) {
                            return;
                        }
                        ambientLoopFadeLevel::instance = 100.0;
                        DAT_AmbientStreamFadeState::instance = 2;
                        return;
                    }
                } else {
                    DAT_SpeechDefinedData::instance.stream2AmbientType = -1;
                }
            }
            if (param_1 <= 0 || DAT_SpeechDefinedData::instance.stream2AmbientType == param_1
                || (ambientLoopIdleTime::instance < 900.0 && param_1 == 8)) {
                return;
            }
            switch (param_1) {
            case 7:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playNextAmbientSoundIfStream2Idle, this)(5);
                ambientLoopFadeLevel::instance = 1.0;
                DAT_SpeechDefinedData::instance.stream2AmbientType = 7;
                DAT_AmbientStreamFadeState::instance = 1;
                DAT_SoundSystemState::instance.streamUnduckedFileVolume[2] = 1;
                break;
            case 8:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playNextAmbientSoundIfStream2Idle, this)(6);
                DAT_SpeechDefinedData::instance.stream2AmbientType = 8;
                break;
            }
        }

    }
}
}
