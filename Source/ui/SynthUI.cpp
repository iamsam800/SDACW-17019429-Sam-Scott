//
//  Sliders.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 05/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SynthUI.h"


 SynthUI::SynthUI()
{
    addAndMakeVisible(envSliders[0]);
    addAndMakeVisible(envSliders[1]);
    addAndMakeVisible(envSliders[2]);
    addAndMakeVisible(envSliders[3]);
    
    envLabel[0].setText("A", dontSendNotification);
    envLabel[1].setText("D", dontSendNotification);
    envLabel[2].setText("S", dontSendNotification);
    envLabel[3].setText("R", dontSendNotification);
    envLabel[0].attachToComponent(&envSliders[0], false);
    envLabel[1].attachToComponent(&envSliders[1], false);
    envLabel[2].attachToComponent(&envSliders[2], false);
    envLabel[3].attachToComponent(&envSliders[3], false);
    
    /** Making envelope sliders vertical */
    envSliders[0].setSliderStyle(Slider::SliderStyle::LinearVertical);
    envSliders[1].setSliderStyle(Slider::SliderStyle::LinearVertical);
    envSliders[2].setSliderStyle(Slider::SliderStyle::LinearVertical);
    envSliders[3].setSliderStyle(Slider::SliderStyle::LinearVertical);
   
    envSliders[0].setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    envSliders[1].setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    envSliders[2].setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    envSliders[3].setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    envSliders[0].setRange(0.1, 5.0f, 0.01); /*Attack slider range */
    envSliders[1].setRange(0.1, 2.0f, 0.01); /*Decay slider range */
    envSliders[2].setRange(0.1, 1.0f, 0.01); /*Sustain slider range */
    envSliders[3].setRange(0.1, 5.0f, 0.01); /*Release slider range */
    
    envSliders[0].setValue(0.1f); /*Attack defaultvalue */
    envSliders[1].setValue(0.6f); /*Decay default value */
    envSliders[2].setValue(0.7f); /*Sustain default value */
    envSliders[3].setValue(0.5f); /*Release default value /*/
    
    /** Making Listeners for envelope sliders */
    envSliders[0].addListener(this);
    envSliders[1].addListener(this);
    envSliders[2].addListener(this);
    envSliders[3].addListener(this);
    
    addAndMakeVisible(fmSliders[0]);
    addAndMakeVisible(fmSliders[1]);
    
    fmSliders[0].setSliderStyle(Slider::SliderStyle::Rotary);
    fmSliders[1].setSliderStyle(Slider::SliderStyle::Rotary);
    fmSliders[0].setTextBoxStyle(Slider::TextBoxAbove, false, 50, 25);
    fmSliders[1].setTextBoxStyle(Slider::TextBoxAbove, false, 50, 25);
    
    fmSliders[0].setRange(0.1f, 100.0f, 0.01);
    fmSliders[1].setRange(0, 16, 1);
    
    fmSliders[0].addListener(this);
    fmSliders[1].addListener(this);
    
    addAndMakeVisible(filterSliders[0]);
    addAndMakeVisible(filterSliders[1]);
    
    filterSliders[0].setSliderStyle(Slider::SliderStyle::Rotary);
    filterSliders[1].setSliderStyle(Slider::SliderStyle::Rotary);
    filterSliders[0].setTextBoxStyle(Slider::TextBoxAbove, false, 50, 25);
    filterSliders[1].setTextBoxStyle(Slider::TextBoxAbove, false, 50, 25);
    

    filterSliders[0].setRange(50.1f, 15000.f, 0.01);
    filterSliders[0].setValue(15000.f);
    filterSliders[1].setRange(0.1f, 1.f, 0.01);
    

    filterSliders[0].addListener(this);
    filterSliders[1].addListener(this);
    
    addAndMakeVisible(raidialLabel[0]);
    addAndMakeVisible(raidialLabel[1]);
    addAndMakeVisible(raidialLabel[2]);
    addAndMakeVisible(raidialLabel[3]);
    
    raidialLabel[0].setText("FM Mod Frequency", dontSendNotification);
    raidialLabel[1].setText("FM Mod Index", dontSendNotification);
    raidialLabel[2].setText("LPF Cutoff", dontSendNotification);
    raidialLabel[3].setText("LPF Q", dontSendNotification);
   
}

void SynthUI::resized()
{
    
    // Size of 'canvas' in relation to waveButtons & MetUI //
    float UI_bounds_X = getWidth();
    float UI_bound_Y = getHeight();
    
    float SLIDERTOTAL_Width = UI_bounds_X * 0.5;
    
    float slider_Width = SLIDERTOTAL_Width * 0.25;
    float Slider_Height = (UI_bound_Y * 0.7) - 5;
    float slider_X = slider_Width + 5;
    float slider_Y = 20;
    
    envSliders[0].setBounds(0, slider_Y, slider_Width, Slider_Height);
    envSliders[1].setBounds(slider_X, slider_Y, slider_Width, Slider_Height);
    envSliders[2].setBounds(slider_X * 2, slider_Y, slider_Width, Slider_Height);
    envSliders[3].setBounds(slider_X * 3, slider_Y, slider_Width, Slider_Height);
    
    float slider_label_Y = Slider_Height + 15;
    float sliderLabel_1_X = envSliders[0].getX() + (envSliders[0].getWidth() * 0.5);
    float sliderLabel_2_X = envSliders[1].getX() + (envSliders[1].getWidth() * 0.5);
    float sliderLabel_3_X = envSliders[2].getX() + (envSliders[2].getWidth() * 0.5);
    float sliderLabel_4_X = envSliders[3].getX() + (envSliders[3].getWidth() * 0.5);
    
    envLabel[0].setBounds(sliderLabel_1_X - 10, slider_label_Y, 20, 20);
    envLabel[1].setBounds(sliderLabel_2_X - 10, slider_label_Y, 20, 20);
    envLabel[2].setBounds(sliderLabel_3_X - 10, slider_label_Y, 20, 20);
    envLabel[3].setBounds(sliderLabel_4_X - 10, slider_label_Y, 20, 20);
    
    float raidial_Height = 75;
    float raidialWidth = 75;
    
    float fmRaidial_y = (getHeight() * 0.1) + 5;
    float filterRaidial_Y = fmRaidial_y + raidial_Height + 40;
    float Raidial_1_x = (getWidth() * 0.5) + 40;
    float Raidial_2_x = Raidial_1_x + raidialWidth + 50;
    
    fmSliders[0].setBounds(Raidial_1_x, fmRaidial_y, raidialWidth, raidial_Height);
    fmSliders[1].setBounds(Raidial_2_x, fmRaidial_y, raidialWidth, raidial_Height);
    
    filterSliders[0].setBounds(Raidial_1_x, filterRaidial_Y, raidialWidth, raidial_Height);
    filterSliders[1].setBounds(Raidial_2_x, filterRaidial_Y, raidialWidth, raidial_Height);
   
    float labael_width = 100;
    raidialLabel[0].setBounds(Raidial_1_x, fmRaidial_y - 20, labael_width, 20);
    raidialLabel[1].setBounds(Raidial_2_x, fmRaidial_y - 20, labael_width, 20);
    raidialLabel[2].setBounds(Raidial_1_x, filterRaidial_Y - 20, labael_width, 20);
    raidialLabel[3].setBounds(Raidial_2_x, filterRaidial_Y - 20, labael_width, 20);
}

void SynthUI::sliderValueChanged (Slider* slider)
{
    std::atomic<float> a = envSliders[0].getValue();
    std::atomic<float> d = envSliders[1].getValue();
    std::atomic<float> s = envSliders[2].getValue();
    std::atomic<float> r = envSliders[3].getValue();
    
    std::atomic<float> modfrequency = fmSliders[0].getValue();
    std::atomic<int> modindex = fmSliders[1].getValue();
    
    std::atomic<float> lpfCutoff = filterSliders[0].getValue();
    std::atomic<float> lpfQ = filterSliders[1].getValue();
    
    audioPTR->setEnvelopeParameters(&a,&d, &s, &r);
    audioPTR->setFmParameters(&modfrequency, &modindex);
    audioPTR->setFilterParameters(&lpfCutoff, &lpfQ);
}

void SynthUI::getReference(Audio &a)
{
    audioPTR = &a;
}
