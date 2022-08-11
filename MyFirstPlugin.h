#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"

const int kNumPresets = 1;

enum EParams
{
    kFrequency = 0,
    kNumParams
};

using namespace iplug;
using namespace igraphics;

class MyFirstPlugin final : public Plugin
{
public:
    MyFirstPlugin(const InstanceInfo& info);
    
    void OnReset() override;
    void OnParamChange(int paramIdx) override;

#if IPLUG_DSP // http://bit.ly/2S64BDd
    void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif
    
private:
    double mFrequency;
    Oscillator mOscillator;
    
    void CreatePresets();
};
