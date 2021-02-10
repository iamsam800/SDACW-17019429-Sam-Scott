//
//  Metronome.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 03/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "Metronome.h"

Metronome::Metronome()
{
    
    metaudioFormatManager.registerBasicFormats();
    
    File MetronomeClick{ File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory) };
    auto myMetronome = MetronomeClick.findChildFiles(File::TypesOfFileToFind::findFiles,true,  "MetronomeSoundSDA.wav");
    
          DBG("FILE LOADING\n");
          auto MetronomeFormatReader = metaudioFormatManager.createReaderFor(myMetronome[0]); /** Creating a reader for file */
          pMetronomeSample.reset(new AudioFormatReaderSource (MetronomeFormatReader, true)); /** Puting into memory */
}

void Metronome::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    
    metSampleRate = sampleRate;
    
    
    DBG("this sample Rate: " << sampleRate << "\n");
    metSampleRate = sampleRate; /** make sample rate match global (when metronome is working) */
    metInterval = 60.0 / metBPM * metSampleRate;
    HighResolutionTimer::startTimer(60.0);
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate); /** pointer to prepareToPlay function in MainComponent class*/
        DBG("FILE LOADED");
        
    }
    
    else
    {
        DBG("File Filed to load\n");
    }
    
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    
  
    auto bufferSize = bufferToFill.numSamples;
    
    metTotalSamples+=bufferSize; /** adds buffersize onto totalSamples */
    
    metNumSamplesRemaining = metTotalSamples % metInterval; /** Gives result: remainder of samples left */
    
   
    if ((metNumSamplesRemaining + bufferSize) >= metInterval) /** if samples remaining + bufferSize are greater or equal to interval metronome clicks */
    {
        const auto timeToStartPlaying = metInterval - metNumSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);
        
        for(auto sample = 0; sample < bufferSize; sample++)
        {
            if(sample == timeToStartPlaying) /** if sample is equal to the time the sample will be plated buffer will start filling */
            {
                
            pMetronomeSample->getNextAudioBlock(bufferToFill);
            
            }
        }
}
        if(pMetronomeSample->getNextReadPosition() != 0) /** If sample in next read position is not equal to 0 continue filling buffer */
        {
            pMetronomeSample->getNextAudioBlock(bufferToFill);
        }
}

void Metronome::reset()
{
    /**Reset metronome */
    metTotalSamples = 0;
    
}

void Metronome::hiResTimerCallback()
{
    /** Maths for working out interval between metronome clicks */
    metInterval = 60.0 / metBPM * metSampleRate;
    
}

void Metronome::setBPM(int newBPM)
{
    /**Setting Metronome BPM*/
    metBPM = newBPM;
  
}

void Metronome::setMetGain(float newGain)
{
    /**Setting metronome gain */
    setGain(newGain);
    DBG("GAIN: " << getGain());
    DBG("NEW GAIN " << newGain);
}
