#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    playButton.setRadioGroupId(1);
    playButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    playButton.onClick = [this]() { play(); };
    addAndMakeVisible(playButton);
    
    stopButton.setRadioGroupId(1);
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    stopButton.onClick = [this]() { stop(); };
    addAndMakeVisible(stopButton);

    
    setSize (200, 200);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::play()
{
    playstate = PlayState::Playing;
};

void MainComponent::stop()
{
    playstate = PlayState::Stopped;
};


//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();
    
    if (playstate == PlayState::Playing)
    {
        DBG("Playing");
    }
    else
    {
        DBG("Stopped");
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    juce::FlexBox flexBox;
    flexBox.items.add(juce::FlexItem(100, 100, playButton));
    flexBox.items.add(juce::FlexItem(100, 100, stopButton));
    flexBox.performLayout(bounds);
}
