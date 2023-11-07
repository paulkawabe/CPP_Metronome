/*
  ==============================================================================

    Metronome.h
    Created: 7 Nov 2023 9:20:11am
    Author:  Paul Kawabe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome
{
public:
    void prepareToPlay(double sampleRate);
    void countSamples( int bufferSize );
    void reset();
    
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
    
    
};
