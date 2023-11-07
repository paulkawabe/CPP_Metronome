/*
  ==============================================================================

    Metronome.cpp
    Created: 7 Nov 2023 9:20:11am
    Author:  Paul Kawabe

  ==============================================================================
*/

#include "Metronome.h"

void Metronome::prepareToPlay(double sampleRate)
{
    mSampleRate = sampleRate;
}

void Metronome::countSamples( int bufferSize )
{
    mTotalSamples+=bufferSize;
    std::cout << mTotalSamples << std::endl;
};

void Metronome::reset()
{
    mTotalSamples = 0;
};
