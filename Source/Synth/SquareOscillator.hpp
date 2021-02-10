//
//  SquareOscillator.hpp
//  JuceAudio - App
//
//  Created by Sam Scott on 30/12/2020.
//  Copyright © 2020 UWE. All rights reserved.
//



#pragma once
#include "BaseOscillator.hpp"
#include <stdio.h>

/** Class for a squarewave oscillator. Call nextSample() repetedly to stream audio samples from the oscilator. */
class SquareOscillator : public BaseOscillator
{
    
public:
    
    /** SquareOscillator constructor */
    SquareOscillator() = default;
    /** SquareOscillator destructor */
    ~SquareOscillator() = default;
    
    
    
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */

    float renderWaveShape (float currentphase) override;
    
private:
    
   
};
