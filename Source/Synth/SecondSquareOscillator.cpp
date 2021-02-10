//
//  SecondSquareOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SecondSquareOscillator.hpp"





float SquareOscillatorTwo::renderWaveShape(float currentphase)
{
    
    currentphase = phase;
    
    if (currentphase < double_Pi){
        
        currentphase = 1;
    }
    
    else {
        
        currentphase = -1;
    }
    
    currentphase = currentphase + ((MathConstants<float>::twoPi * frequency) / sampleRate);
    
    if (currentphase > MathConstants<float>::twoPi){
        
        currentphase = phase - MathConstants<float>::twoPi;
        
    }
    
    
    return std::sin(currentphase);
    
}


