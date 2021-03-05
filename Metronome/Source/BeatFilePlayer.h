/*
  ==============================================================================

    BeatFilePlayer.h
    Created: 4 Mar 2021 4:17:33pm
    Author:  xhkj

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BeatFilePlayer
{
public:
    BeatFilePlayer();
    ~BeatFilePlayer();
    
    void reset();
    void prepareToPlay(int samplesPerBlock, double sampleRate);
    
    void startGetNextBlock(const juce::AudioSourceChannelInfo& bufferToFill, int startPosition);
    void getNextBlockIfPlaying(const juce::AudioSourceChannelInfo& bufferToFill);
private:
    juce::AudioFormatManager mFormatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> pMetronomeSample { nullptr };
};
