/*
  ==============================================================================

    Metronome.h
    Created: 7 Nov 2023 9:20:11am
    Author:  Paul Kawabe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome : public juce::HighResolutionTimer
{
public:
    Metronome();
    
    void prepareToPlay(int samplesPerBlockExpected,double sampleRate);
    void getNextAudioBlock( const juce::AudioSourceChannelInfo& bufferToFill );
    void reset();
    
    void hiResTimerCallback() override;
    
    int getTotalSamples()
    {
        return mTotalSamples;
    };
    
    double getSampleRate()
    {
        return mSampleRate;
    };
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    int mUpdateInterval { 0 };
    int mBpm { 120 };
    int mSamplesRemaining { 0 };
    
    juce::AudioFormatManager mFormatManager;
    std::unique_ptr <juce::AudioFormatReaderSource> pMetronomeSample { nullptr };
    
};
