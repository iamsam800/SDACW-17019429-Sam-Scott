//
//  Metronome.h
//  JuceAudio - App
//
//  Created by Sam Scott on 03/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#pragma once

#include <JuceHeader.h>

/** A class containing the file finding and sample maths functionality for the Metronome, HighResoloutionTimer is used to provide an accurate 60 second for maths working out metrnome interval */
class Metronome : public HighResolutionTimer,
                  public AudioTransportSource
{
public:
    /** Constructor */
    Metronome();
    
    /** Works out the interval for metronome.
     @param samplesPerBlock provides samplesPerBlock for the AudioTransportSource
     @param sampleRate provides samplerate for AudioTransport source
     @see Audio prepareToPlay (int samplesPerBlock, double sampleRate) as values are passed from there */
    void prepareToPlay (int samplesPerBlock, double sampleRate) override;
    
    /** Fills the metronome buffer*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    /** Resets the metronome */
    void reset();
    
    /** Sets metronome BPM
     @param newBPM the BPM value received from metronome UI
     @see setMetronomeBPM(int newBPM) as BPM value is received from here */
    void setBPM(int newBPM);
    
    /** Sets metronome gain
     @param newGain the gain value received from metronome UI
     @see setMetronomeGain(int newGain) as gain value is received from here */
    void setMetGain(float newGain);
    
    
    /** Call backk for hiResTimer */
    void hiResTimerCallback() override;
    
private:
    
    int metTotalSamples { 0 };
    double metSampleRate { 48000 };
    int metInterval { 0 };
    int metBPM { 40 };
    int metNumSamplesRemaining;
    
    
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample { nullptr }; /* Allows previous samples to be removed from memory (after that sample has been used) */
    AudioFormatManager metaudioFormatManager;
    
    int sliderValue { 0 };
    
};
