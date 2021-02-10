//
//  SecondSawToothOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SecondSawToothOscillator.hpp"

float SawToothOscillatorTwo::renderWaveShape(float currentphase)
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
