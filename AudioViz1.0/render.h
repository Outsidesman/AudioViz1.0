/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#ifndef RENDER_H
#define RENDER_H

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define MAX_WAVEFRAMES 500

// Time variable for background color transition
extern float cycleTime;

// Keep track of which color cycle we're on
extern int colorCycle;

// Remember which color in the palette we were just on
extern int prevIndex;

// Store the square colors
extern int squareR;
extern int squareG;
extern int squareB;

// Current size and rotation angle of the square
extern float squareScale;
extern float rotationAngle;

// Store past waveforms and audio samples
extern std::deque<std::vector<float>> waveformHistory;
//extern std::vector<float> audioData;

// OpenGL rendering function to render the waveform
void renderVisualization();

// Draw the rotated square to the screen
void renderRotatingSquare();

// Compute interpolated background color
void updateBackgroundColor();

// Compute interploated square color
void updateSquareColor();

// Update the square's size based on the audio amplitude
void updateSquareScale();

#endif