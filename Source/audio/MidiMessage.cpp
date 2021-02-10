//
//  MidiMessage.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 05/02/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "MidiMessage.h"

MyMidiMessage::MyMidiMessage()
{
    
}

MyMidiMessage::~MyMidiMessage(){
    
     
}

void MyMidiMessage::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
 
    DBG ("Midi event..." << message.getNoteNumber() << "\n");
    DBG ("Freq: " << message.getMidiNoteInHertz(message.getNoteNumber()));
    if(message.isController())
    {
        
        m_modWheelValue = message.getControllerValue();
        DBG("Controller value: " << message.getControllerValue());
       
    }
    
    if (message.isPitchWheel())
    {
        m_isPitchWheel = true;
        setPitchBendValue(message.getPitchWheelValue());
    }
    if (!message.isPitchWheel()){ m_isPitchWheel = false; }
    
    if (message.isNoteOn())
    {
        m_pitchBendValue = 1.0f;
        m_isNoteOn = true;
        
        m_frequency = message.getMidiNoteInHertz(message.getNoteNumber());
        m_notenum = message.getNoteNumber();
        m_velocity = message.getVelocity();
    }
    if (message.isNoteOff())
    {
        m_isNoteOn = false;
    }
    
    
}

float MyMidiMessage::getMidiFrequency()
{
    return m_frequency;
}

int MyMidiMessage::getMidiNoteNumber()
{
    return m_notenum;
}

float MyMidiMessage::getMidiGain()
{
    return m_velocity;
}

void MyMidiMessage::setPitchBendValue(float pitchWheel)
{
    /** Getting pitch bend mutliplier */
    float bend = (pitchWheel / 8192) - 1.0 ;
    
    m_pitchBendValue = powf(2.0, bend);
}

float MyMidiMessage::pitchBendGet()
{
    return m_pitchBendValue;
}


