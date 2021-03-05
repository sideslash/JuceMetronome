#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output  channels that we want to open
        setAudioChannels (2, 2);
    }
    
    
//    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    addAndMakeVisible(playButton);
    playButton.onClick = [this]{ playClick(); };
    updatePlayButtonStyle();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    mMetronome.prepareToPlay(sampleRate);
    
//    mBeatFilePlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    
    auto bufferSize = bufferToFill.numSamples;
    
    if (mPlayState == PlayState::Playing)
    {
        int startSampleInBlock = mMetronome.countSamples(bufferSize);
        if (startSampleInBlock >= 0)
        {
            DBG("CLICK" << startSampleInBlock);
            mBeatFilePlayer.startGetNextBlock(bufferToFill, startSampleInBlock);
        }
        else {
            mBeatFilePlayer.getNextBlockIfPlaying(bufferToFill);
        }
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

}

void MainComponent::resized()
{
    playButton.setBounds(getLocalBounds().reduced(50));
}

//==============================================================================
void MainComponent::playClick()
{
    if (mPlayState == PlayState::Playing)
    {
        mPlayState = PlayState::Stopped;
        mMetronome.reset();
        mBeatFilePlayer.reset();
    }
    else
    {
        mPlayState = PlayState::Playing;
    }
    
    updatePlayButtonStyle();
}

void MainComponent::updatePlayButtonStyle()
{
    if (mPlayState == PlayState::Playing)
    {
        playButton.setButtonText("Stop");
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    }
    else
    {
        playButton.setButtonText("Play");
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }
}



//==============================================================================
bool MainComponent::keyPressed (const juce::KeyPress& key,
                         juce::Component* originatingComponent)
{
//    DBG(key.getKeyCode());
    if (key.isKeyCode(32)) {
        playClick();
        return true;
    }
    return false;
}
