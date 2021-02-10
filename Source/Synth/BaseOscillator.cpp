//
//  BaseOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 09/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include <cmath>
#include "BaseOscillator.hpp"
#include "../../Source/Synth/sOscillator.hpp"

BaseOscillator::BaseOscillator()
{
    
    updatePhaseIncrement();
}

void BaseOscillator::setFrequency (float newFrequency)
{
    frequency = newFrequency * pitchBendValue;
    
    updatePhaseIncrement();
}

void BaseOscillator::setNote (int noteNumber)
{
    setFrequency (440.f * pow (2, (noteNumber - 69) / 12.0));
}
void BaseOscillator::setGain (float newGain)
{
    gain = newGain / 127;
    
    
}

void BaseOscillator::setSampleRate (float newSampleRate)
{
    sampleRate = newSampleRate;
    updatePhaseIncrement();
}

float BaseOscillator::nextSample()
{
    auto out = renderWaveShape (phase) * gain ;
    
    phase += phaseIncrement;
    
    if(phase  > MathConstants<float>::twoPi)
        phase -= MathConstants<float>::twoPi;
    
    return out;
}

float BaseOscillator::renderWaveShape (float currentPhase)
{
    return std::sin (currentPhase);
}

void BaseOscillator::updatePhaseIncrement()
{
    
    phaseIncrement = (MathConstants<float>::twoPi * frequency) / sampleRate;
}

float BaseOscillator::getFrequency(float currentFrequency)
{
    
   currentFrequency = frequency;
    
    return currentFrequency;
}

void BaseOscillator::setPitchBend(float Value)
{
    pitchBendValue = Value;
    
}

void BaseOscillator::setFMmodulator(float fmValue)
{
    fmSum = fmValue;
}
