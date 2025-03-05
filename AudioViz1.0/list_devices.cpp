/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#include <iostream>
#include "portaudio.h"

int main() {
    Pa_Initialize();
    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cerr << "ERROR: Pa_GetDeviceCount returned " << numDevices << "\n";
        return 1;
    }

    std::cout << "Available audio devices:\n";
    for (int i = 0; i < numDevices; i++) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "Device " << i << ": " << deviceInfo->name
                  << " (Max input channels: " << deviceInfo->maxInputChannels
                  << ", Max output channels: " << deviceInfo->maxOutputChannels << ")\n";
    }

    Pa_Terminate();
    return 0;
}
