//
//  Buttons.h
//  JuceAudio - App
//
//  Created by Sam Scott on 05/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#pragma once

#include <JuceHeader.h>
#include "../../Source/ui/SynthUI.h"
#include "../../Source/audio/Audio.h"

/** UI class for the metrnome, where metronome button and sliders are created and respective component functionlity is provided to provide UI values to audio preferences through an Audio reference */

class MetronomeUI : public Component, public Button::Listener, public Slider::Listener
{
    
public:
    
    /** Constructor */
    MetronomeUI();
    
    /** Constructor with a string argument */
    MetronomeUI(std::string name);
    
    /** Destructor */
    ~MetronomeUI() = default;
    
    
    /** Sets bounds of this classes components */
    void resized() override;
   
    /** Where component button clicked functionality is provided.
     @param Button used for accsessing button clicked functionality */
    void buttonClicked (Button* Button) override;
    void buttonClicked();
    
    /** Where component slider moved functionality is provided.
     @param slider used for accsessing slider moved functionality */
    void sliderValueChanged (Slider* slider) override;
    
    /** Puts metrnome in a play state.
     @see MetPlayState  */
    void play();
    
    /** Puts metrnome in a play state.
     @see MetStopState  */
    void stop();
   
    /** Sets metronome toggle state.
     @param state is the bool value of the metronome button */
    void setState(bool state);
    
    /** Reference of audio to allow UI values to be provided to Audio
     @param a is the Audio reference */
    void getAudioReference(Audio& a);
    
   // TextButton getButton();
    
    std::string txt = "button text";
    
    TextButton thisButton;
    
    /** Gets metronome button state */
    void getmetButtonState();
    
    enum class MetPlayState /**enum class for play state */
    {
        Playing,
        Stopped
    };
    
private:
    
    int m_metbutval  { 0 };
    
    MetPlayState metplayState { MetPlayState::Stopped }; /** Play state dafaulted to not playing */
    Audio metronome;
    Audio* audioPtr;
    
    Slider Metronomesliders[2];
    TextButton metStartButton;
    TextButton metStopButton;
    Label metBpmLabel;
    Label metGainLabel;
    
};
