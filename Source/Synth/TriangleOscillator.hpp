//
//  TriangleOscillator.hpp
//  JuceAudio - App
//
//  Created by Sam Scott on 09/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#pragma once
#include "BaseOscillator.hpp"
#include <stdio.h>

 /** Class for a triangle oscillator. Call nextSample() repetedly to stream audio samples from the oscilator. */
class TriangleOscillator : public BaseOscillator
{
public:
    
    TriangleOscillator() = default;
    ~TriangleOscillator() = default;
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */

    float renderWaveShape (float currentphase) override;
    
private:
};
