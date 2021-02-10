/*
 *  SinOscillator.cpp
 *  Software Development for Audio
 */

#pragma once
#define _USE_MATH_DEFINES

#include "BaseOscillator.hpp"
#include <JuceHeader.h>
#include <cmath>


/** Class for a sinewave oscillator. Call nextSample() repetedly to stream audio samples from the oscilator. */

class SinOscillator : public BaseOscillator
{
public:
    /** SinOscillator constructor */
    SinOscillator() = default;
    
    /** SinOscillator destructor */
     ~SinOscillator() = default;
    
    
    
    
   
    
    
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */

    float renderWaveShape (float currentphase) override;
    
    
    
    
private:
    
 
    
   
   
};
