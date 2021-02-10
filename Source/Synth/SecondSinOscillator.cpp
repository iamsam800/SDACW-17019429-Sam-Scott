//
//  SecondSinOscillator.cpp
//  JuceAudio - App
//
//  Created by Sam Scott on 15/01/2021.
//  Copyright © 2021 UWE. All rights reserved.
//

#include "SecondSinOscillator.hpp"
/*
 *  SinOscillator.cpp
 *  Software Development for Audio
 */


#include <cmath>



float SinOscillatorTwo::renderWaveShape (float currentPhase)
{
    return std::sin (currentPhase);
}


