#pragma once

#include <iostream>
#include <array>
#include <JuceHeader.h>
#include "../audio/Audio.h"
#include "../../Source/audio/Metronome.h"
#include "../../Source/ui/SynthUI.h"
#include "../../Source/ui/MetronomeUI.h"
#include "../../Source/Synth/BaseOscillator.hpp"
#include "../../Source/Synth/SecondBaseOscillator.hpp"
#include "../../Source/ui/Draw.h"


/**
 Main Component, provides settings menu and switches oscillator wave type here
 */
class MainComponent   : public MenuBarModel,
                        public Button::Listener,
                        public Component
{
public:
    //==============================================================================
    /** Constructor */
    MainComponent (Audio& a);
    
    /** Destructor */
    ~MainComponent() override;
    
    //Comoponent====================================================================
    
    /** Sets bounds of oscillators wave type buttons and calls synth and UI resized functions */
    void resized() override;
    
    /** Paints components */
    void paint (Graphics&) override;
    
    /** Where wavebutton type is changed */
    void buttonClicked (Button* Button) override;
   
    //MenuBarEnums/MenuBarModel=====================================================
    /** enum for Menu */
    enum Menus
    {
        FileMenu = 0,
        
        NumMenus
    };
    
    /** Enum for menu items */
    enum FileMenuItems
    {
        AudioPrefs = 1,
        
        NumFileItems
    };
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    
    int getmetButtonState();
    
  
private:
    OtherLookAndFeel f;
    MetronomeUI UI;
    SynthUI OscilUI;
    
    Audio& audio;
 
    
    /**Buttons, objects  of myButtons button class */
    MetronomeUI waveButton[4] = {MetronomeUI("Sine Wave"), MetronomeUI("Square Wave"), MetronomeUI("Triangle Wave"), MetronomeUI("Saw-Tooth Wave")};
   
    /**Objects of oscillator wave types */
    SinOscillator sin;
    SquareOscillator square;
    SawToothOscillator saw;
    TriangleOscillator triangle;
    
    SinOscillatorTwo sin2;
    SquareOscillatorTwo square2;
    TriangleOscillatorTwo triangle2;
    SawToothOscillatorTwo saw2;
   
  
  //  float m_modwheelval {0.f};
//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
