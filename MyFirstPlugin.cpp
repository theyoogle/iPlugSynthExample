#include "MyFirstPlugin.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

MyFirstPlugin::MyFirstPlugin(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
    GetParam(kFrequency)->InitDouble("Frequency", 440.0, 50.0, 20000.0, 0.01, "Hz");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
    pGraphics->AttachControl(new ITextControl(b.GetMidVPadded(50), "Hello iPlug 2!", IText(50)));
    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetVShifted(-100), kFrequency));
  };
#endif
}

#if IPLUG_DSP
void MyFirstPlugin::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
    sample *leftOutput = outputs[0];
    sample *rightOutput = outputs[1];

    mOscillator.generate(leftOutput, nFrames);

    // Copy left buffer into right buffer:
    for (int s = 0; s < nFrames; ++s) {
      rightOutput[s] = leftOutput[s];
    }
}
#endif

void MyFirstPlugin::CreatePresets() {
    MakePreset("clean", 440.0);
}

void MyFirstPlugin::OnReset() {
    mOscillator.setSampleRate(GetSampleRate());
}

void MyFirstPlugin::OnParamChange(int paramIdx) {
    switch (paramIdx) {
        case kFrequency:
            mOscillator.setFrequency(GetParam(kFrequency)->Value());
            break;

        default:
            break;
    }
}
