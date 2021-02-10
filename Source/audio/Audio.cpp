#include "Audio.h"

Audio::Audio()
{
    
  /**Receiving addresses of sine class 1 and 2 to initialise default value, can remove this by making thread safe with atomics to stop potential data leak and bad access */
  oscillator = &sin;
  oscillator2 = &sin2;

   combinedOutput.addInputSource(&met, false); /** Receving address of met object to put met audio source into a mix source to add audio to the synth buffer */
   metaudiosourceplayer.setSource(&combinedOutput);
   
    /** Getting available midi and audio input devices and setting respective input */
    auto midiInputDevices = MidiInput::getAvailableDevices();
    if (midiInputDevices.size() > 0)
        audioDeviceManager.setMidiInputDeviceEnabled (midiInputDevices[0].identifier, true);
    audioDeviceManager.addMidiInputCallback ("", this);

    auto errorMessage = audioDeviceManager.initialiseWithDefaultDevices (1, 2);
    if ( ! errorMessage.isEmpty())
        DBG (errorMessage);
    audioDeviceManager.addAudioCallback (this);
    
}

Audio::~Audio()
{
    /**Removing callbacks */
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback ("", this);
    combinedOutput.removeAllInputs();
    
    Nyquist.reset();
    Nyquist2.reset();
    lpf.reset();
    lpf2.reset();
   
}


void Audio::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    m_Midi.handleIncomingMidiMessage(source, message);
}
void Audio::updateMidiMessage()
{
    
    
    /**Setting each oscillator voice's: gain, frequency and pitch bend values while making pitch bend value 1.0 (ferquency * 0, which is initial value*/
    if (m_Midi.m_isNoteOn)
    {
        adsr.noteOn();
        oscillator->setNote(m_Midi.getMidiNoteNumber());
        oscillator->setGain(m_Midi.getMidiGain());
        currentFrequency = m_Midi.getMidiFrequency();
    }
    if (!m_Midi.m_isNoteOn){ adsr.noteOff();}
    
    oscillator->setFrequency(fmSum + currentFrequency);
    oscillator->setPitchBend(m_Midi.pitchBendGet());
    
    if(fmSum == 0)
    {
        oscillator2->setFrequency(currentFrequency);
        oscillator2->setPitchBend(m_Midi.pitchBendGet());
        
    }
}

  void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                   int numInputChannels,
                                   float** outputChannelData,
                                   int numOutputChannels,
                                    int numSamples)
{
   
    /**Putting metronome audio into the buffer than synth is playing from */
    updateMidiMessage();
    
     metaudiosourceplayer.audioDeviceIOCallback(inputChannelData, numInputChannels, outputChannelData, numOutputChannels, numSamples);
    
    
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
   
    
    /** setting oscillator voices pitch bend values */
    adsr.setParameters(adsrParams);
  
    while(numSamples--)
    {
        //met.setGain(setGain);
        float fileOutL = *outL;
        float fileOutR = *outR;
       
        auto outputL = std::sin(oscillator->nextSample() + oscillator2->nextSample() ) * adsr.getNextSample();
        auto outputR = outputL;
      
        auto NyquistFilterL = Nyquist.processSingleSampleRaw(outputL);
        auto NyquistFilterR = Nyquist2.processSingleSampleRaw(outputR);
        
        auto lpfL = lpf.processSingleSampleRaw(NyquistFilterL);
        auto lpfR =  lpf2.processSingleSampleRaw(NyquistFilterR);
        
        auto secondOrderlpfL = lpfImproving.processSingleSampleRaw(lpfL);
        auto secondOrderlpfR = lpf2Improving.processSingleSampleRaw(lpfR);
      
       
        switch (metglobVal) {
            case 0:
              
                *outL = secondOrderlpfL;
                *outR = secondOrderlpfR;
              
                break;
            case 1:
              
                *outL =  secondOrderlpfL + (fileOutL * met.getGain());
                *outR =  secondOrderlpfR  + (fileOutR * met.getGain());
               
                break;
            }
        
        outL++;
        outR++;
        }
}

void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    
    /**getting universal sample and buffer rate to allow unison of values accross synth and metronome */
    metaudiosourceplayer.audioDeviceAboutToStart(device);
    sampleRate = device -> getCurrentSampleRate(); /** Setting audio preferences sample rate value to global variable  'sampleRate' */
    bufferSize =  device -> getCurrentBufferSizeSamples();
    
    Nyquist.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, sampleRate / 2));
    Nyquist2.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, sampleRate / 2));
}

void Audio::audioDeviceStopped()
{
    /** Stopping audio source */
    metaudiosourceplayer.audioDeviceStopped();
   
 }

void Audio::setOscillatorType(BaseOscillator &type, BaseOscillatorTwo& type2)
{
    /**Receiving oscillator wavetype from  wave button selection*/
    oscillator = &type;
    oscillator2 = &type2;
    
}

void Audio::prepareToPlay(std::atomic<int> samplesPerBlockExpected, std::atomic<double> sampleRate)
{
    /**Preparing to play audio */
    met.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void Audio::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    /**Filling vuffer with metronome audio */
    bufferToFill.clearActiveBufferRegion();
    DBG("Metronome State: " << metglobVal << "\n");
    if(metglobVal == 1 )
    {
        met.getNextAudioBlock(bufferToFill);
        DBG("Playing");
    }
    
    else{
     
     met.reset();
     
     }
    
}

void Audio::setMetButtonState(int currentState)
{
    /**setting global metronome value from value received in maincomponent */
    metglobVal = currentState;
   
}

int Audio::getMetStateValue()
{
    /**Getting metstate from making local variable value same as global then returning it */
    int metstate = metglobVal;
    
    return metstate;
}

void Audio::setMetronomeBPM(std::atomic<int> newBPM)
{
    /**Setting metronome bpm from slider value received from maincomponent */
    met.setBPM(newBPM);
}

void Audio::setMetronomeGain(std::atomic<float> newGain)
{
    /** Setting metronome gain received from maincomponent */
    met.setGain(newGain);
}

void Audio::setEnvelopeParameters(std::atomic<float> *attack, std::atomic<float> *decay, std::atomic<float> *sustain, std::atomic<float> *release)
{
    adsrParams.attack = *attack;
    adsrParams.decay = *decay;
    adsrParams.sustain = *sustain;
    adsrParams.release = *release;
    
}

void Audio::setFmParameters(std::atomic<float> *modFrequency, std::atomic<int> *modIndex)
{
    /**Dereferencing pointer values as global values to be used out of scope from this funciton */
    fmodFrequency = *modFrequency;
    fmodIndex = *modIndex;
    
    fmSum = fmodIndex * fmodFrequency; /** Sum for modulator signal */
}

void Audio::setFilterParameters(std::atomic<float> *cutOff, std::atomic<float> *Q)
{
    lpf.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, *cutOff, *Q));
    lpf2.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, *cutOff, *Q));
    
    
    lpfImproving.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, *cutOff, *Q));
    lpf2Improving.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, *cutOff, *Q));
}
