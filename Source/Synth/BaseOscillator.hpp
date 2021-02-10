//
//  BaseOscillator.hpp
//  JuceAudio - App
//
//  Created by Sam Scott on 09/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#pragma once
#define _USE_MATH_DEFINES




#include <JuceHeader.h>
#include <cmath>


/** Class for the base class oscillator with velocity control and pitchbend and FM control. Call nextSample() repetedly to stream audio samples from the oscilator. */

class BaseOscillator
{
public:
    /** BaseOscillator constructor */
    BaseOscillator();
    
    /** BaseOscillator destructor */
    virtual ~BaseOscillator() = default;
    
    /** Sets the oscillator frequency.
     @param newFrequency  specifies the oscilator frequency
     @see setNote()*/
    void setFrequency (float newFrequency);
    
    /** Sets the oscillator frequency using a midi note number.
     @param noteNumber  MIDI note number (0 - 127)
     @see setFrequency()*/
    void setNote (int noteNumber);
    
    /** Sets the oscillator gain.
     @param newGain  the new gain value */
    void setGain (float newGain);
    
    /** Sets the sample rate.
     @param newSampleRate  new sample rate */
    void setSampleRate (float newSampleRate);
    
    /** Returns the next sample value.
     @return the next oscillator sample */
    float nextSample();
    
    /** Returns current frequency.
     @return currentfrequency */
    float getFrequency(float currentFrequency);
    
    /** Sets global variable for pitch bend as the incoming pitch bend variable Value.
     @param Value is pitch bend value */
    void setPitchBend(float Value);
    
    /** Sets FM sum*.
     @param fmValue is fm sum and is fm mod x index
     @see audio setEnvelopeParameters(std::atomic<float> *attack, std::atomic<float> *decay, std::atomic<float> *sustain, std::atomic<float> *release)*/
    void setFMmodulator(float fmValue);
    
    
    
  
    
    
protected:
    /** Generates the actual waveshape from a given phase value. This should not be called directly it is used internally by nextSample()
     @param phase argument in the range 0 - 2pi
     @return amplitude value for the given phase */
    virtual  float renderWaveShape (float currentphase);
    float frequency {0.f};
    float phase {0.f};
    std::atomic<float> gain {0.f};
    std::atomic<float> sampleRate {44100.f};
    std::atomic<float> phaseIncrement {0.f};
    
    float pitchBendValue = 0;
    
private:
    /** Updates the internal state for the current sample rate and frequency. */
    void updatePhaseIncrement();
    
    std::atomic<float> fmSum = {0.f};
    
};

