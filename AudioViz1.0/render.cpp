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
#include <GL/glut.h>
#include <GLKit/GLKMatrix4.h>
#include "render.h"
#include "sliders.h"
#include "palettes.h"
#include "audio.h"

float cycleTime = 0.0f;
int colorCycle = 0;
int prevIndex = -1;
int squareR = 0;
int squareG = 0;
int squareB = 0;

float squareScale = 1.0f;
float rotationAngle = 0.0f;

std::deque<std::vector<float>> waveformHistory;

void renderVisualization() {
    updateBackgroundColor();
    glClear(GL_COLOR_BUFFER_BIT);
    float yOffset = 0.0f;

    // Normalize redness slider value
    float redness = (knobYPositions[0] - (-0.95f)) / (-0.675f - (-0.95f));

    // Normalize amplitude slider value
    float amplitude = (knobYPositions[1] - (-0.95f)) / (-0.675f - (-0.95f)) * 100;

    // Normalize point size slider value
    float pointSize = (knobYPositions[2] - (-0.95f)) / (-0.675f - (-0.95f)) * 9;

    for (size_t i = 0; i < waveformHistory.size(); ++i) {
        // Fading effect
        float alpha = 1.0f - (i / (float)MAX_WAVEFRAMES);
        float r = redness;
        float g = alpha;         // Green fades out
        float b = 1.0f - alpha;  // Blue fades in, creating cyan transition

        // RGBA (transitioning from green to cyan with transparency)
        glColor4f(r, g, b, alpha);
        
        glPointSize(1.0f + pointSize);
        glBegin(GL_POINTS); // Draw waveform
        for (size_t j = 0; j < waveformHistory[i].size(); j++) {
            float x = (float)j / (waveformHistory[i].size() - 1) * 2.0f - 1.0f;  // Map index to screen space (-1 to 1)
            float y = waveformHistory[i][j] * (10 + amplitude) + yOffset;        // Offset for falling effect
            glVertex2f(x, y);
        }
        glEnd();
        
        yOffset -= 0.005f;  // Move older frames downward
    }
    
    renderRotatingSquare(); // Draw rotating square
}

void renderRotatingSquare() {
    updateSquareScale();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(squareScale, squareScale, 1.5f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    updateSquareColor();
    glColor3f(squareR / 255.0f, squareG / 255.0f, squareB / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f( 0.1f, -0.1f);
    glVertex2f( 0.1f,  0.1f);
    glVertex2f(-0.1f,  0.1f);
    glEnd();
    glPopMatrix();
}

void updateBackgroundColor() {
    cycleTime += 0.001f; // Speed of transition
    int index1 = ((int)cycleTime) % 5;
    int index2 = (index1 + 1) % 5;
    float blendFactor = cycleTime - (int)cycleTime;

    // Check to see if we've cycled through a palette
    if (index1 == 0 && prevIndex == 4) {
        colorCycle = (colorCycle + 1) % totalPalettes;
        cycleTime = 0.0f; // Reset cycle time for smooth blending
    }
    prevIndex = index1;
    const int* currentPalette = colorPalettes[colorCycle];

    int r = (1.0f - blendFactor) * currentPalette[index1 * 3] + blendFactor * currentPalette[index2 * 3];
    int g = (1.0f - blendFactor) * currentPalette[index1 * 3 + 1] + blendFactor * currentPalette[index2 * 3 + 1];
    int b = (1.0f - blendFactor) * currentPalette[index1 * 3 + 2] + blendFactor * currentPalette[index2 * 3 + 2];

    // Draw the background
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

void updateSquareColor() {
    int index1 = ((int)cycleTime + 1) % 5;
    int index2 = (index1 + 1) % 5;
    float blendFactor = cycleTime - (int)cycleTime;
    const int* currentPalette = colorPalettes[colorCycle];

    squareR = (1.0f - blendFactor) * currentPalette[index1 * 3] + blendFactor * currentPalette[index2 * 3];
    squareG = (1.0f - blendFactor) * currentPalette[index1 * 3 + 1] + blendFactor * currentPalette[index2 * 3 + 1];
    squareB = (1.0f - blendFactor) * currentPalette[index1 * 3 + 2] + blendFactor * currentPalette[index2 * 3 + 2];
}

void updateSquareScale() {
    float sum = 0.0f;
    float ampBoost = (knobYPositions[3] - (-0.95f)) / (-0.675f - (-0.95f)) * 100;
    for (float sample : audioData) {
        sum += std::abs(sample);
    }
    float avgAmplitude = sum / audioData.size();

    // Normalize and scale the amplitude to keep resonable square size changes
    squareScale = 1.0f + avgAmplitude * (45.0f + ampBoost); // Adjust multiplier for effect intensity
}