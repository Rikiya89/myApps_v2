#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);

    vector<ofPoint> points;       // Particle positions
    vector<ofPoint> velocities;  // Particle velocities
    int numPoints = 500;         // Number of particles
    float noiseScale = 0.01;     // Perlin noise scale
    ofPoint mousePos;            // Mouse position
};
