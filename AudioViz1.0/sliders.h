/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/
#ifndef SLIDER_H
#define SLIDER_H

// Slider Properties
extern float sliderY;                       // Y position (bottom left of the screen)
extern float sliderWidth;                   // Horizontal width of the sliders
extern float sliderHeight;                  // Vertical length of the sliders
extern float knobHeight;                    // Height of the knobs
extern float knobY;                         // Starting position of the knobs
extern bool isDragging;                     // Track whether the sliders are being down-clicked
extern std::vector<float> sliderXPositions; // Positions of the sliders (bottom left of screen)
extern std::vector<float> knobYPositions;   // Starting position of the knobs

// Handle mouse being down/up-clicked
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// Handle cursor clicking/draggind knobs
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

// Draw the sliders to the screen
void renderSliders();



#endif