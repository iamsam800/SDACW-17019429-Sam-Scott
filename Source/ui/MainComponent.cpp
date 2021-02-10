/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (Audio& a) : 
audio (a)
{
    UI.getAudioReference(a);
    OscilUI.getReference(a);
    setLookAndFeel(&f);
    
    addAndMakeVisible(UI);
    addAndMakeVisible(OscilUI);
    
    /** Creating default oscillator wavet type on app launch */
   // a.setOscillatorType(sin, sin2);
    
    /** Setting size of window */
    setSize (600, 400);
    
    /** Making array of wave type buttons visable, wanted to do an if loop but accsess problems occured */
    addAndMakeVisible(waveButton[0].thisButton);
    addAndMakeVisible(waveButton[1].thisButton);
    addAndMakeVisible(waveButton[2].thisButton);
    addAndMakeVisible(waveButton[3].thisButton);
    
    waveButton[0].thisButton.addListener(this);
    waveButton[1].thisButton.addListener(this);
    waveButton[2].thisButton.addListener(this);
    waveButton[3].thisButton.addListener(this);
    
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
    
}

MainComponent::~MainComponent()
{
   setLookAndFeel (nullptr);
    
}

//==============================================================================
void MainComponent::resized()
{
    /** Doing math to make each component dynamic on windw size change, and storing in respective variables to be used in set bounds */
    float WidthOfWindow = getWidth();
    float HeightOfWindow = getHeight();
    float WaveButtonWidth = (WidthOfWindow * 0.25) - 5;
    float WaveButtonHeight = HeightOfWindow * 0.1;
    
    float oscilUI_posY = WaveButtonHeight + 5;
    float oscilUI_height = (HeightOfWindow * 0.63) - WaveButtonHeight;
    
    float UI_posY = (HeightOfWindow * 0.63) + WaveButtonHeight;
    float UI_height = (HeightOfWindow * 0.37) - WaveButtonHeight;
    /** Applying variables created above and placing them in their respective paramater for getbounds */
    waveButton[0].thisButton.setBounds(0, 5, WaveButtonWidth, WaveButtonHeight);
    waveButton[1].thisButton.setBounds(getWidth() * 0.25, 5, WaveButtonWidth, WaveButtonHeight);
    waveButton[2].thisButton.setBounds(getWidth() * 0.5, 5, WaveButtonWidth, WaveButtonHeight);
    waveButton[3].thisButton.setBounds(getWidth() * 0.75, 5, WaveButtonWidth, WaveButtonHeight);
    
    OscilUI.setBounds(0, oscilUI_posY, WidthOfWindow, oscilUI_height);
    UI.setBounds(0, UI_posY, WidthOfWindow, UI_height);
    
}
void MainComponent::paint (Graphics& g)
{
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
}

//MenuBarCallbacks==============================================================
StringArray MainComponent::getMenuBarNames()
{
    /**Getting menu bar names */
    auto names = { "File" };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
    /** Adding audio preferences */
    PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
    return menu;
}

void MainComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
    /** Getting audio preferences preference change selection */
    if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            DialogWindow::LaunchOptions la;
            la.dialogTitle = "Audio Settings";
            OptionalScopedPointer<Component> osp (std::make_unique<AudioDeviceSelectorComponent>
                                                  (audio.getAudioDeviceManager(),
                                                   1, 2, 2, 2,
                                                   true, true, true, false));
            osp->setSize (450, 350);
            la.content = std::move (osp);
            la.componentToCentreAround = this;
            la.launchAsync();
        }
    }
}

void MainComponent::buttonClicked(Button *Button)
{
    
   /**Setting metronome playstate to play by calling lambda function, as well as setting play colour to red and stopping stop button from being red when this button is cilcked */
  
    /**For loop for initialising button states through calls to 'setState()' in button class, as well as button cilcked functionality for switching wave type */
    for(int x = 0; x < sizeof(waveButton); x++)
    {
        if(Button == &waveButton[x].thisButton)
        {
            waveButton[0].setState(false);
            waveButton[1].setState(false);
            waveButton[2].setState(false);
            waveButton[3].setState(false);
            waveButton[x].buttonClicked();
            
            switch (x) {
                case 0:
                    audio.setOscillatorType(sin, sin2);
                    break;
                
                case 1:
                    audio.setOscillatorType(square, square2);
                    break;
                    
                case 2:
                    audio.setOscillatorType(triangle, triangle2);
                    break;
                    
                case 3:
                    audio.setOscillatorType(saw, saw2);
                    break;
                }
           }
        }
    
}


