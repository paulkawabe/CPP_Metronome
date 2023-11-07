/*
  ==============================================================================

    Metronome.cpp
    Created: 7 Nov 2023 9:20:11am
    Author:  Paul Kawabe

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{
    mFormatManager.registerBasicFormats();
    juce::File myFile { juce::File::getSpecialLocation(juce::File::userDesktopDirectory) };
    auto mySamples = myFile.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, "click.wav");
    
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
    
    pMetronomeSample.reset( new juce::AudioFormatReaderSource(formatReader, true));
}

void Metronome::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
    juce::HighResolutionTimer::startTimer(60.0);
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        std::cout << "File Loaded" << std::endl;
    }
}

void Metronome::getNextAudioBlock( const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto bufferSize = bufferToFill.numSamples;
    
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mInterval;
    
//    std::cout << "mSamples remaining: " << mSamplesRemaining << std::endl;
//    std::cout << "Beat Interval: " << mInterval << std::endl;
    
    if ((mSamplesRemaining + bufferSize) >= mInterval)
    {
        std::cout << ("CLICK") << std::endl << "Total Samples: " << mTotalSamples << std::endl;
    }
    
//    pMetronomeSample->getNextAudioBlock(<#const AudioSourceChannelInfo &#>)
    
};

void Metronome::reset()
{
    mTotalSamples = 0;
};

void Metronome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
