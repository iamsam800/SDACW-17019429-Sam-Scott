//
//  Buttons.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 05/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "MetronomeUI.h"


MetronomeUI::MetronomeUI()
{
    addAndMakeVisible(metStartButton);
    metStartButton.setButtonText("Start Metronome");
    metStartButton.addListener(this);
    addAndMakeVisible(metStopButton);
    metStopButton.setButtonText("Stop Metronome");
    metStopButton.addListener(this);
    
    
    addAndMakeVisible(Metronomesliders[0]);
    addAndMakeVisible(Metronomesliders[1]);
    
    Metronomesliders[1].setSliderStyle(Slider::Rotary);
    
    addAndMakeVisible(metBpmLabel);
    metBpmLabel.setText("BPM Control", dontSendNotification);
    
    addAndMakeVisible(metGainLabel);
    metGainLabel.setText("Metronome Gain", dontSendNotification);
    Metronomesliders[0].setRange(40, 200, 1);
    Metronomesliders[1].setRange(0, 1, 0.01);
    Metronomesliders[1].setValue(1); /** Default to 1 */
    metStartButton.onClick = [this](){play();};
    
    Metronomesliders[0].addListener(this);
    Metronomesliders[1].addListener(this);
}

MetronomeUI::MetronomeUI(std::string name)
{
   /**Set Button text */
    thisButton.setButtonText(name);
}

void MetronomeUI::resized()
{
    float MetButtonWidth = getWidth() * 0.15;
    float MetButtonHeight = 40;
    float MetButtonxPosition = 10;
    
    float LabelWidth =  100;
    float LabelHeight = 10;
    float MetGainSliderWidth = 100;
    float MetGainSliderHeight = 100;
    float MetGainSliderxPosition = getWidth() * 0.17;
    float MetGainSlideryPosition = (getHeight() - MetGainSliderHeight) - 10;
    
    float MetBPMSliderWidth = (getWidth() - (MetButtonWidth + MetGainSliderWidth)) - 50;
    float MetBPMSliderHeight = 20;
    float MetBPMyPosition = getHeight() - (MetGainSliderHeight / 2);
    float MetBPMxPosition = (MetGainSliderxPosition + MetGainSliderWidth) + 10;
   
     metStartButton.setBounds(MetButtonxPosition, (getHeight() - MetButtonHeight) - 65, MetButtonWidth, MetButtonHeight);
    metStopButton.setBounds(MetButtonxPosition, (getHeight() - MetButtonHeight) - 10, MetButtonWidth, MetButtonHeight);
    Metronomesliders[0].setBounds(MetBPMxPosition, MetBPMyPosition, MetBPMSliderWidth,  MetBPMSliderHeight);
    Metronomesliders[1].setBounds(MetGainSliderxPosition, MetGainSlideryPosition, MetGainSliderWidth, MetGainSliderHeight);
    
    metBpmLabel.setBounds(MetBPMxPosition, MetBPMyPosition - LabelHeight, LabelWidth, LabelHeight);
    metGainLabel.setBounds(MetGainSliderxPosition, MetGainSlideryPosition - LabelHeight, LabelWidth, LabelHeight);
    
    Metronomesliders[1].setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 30); /** Putting gain slider value box below slider */
}

void MetronomeUI::buttonClicked()
{
    /** Set buttons toggle state for button toggle colour */
    thisButton.setToggleState(! thisButton.getToggleState(), NotificationType::dontSendNotification);
    thisButton.setColour(TextButton::buttonOnColourId, Colours::red);
    
}

void MetronomeUI::setState(bool state)
{
    /** Set button state*/
    thisButton.setToggleState(state, dontSendNotification);
    
}
void MetronomeUI::buttonClicked (Button* Button)
{
    if(Button == &metStartButton)
    {
        DBG("Start");
        
        metStartButton.setToggleState(! metStartButton.getToggleState(), NotificationType::dontSendNotification);
        metStartButton.setColour(TextButton::buttonOnColourId, Colours::red);
        metStopButton.setToggleState(false, dontSendNotification);
        play();
        metStartButton.onClick = [this]() {play(); };
    }
    
     if(Button == &metStopButton)
     {
         metStopButton.setToggleState(! metStopButton.getToggleState(), NotificationType::dontSendNotification);
         metStopButton.setColour(TextButton::buttonOnColourId, Colours::red);
         metStartButton.setToggleState(false, dontSendNotification);
         stop();
         DBG("Stop");
     }
}

void MetronomeUI::play()
{
    metplayState = MetPlayState::Playing;
    m_metbutval = 1;
    getmetButtonState();
}

void MetronomeUI::stop()
{
    metplayState = MetPlayState::Stopped;
    m_metbutval = 0;
    getmetButtonState();
}

void MetronomeUI::getmetButtonState()
{
    /** Getting button state then returning value of button state */
    std::atomic<int> met = m_metbutval;
    
    audioPtr->setMetButtonState(met);

}
void MetronomeUI::getAudioReference(Audio &a)
{
    audioPtr = &a;
}

void MetronomeUI::sliderValueChanged(Slider *slider)
{
    audioPtr->setMetronomeBPM(Metronomesliders[0].getValue());
    
    audioPtr->setMetronomeGain(Metronomesliders[1].getValue());
}
