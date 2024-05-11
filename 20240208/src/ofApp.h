#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        vector<float> phase;
        vector<float> amplitude;
        vector<float> frequency;
        vector<ofColor> colors; // Array to hold colors for each wave
        int numWaves; // Number of waves
};
