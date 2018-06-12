//
//  Synthesizer.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#include "Synthesizer.hpp"

Synth::Synth(double sampleRate)
{
    this->sampleRate = sampleRate;

    oscillators = new Oscillator*[3];
    
    //create a carrier a modulator and a noise oscillator
    oscillators[0] = new SineWave(sampleRate, 220, 0);
    oscillators[1] = new SineWave(sampleRate, 0, 0);
    oscillators[2] = new RandomGenerator(sampleRate, 0, 0);
    
}

Synth::~Synth()
{
    delete[] oscillators;
    oscillators = nullptr;
}


void Synth::setLFO(int LFOnumber)
{
    //checks if the LFOparam has changed. If it has, it changes the LFO wave form
    if(LFOnumber != previousWaveForm || !initWaveForm){
        initWaveForm = true;
        switch (LFOnumber) {
            case 1: { oscillators[2] = new SawWave(sampleRate, 0, phase);
                break; }
            case 2: { oscillators[2] = new InvertedSawWave(sampleRate, 0, phase);
                break; }
            case 3: { oscillators[2] = new SineWave(sampleRate, 0, phase);
                break; }
            case 4: { oscillators[2] = new SquareWave(sampleRate, 0, phase);
                break; }
            case 5: { oscillators[2] = new RandomGenerator(sampleRate, 0, phase);   //execution starts at this case label
                break; }
        }
        previousWaveForm = LFOnumber;
    }
    
}

void Synth::setPhaseLFO(double phase)
{
    this->phase = phase;
}

void Synth::setGlide(double glide)
{
    this->glideValue = glide;
}

void Synth::setFrequency(double frequency)
{
    this->frequency = frequency;
}

void Synth::setLFOfreq(double LFOfreq)
{
    this->LFOfreq = LFOfreq;
}

void Synth::setLFOdepth(double LFOdepth)
{
    this->LFOdepth = LFOdepth;
}

void Synth::setRatio(float fmRatio)
{
    this->fmRatio = fmRatio;
}

void Synth::setModDepth(float fmModDepth)
{
    this->fmModDepth = fmModDepth;
}


double Synth::getLFOsample()
{
    return oscillators[2]->getSample();
}

double Synth::getModulatorSample()
{
    return oscillators[1]->getSample();
}
void Synth::updateFrequency()
{
   //fm synthesis, 0 is the carrier 2 is the modulator
    oscillators[1]->setFrequency(frequency * fmRatio);
    oscillators[0]->setFrequency(frequency + ((oscillators[1]->getSample())* (fmModDepth * frequency * fmRatio)));
}

double Synth::mtof(double midiPitch)
{
    //convert MIDI-pitch to frequency
    double pitch = midiPitch;
    pitch = pow(2.0,(pitch-69.0)/12.0) * 440.0;
    return pitch;
}


double Synth::process()
{
    //update frequency for FM synthesis
    updateFrequency();
    
    oscillators[0]->tick();
    oscillators[1]->tick();
    oscillators[2]->tick();
   
    //get sample of the carrier
    sample = oscillators[0]->getSample();
    
    return sample;
}
