/*
 *  SinOscillator.cpp
 *  Software Development for Audio
 */

#pragma once
#define _USE_MATH_DEFINES

#include "../../Source/Synth/SecondBaseOscillator.hpp"
#include <JuceHeader.h>
#include <cmath>


/** Class for a detuned sinewave oscillator. Call nextSample() repetedly to stream audio samples from the oscilator. */

class SinOscillatorTwo : public BaseOscillatorTwo
{
public:
    /** SinOscillator constructor */
    SinOscillatorTwo() = default;
    
    /** SinOscillator destructor */
    ~SinOscillatorTwo() = default;
    
    
    
    
    
    
    
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */
    float renderWaveShape (float currentphase) override;
    
    
    
    
private:
    /** Updates the internal state for the current sample rate and frequency. */
    
    
    
    
};
