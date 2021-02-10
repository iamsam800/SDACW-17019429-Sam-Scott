//
//  SecondBaseOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SecondBaseOscillator.hpp"







#include <cmath>

BaseOscillatorTwo::BaseOscillatorTwo()
{
    
    updatePhaseIncrement();
}

void BaseOscillatorTwo::setFrequency (float newFrequency)
{
    frequency = newFrequency * pitchBendValue;
    
    updatePhaseIncrement();
}

void BaseOscillatorTwo::setNote (int noteNumber)
{
    setFrequency (440.f * pow (2, (noteNumber - 69) / 12.0));
}
void BaseOscillatorTwo::setGain (float newGain)
{
    gain = newGain / 127;
}

void BaseOscillatorTwo::setSampleRate (float newSampleRate)
{
    sampleRate = newSampleRate;
    updatePhaseIncrement();
}

float BaseOscillatorTwo::nextSample()
{
    auto out = renderWaveShape (phase) * gain ;
    
    phase += phaseIncrement;
    
    // phase = phase + ((MathConstants<float>::twoPi * frequency) / sampleRate);
    if(phase  > MathConstants<float>::twoPi)
        phase -= MathConstants<float>::twoPi;
    
    return out;
}

float BaseOscillatorTwo::renderWaveShape (float currentPhase)
{
    return std::sin (currentPhase);
}

void BaseOscillatorTwo::updatePhaseIncrement()
{
    getFrequency(frequency);
  
    phaseIncrement = (MathConstants<float>::twoPi * frequency) / sampleRate;
}

float BaseOscillatorTwo::getFrequency(float currentFrequency)
{
    double root = std::exp(std::log(2) / 12); /** cent root */
    double cent = pow(root, 5);   /** Increase to number of cent */
    
    currentFrequency = frequency * cent;
    
  
    return currentFrequency;
    
}


void BaseOscillatorTwo::setPitchBend(float Value)
{
    pitchBendValue = Value;
    
}
