//
//  SynthUI.h
//  JuceAudio
//
//  Created by Sam Scott on 01/02/2021.
//  Copyright © 2021 UWE. All rights reserved.
//
#pragma once
#include <JuceHeader.h>



/** Customises a component */

//==============================================================================
class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel();
 
    /** Creates rotary slider */
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
     /** Draws button background */
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool, bool isButtonDown) override;
    /** Draws button text */
    void drawButtonText (juce::Graphics& g, juce::TextButton& button, bool, bool isButtonDown) override;
    
private:
    
};
    

