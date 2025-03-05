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
#include "palettes.h"

const std::string palatteNames[] = {
    "cancer",
    "petals",
    "rouge",
    "periwinkle",
    "wedding",
    "retro",
    "easter",
    "cosmicHorror",
    "coolGreen",
    "badDracula",
    "greenLeaf",
    "beiges",
    "spaceAlien",
    "neutralBrown",
    "easter2",
    "fallRainbow"
};

const int* colorPalettes[] = {
    &cancer[0][0],
    &petals[0][0],
    &rouge[0][0],
    &periwinkle[0][0],
    &wedding[0][0],
    &retro[0][0],
    &easter[0][0],
    &cosmicHorror[0][0],
    &coolGreen[0][0],
    &badDracula[0][0],
    &greenleaf[0][0],
    &beiges[0][0],
    &spaceAlien[0][0],
    &neutralBrown[0][0],
    &easter2[0][0],
    &fallRainbow[0][0]
};
const int totalPalettes = sizeof(colorPalettes) / sizeof(colorPalettes[0]);
