//
//  Sliders.h
//  JuceAudio
//
//  Created by Sam Scott on 05/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#pragma once

#include <JuceHeader.h>
#include "SynthUI.h"
#include "../../Source/Synth/BaseOscillator.hpp"
#include "../../Source/Synth/SecondBaseOscillator.hpp"
#include "../../Source/audio/Audio.h"

/** Class for creating Synth UI components and providing component functionality */
class SynthUI : public Component,  public Slider::Listener
{
public:
    /** Constructor */
    SynthUI();
    
    /** Destructor */
    ~SynthUI() = default;
    
    
    void sliderMoved();
   
    /** Provides synth parameter values through a pointer reference to Audio
     @param silder used to accsess slider moved fucntionality
     @see audioPTR pointer used to provide UI values to Audio */
    void sliderValueChanged (Slider* slider) override;
    
    /** Sets this classes component bonds */
    void resized() override;
  
    /** Gets a referecne from Audio
     @param &a is the reference supplied as a function argument */
    void getReference(Audio &a);
   
private:
   
    Audio* audioPTR;

    Slider envSliders[4];
    Label envLabel[4];
    Slider fmSliders[2];
    Slider filterSliders[2];
    Label raidialLabel[4];
};
