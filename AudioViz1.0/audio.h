/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#ifndef AUDIO_H_
#define AUDIO_H_

#include <vector>
#include <portaudio.h>

extern std::vector<float> audioData;

// Audio callback function
int audioCallback(const void* inputBuffer,
    void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags, void* userData);

void updateWaveform();

#endif /* AUDIO_H_ */