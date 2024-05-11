#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        // Function for a 3D-ish flower of life pattern
        void draw3DFlowerOfLife(float x, float y, float baseRadius, int steps, int layers, float time);

        float startTime; // To track the time for animation
        ofEasyCam cam; // Camera for 3D view
};
