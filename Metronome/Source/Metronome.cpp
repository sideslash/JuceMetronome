/*
  ==============================================================================

    Metronome.cpp
    Created: 4 Mar 2021 2:03:36pm
    Author:  xhkj

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{

}

Metronome::~Metronome()
{
    
}

void Metronome::prepareToPlay(double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
}

int Metronome::countSamples (int bufferSize)
{
    mTotalSamples += bufferSize;
//    DBG(totalSamples);
    
    mSampleRemaining = mTotalSamples % mInterval;
    
//    const int startSampleInBlock = bufferSize - mSampleRemaining;
    return bufferSize - mSampleRemaining;
}

void Metronome::reset()
{
    mTotalSamples = 0;
}


