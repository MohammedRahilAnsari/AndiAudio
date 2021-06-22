#ifndef ANDI_AUDIO_AUDIOENGINE_H
#define ANDI_AUDIO_AUDIOENGINE_H

#include <Oboe/Oboe.h>
#include <vector>
#include <array>
#include "SineWaveGenerator.h"

class AudioEngine :
        public oboe::AudioStreamDataCallback,
        public oboe::AudioStreamErrorCallback{
public :
            AudioEngine();
            void start();
            void stop();
            void setIsPlaying(bool isPlaying);
            void setTempo(int tempo);
            void setStepIsActive(int step, bool isActive);
            void setStepPitch(int step, int pitch);

            int getCurrentStep();

oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeSteam, void *audioData, int32_t numFrames)override;
void onErrorAfterClose(oboe::AudioStream *oboeSteam, oboe::Result error)override;

private:    void setSampleRate(float sampleRate);
            void updateSequencePhaseIncrement();
            float pitchToFrequency(int pitch);

private:
            float mSampleRate = 0.f;
            std::shared_ptr<oboe::AudioStream> mStream;
            bool mIsPlaying = false;

            SineWaveGenerator mSineWaveGen;
            std::vector<float> mSineBuffer;

    // Sequencing related
    static constexpr int kSequencerStepsCount = 8;
    double mSequencePhase = 0.f;
    double mSequencePhaseIncrement = 0.f;
    float mTempo = 120;
    int mCurrentStep = 0;
    std::array<bool, kSequencerStepsCount> mIsStepActive;
    std::array<int, kSequencerStepsCount> mStepPitch;
};

#endif //ANDI_AUDIO_AUDIOENGINE_H