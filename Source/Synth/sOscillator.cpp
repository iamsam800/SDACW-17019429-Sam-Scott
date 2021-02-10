/*
 *  SinOscillator.cpp
 *  Software Development for Audio
 */

#include "sOscillator.hpp"

#include <cmath>



float SinOscillator::renderWaveShape (float currentPhase)
{
    return std::sin (currentPhase);
}


