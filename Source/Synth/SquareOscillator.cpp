//
//  SquareOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 30/12/2020.
//  Copyright © 2020 UWE. All rights reserved.
//

#include "SquareOscillator.hpp"



float SquareOscillator::renderWaveShape(float currentphase)
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


