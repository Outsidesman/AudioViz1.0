/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <portaudio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "render.h"
#include "audio.h"

std::vector<float> audioData(FRAMES_PER_BUFFER, 0.0f);

// Audio callback function
int audioCallback(const void* inputBuffer, void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags, void* userData) {
    float* in = (float*)inputBuffer;
    if (inputBuffer) {
        for (unsigned int i = 0; i < framesPerBuffer; i++) {
            // Store audio data for visualization
            audioData[i] = in[i];
        }
    }
    return paContinue;
}

// Update waveform history
void updateWaveform() {
    // Add new frame at the front
    waveformHistory.push_front(audioData);
    if (waveformHistory.size() > MAX_WAVEFRAMES){
        // Remove the oldest waveform
        waveformHistory.pop_back();
    }
}