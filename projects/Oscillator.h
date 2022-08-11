//
//  Oscillator.hpp
//  AUv3Framework
//
//  Created by The YooGle on 10/08/22.
//

#ifndef Oscillator_h
#define Oscillator_h

#include <math.h>

enum OscillatorMode {
    OSCILLATOR_MODE_SINE,
    OSCILLATOR_MODE_SAW,
    OSCILLATOR_MODE_SQUARE,
    OSCILLATOR_MODE_TRIANGLE
};

class Oscillator {
private:
    const double mPI = 2 * acos(0.0);
    
    OscillatorMode mOscillatorMode;
    double mFrequency;
    double mPhase;
    double mSampleRate;
    double mPhaseIncrement;
    
    void updateIncrement();
    
public:
    Oscillator() {
        mOscillatorMode = OSCILLATOR_MODE_SINE;
        mFrequency = 440.0;
        mPhase = 0.0;
        mSampleRate = 44100.0;
        
        updateIncrement();
    };
    
    void setMode(OscillatorMode mode);
    void setFrequency(double frequency);
    void setSampleRate(double sampleRate);
    void generate(float* buffer, int nFrames);
};

#endif /* Oscillator_hpp */
