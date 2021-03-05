/*
  ==============================================================================

    BeatFilePlayer.cpp
    Created: 4 Mar 2021 4:17:33pm
    Author:  xhkj

  ==============================================================================
*/

#include "BeatFilePlayer.h"

BeatFilePlayer::BeatFilePlayer()
{
    mFormatManager.registerBasicFormats();
    
    juce::File myFile { juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory) };
    DBG(myFile.getFullPathName());
    
    auto mySamples = myFile.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false, "Blocked.wav");
    
    jassert(mySamples[0].exists());
    
    auto reader = mFormatManager.createReaderFor(mySamples[0]);

    pMetronomeSample.reset(new juce::AudioFormatReaderSource(reader, true));
}

BeatFilePlayer::~BeatFilePlayer()
{
    pMetronomeSample.reset();
}

//----------------------------------------------------------
void BeatFilePlayer::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    if (pMetronomeSample == nullptr) return;
        
    pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
    DBG("file loaded");
}


void BeatFilePlayer::reset()
{
    if (pMetronomeSample == nullptr) return;
    
    pMetronomeSample->setNextReadPosition(0);
}

void BeatFilePlayer::startGetNextBlock(const juce::AudioSourceChannelInfo& bufferToFill, int startPosition)
{
    reset();
    
    pMetronomeSample->getNextAudioBlock(bufferToFill);
//    bufferToFill.startSample = 1;
//    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
//    {
//        auto samplePointer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
//        samplePointer += startPosition;
//
//    }
//
}

void BeatFilePlayer::getNextBlockIfPlaying(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (pMetronomeSample == nullptr) return;
    if (pMetronomeSample->getNextReadPosition() == 0) return;
    
    pMetronomeSample->getNextAudioBlock(bufferToFill);
}
