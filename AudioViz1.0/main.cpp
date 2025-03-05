/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <string.h>
#include <portaudio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "palettes.h"
#include "sliders.h"
#include "render.h"
#include "audio.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
            // Convert 0-9 keypress to index
            colorCycle = key - GLFW_KEY_0;
        } else if(key >= GLFW_KEY_A && key <= GLFW_KEY_F) {
            // Convert A-F key presss to index
            colorCycle = 10 + (key - GLFW_KEY_A);
        }
        // Reset the cycle time for the new color palette
        cycleTime = 0.0f;
    }
}


int main() {
    // Initialize PortAudio
    Pa_Initialize();
    PaStream* stream;
    Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, nullptr);
    Pa_StartStream(stream);

    // Initialize OpenGL (GLFW)
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "AudioViz 1.0", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    // Register mouse callbacks
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    // Register key callbacks
    glfwSetKeyCallback(window, keyCallback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Store new waveform
        updateWaveform();
        // Render waveform
        renderVisualization();
        // Render sliders
        renderSliders();
        // Increment rotation angle for the square
        rotationAngle += 0.5f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
