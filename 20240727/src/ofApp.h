#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void drawFlowerOfLife(float x, float y, float radius, int depth);
    ofColor getColor(int depth, float time);

    float rotationAngle;  // Angle for rotation
    float scaleFactor;    // Factor for scaling
    float pulse;          // Pulse effect for glow
};
