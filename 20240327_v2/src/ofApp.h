#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void mouseMoved(int x, int y);

        int gridWidth;
        int gridHeight;
        float colorChangeRate;
        float sizeChangeRate;
        float noiseOffset;
        float noiseIncrement;
        glm::vec2 mousePos;
        float magnetismStrength;
        vector<float> lifeCycles; // Store the life cycle state for each circle
};
