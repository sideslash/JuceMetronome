/*
  ==============================================================================

    Metronome.h
    Created: 4 Mar 2021 2:03:36pm
    Author:  xhkj

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome
{
public:
    Metronome();
    ~Metronome();
    
    void prepareToPlay(double sampleRate);
    //return the start index of the filling position for the current block buffer
    int countSamples (int bufferSize);
    void reset();
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    int mInterval { 0 }; //sample count between two beats
    int mBpm { 60 };
    int mSampleRemaining { 0 };
};
