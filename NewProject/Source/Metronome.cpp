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
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    juce::HighResolutionTimer::startTimer(60.0);
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        std::cout << "File Loaded" << std::endl;
    }
}

void Metronome::getNextAudioBlock( const juce::AudioSourceChannelInfo& bufferToFill)
{
    const auto bufferSize = bufferToFill.numSamples;
    
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mUpdateInterval;
    
    if ((mSamplesRemaining + bufferSize) >= mUpdateInterval)
    {
        const auto timeToStartPlaying = mUpdateInterval - mSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);
        
        for (auto sample = 0; sample < bufferSize; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                std::cout << ("CLICK -- ") << sample + mSamplesRemaining << std::endl;
                std::cout << "Total Samples: " << mTotalSamples << std::endl;
                pMetronomeSample->getNextAudioBlock(bufferToFill);
            }
        }
    }
    
    if (pMetronomeSample->getNextReadPosition() != 0)
    {
        pMetronomeSample->getNextAudioBlock(bufferToFill);
    }
    
};

void Metronome::reset()
{
    mTotalSamples = 0;
};

void Metronome::hiResTimerCallback()
{
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
}
