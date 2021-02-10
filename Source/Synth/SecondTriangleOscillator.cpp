//
//  SecondTriangleOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SecondTriangleOscillator.hpp"

float TriangleOscillatorTwo::renderWaveShape(float currentphase)
{
    currentphase = phase;
    
    if(currentphase < double_Pi)
    {
        currentphase = ((-1 + 2 / double_Pi) * currentphase);
    }
    else
    {
        currentphase = ((3 - 2 / double_Pi) * currentphase);
    }
    
    currentphase = currentphase + ((MathConstants<float>::twoPi * frequency) / sampleRate);
    
    if(currentphase > MathConstants<float>::twoPi)
    {
        currentphase = currentphase - MathConstants<float>::twoPi;
    }
    
    return std::sin(currentphase);
}
