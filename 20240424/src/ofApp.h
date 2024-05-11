#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        // Recursive function to draw wave-influenced fractal layers
        void drawWaveFractalLayer(int angle, float rad, int depth, float lineWidth);

        // Custom variables for pattern generation
        float angleOffsetA;
        float angleOffsetB;
        float radius;
};
