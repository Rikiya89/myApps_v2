#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Number of sacred layers (depth and density)
    int numLayers = 20;

    // Base radius for the core structure
    float baseRadius = 30;

    // Amplitude for sacred oscillations
    float amplitude = 18;

    // Breathing speed (pulsation of the mandala)
    float breathSpeed = 2.0;

    // Rotation speed (divine vortex spinning)
    float rotationSpeed = 0.08;

    // Rotation angle (infinite spinning)
    float rotationAngle = 0;

    // Global expansion effect (universal breath)
    float universeExpansion = 1.0;

    // Core pulsation effect (sacred light energy)
    float corePulse = 5.0;
};
