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
#include "sliders.h"

int selectedSlider = -1;
float sliderY = -0.95f;
float sliderWidth = 0.025f;
float sliderHeight = 0.3f;
float knobHeight = 0.025f;
float knobY = sliderY;
bool isDragging = false;
std::vector<float> sliderXPositions = {-0.95f, -0.90f, -0.85f, -0.80f};
std::vector<float> knobYPositions = {sliderY, sliderY, sliderY, sliderY};

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Convert to OpenGL coordinates
        xpos = (xpos / 400.0) - 1.0;
        ypos = 1.0 - (ypos / 300.0);

        if (action == GLFW_PRESS) {
            for (size_t i = 0; i < sliderXPositions.size(); ++i) {
                if (xpos >= sliderXPositions[i] && xpos <= sliderXPositions[i] + sliderWidth &&
                    ypos >= knobYPositions[i] && ypos <= knobYPositions[i] + knobHeight) {
                    isDragging = true;
                    selectedSlider = i; // Track which slider is active
                }
            }
        } else if (action == GLFW_RELEASE) {
            isDragging = false;
            selectedSlider = -1;
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (isDragging) {
        // Convert screen space to OpenGL space
        ypos = 1.0 - (ypos / 300.0); // Flip Y-axis conversion
        
        // Clamp movement within the slider's vertical range
        knobYPositions[selectedSlider] = std::max(sliderY, std::min(sliderY + sliderHeight - knobHeight, (float)ypos));
    }
}

void renderSliders() {
    for (size_t i = 0; i < sliderXPositions.size(); i++){
        float x = sliderXPositions[i];
        float knobY = knobYPositions[i];

        // Draw slider bar
        glColor3f(0.5f, 0.5f, 0.5f); // Gray bar
        glBegin(GL_QUADS);
        glVertex2f(x, sliderY);
        glVertex2f(x + sliderWidth, sliderY);
        glVertex2f(x + sliderWidth, sliderY + sliderHeight);
        glVertex2f(x, sliderY + sliderHeight);
        glEnd();

        // Draw the sliding knob
        glColor3f(0.3f, 0.3f, 0.3); // Slightly darker knob
        glBegin(GL_QUADS);
        glVertex2f(x, knobY);
        glVertex2f(x + sliderWidth, knobY);
        glVertex2f(x + sliderWidth, knobY + knobHeight);
        glVertex2f(x, knobY + knobHeight);
        glEnd();

    }
}