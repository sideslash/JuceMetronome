#pragma once

#include <JuceHeader.h>
#include "Metronome.h"
#include "BeatFilePlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, public juce::KeyListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    bool keyPressed (const juce::KeyPress& key,
                     juce::Component* originatingComponent) override;
private:
    //==============================================================================
    enum class PlayState
    {
       Playing,
       Stopped
    };
       
    PlayState mPlayState { PlayState::Stopped };

    juce::TextButton playButton { "Play" };

    void playClick();
    void updatePlayButtonStyle();
    
    Metronome mMetronome;
    BeatFilePlayer mBeatFilePlayer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
