//
//  SquareOscillator.hpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/12/2020.
//  Copyright © 2020 UWE. All rights reserved.
//



#pragma once
#include "../../Source/Synth/SecondBaseOscillator.hpp"
#include <stdio.h>

/** Class for a detuned squarewave oscillator. Call nextSample() repetedly to stream audio samples from the oscilator. */
class SquareOscillatorTwo : public BaseOscillatorTwo
{
    
public:
    /** SquareOscillator Two constructor */
    SquareOscillatorTwo() = default;
    
    /** SquareOscillator Two constructor */
    ~SquareOscillatorTwo() = default;
    
    
    
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */

    float renderWaveShape (float currentphase) override;
    
private:
    
    
};
