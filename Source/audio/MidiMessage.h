//
//  MidiMessage.h
//  JuceAudio
//
//  Created by Sam Scott on 05/02/2021.
//  Copyright © 2021 UWE. All rights reserved.
//


#pragma once
#include <JuceHeader.h>
#include "../Synth/BaseOscillator.hpp"

/** A class used to receive MidiMessages */
class MyMidiMessage : public MidiInputCallback
{

public:
    
    /** Constructor */
    MyMidiMessage();
    
    /**Destructor */
     ~MyMidiMessage(); 
    
    /** Handles incoming midiMessage
     @param message used for midiMessage functionality of incoming message
     @see Audio handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) as call received from there due to IO callbacks being handles within Audio */
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    
    /** Sets pitch bend value of incoming midi pitchwheel value received from handleIncoming MIDImessage and does maths to create bend mulitplier
     @param pitchWheel Midi pitchweel value
     @see handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) param value received from here */
    void setPitchBendValue(float pitchWheel);
    
    /** Returns midi values freqeuncy to be used outside this class
     @return m_frequency global value set in handleIncomingMidiMessage  */
    float getMidiFrequency();
    
    /** Returns midi values note number to be used outside this class
     @return m_notenum global value set in handleIncomingMidiMessage  */
    int getMidiNoteNumber();
    
    /** Returns midi values velocity to be used outside this class
     @return m_velocity global value set in handleIncomingMidiMessage  */
    float getMidiGain();
    
    /** Returns midi values pitchbend  to be used outside this class
     @return m_pitchbend global value set in handleIncomingMidiMessage  */
    float pitchBendGet();
    
   
private:
    std::atomic<float> m_frequency { 0.f };
    std::atomic<int> m_notenum  { 0 };
    std::atomic<float> m_velocity { 0.f };
    
    //float m_pitchWheel = 0;
    std::atomic<float> m_pitchBendValue { 0.f };

    float m_modWheelValue { 0.f };
public:
    bool m_isNoteOn = false;
    bool m_isPitchWheel = false;
    
};
