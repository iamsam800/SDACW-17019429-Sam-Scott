#pragma once
#include <atomic>
#include <JuceHeader.h>
#include "../../Source/Synth/sOscillator.hpp"
#include "../../Source/Synth/SquareOscillator.hpp"
#include "../../Source/Synth/SawOscillator.hpp"
#include "../../Source/Synth/TriangleOscillator.hpp"
#include "../../Source/audio/Metronome.h"
#include "../../Source/Synth/SecondBaseOscillator.hpp"
#include "../../Source/Synth/SecondSinOscillator.hpp"
#include "../../Source/Synth/SecondSquareOscillator.hpp"
#include "../../Source/Synth/SecondTriangleOscillator.hpp"
#include "../../Source/Synth/SecondSawToothOscillator.hpp"
#include "../../Source/audio/MidiMessage.h"

/** Class containing all audio processes */

class Audio :   public MidiInputCallback,
                public AudioIODeviceCallback
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager;}
    
    /** Handles incoming MidiMessage, only kept in as, unable to receive MIDI input on myMidiclass without audio handleMidi call.
     @param MidiMessage& used to accsess midi message functionality */
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    
    /** Handles incoming input and output and is used to ouput sound.
     @param inputChannelData points to the array values of buffers input data
     @param numInputChannels is the number of input channel available to the buffer
     @param outputChannelData points to the array values of the buffers output channel data
     @param numSamples is the number of samples available to the buffer */
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
   
    /** Handles what should happen when the device is started */
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    /** Handles what should happen when device is stopped */
    void audioDeviceStopped() override;
    
    ///////////////////Synth/////////////////////////////////////////////
    
    /** Used to set oscillators wave type.
     @param &BaseOscillator& type sets oscillator wave type based on button click
     @see MainComponent buttonClicked(Button *Button) as this is where wave type is set
     @param &BaseOscillator& type sets oscillator wave type for second oscillator based on button click
     @see MainComponent buttonClicked(Button *Button) as this is where wave type is set*/
    void setOscillatorType(BaseOscillator& type, BaseOscillatorTwo& type2);
   
    /** Sets envelope paramaters based off received slider values received through an audio reference in the synth UI class
     
     @param *attack gets value of attack slider paramter value in synth UI class value 0.1 - 5.0 in seconds
     @param *decay gets value of decay slider paramter value in synth UI class value 0.1 - 2.0 n seconds
     @param *sustain gets value of sustain slider paramter value in synth UI class 0.1 - 1.0 n seconds
     @param *release gets value of release slider paramter value in synth UI class 0.1 - 5.0 n seconds
     
     @see SynthUI sliderValueChanged (Slider* slider) is where param pointer values are applied */
    void setEnvelopeParameters(std::atomic<float> *attack, std::atomic<float> *decay, std::atomic<float> *sustain, std::atomic<float> *release);
    
    /** Sets frequency modulation paramters and calculates the FM sum
     
     @param *modFrequency gets FM mod frequency value from slider value in SynthUI values 0.1-100
     @param *modIndex gets FM index value from slider value in SynthUI values 0-16
     
     @see  SynthUI sliderValueChanged(Slider *slider) as slider values received from here  */
    void setFmParameters(std::atomic<float> *modFrequency, std::atomic<int> *modIndex);
    
    /** Sets Filter Parameters based off respective received slider values in SynthUI
     @param *lpfcutOff value 50.1 - 15000 in Hz
     @param *lpfQ value 0.1 - 1
     
     @see SynthUI sliderValueChanged(Slider *slider) as value received from there    */
    void setFilterParameters(std::atomic<float> *lpfcutOff, std::atomic<float> *lpfQ);
   ///////////////Metronome///////////////////////////////////
    
    /** Sets metronome gain based off received gain slider value in MetronomeUI
     @param newGain values 0.0-1.0
     
     @see MetronomeUI sliderValueChanged(Slider *slider) where gain slider value is received from */
    void setMetronomeGain(std::atomic<float> newGain);
    
    /** Prepares the metronome, providing samples per block expected and sample rate, which passes them into Metronome.
     @Param samplesPerBlockExpected
     @Param sampleRate
     @see */
    void prepareToPlay (std::atomic<int> samplesPerBlockExpected, std::atomic<double> sampleRate);
    
    /** Fills Metronome Buffer.
     @see Metronome getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    
    /** Sets the global variable for metronome button state, to be used to start and stop the metronome buffer in the audio output.
     @param currentState metronome button state value received from MetronomeUI
     @see MetronomeUI buttonClicked (Button* Button) as metronome button state is received from here*/
    
    void setMetButtonState (int currentState);
    
    /** May get rid of */
    int getMetStateValue();
    
    /** Sets metronome BPM from slider value received from MetronomeUI class
     @param newBPM is the BPM slider value received from MetronomeUI class
     @see MetronomeUI sliderValueChanged(Slider *slider) where gain slider value is received from */
    void setMetronomeBPM(std::atomic<int> newBPM);
    
    
    float getMetGain();
   
    /////////////Midi///////////////////////////////////////////////
    /** Updates MidiMessage with values received from the MidiMessage class
     @see myMidiMessage handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) where MIDI message values are received from */
    void updateMidiMessage();
  
  
  
private:
    MyMidiMessage m_Midi;
    float sampleRate {0.f};
    int bufferSize { 0 };
    
    //////////////////Synth objects and global variables/////////////////
    AudioDeviceManager audioDeviceManager;
    BaseOscillator* oscillator;
    BaseOscillatorTwo* oscillator2;
    SinOscillator sin;
    SinOscillatorTwo sin2;
    float currentFrequency {0.f};
    
    ADSR adsr;
    ADSR::Parameters adsrParams; /** Allows accsess to envelope paramaters within ADSR class */
    float fmodFrequency {0.f};
    int fmodIndex { 0 };
    float fmSum {0.f};

    IIRFilter Nyquist;
    IIRFilter Nyquist2;
    
    IIRFilter lpf;
    IIRFilter lpf2;
    
    IIRFilter lpfImproving;
    IIRFilter lpf2Improving;
    
    ///////////////////Metronome Objects and global variables //////////////////
    Metronome met;
    AudioSourcePlayer metaudiosourceplayer;
    MixerAudioSource combinedOutput;
    int metglobVal = 0;
};

