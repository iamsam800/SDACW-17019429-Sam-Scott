//
//  SawOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 09/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SawOscillator.hpp"

float SawToothOscillator::renderWaveShape(float currentphase)
{
    currentphase = phase;
    
    currentphase = 1 - ((1 / double_Pi) * currentphase);
    
    currentphase = currentphase + ((MathConstants<float>::twoPi * frequency)  / sampleRate);
    
    if(currentphase > MathConstants<float>::twoPi)
    {
        currentphase = currentphase - MathConstants<float>::twoPi;
        
    }
    
    return std::sin(currentphase);
}
