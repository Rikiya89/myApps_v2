#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        int circleCount;
        vector<glm::vec2> circlePositions;
        vector<float> circleSizes;
        vector<ofColor> circleColors;
        vector<float> noiseOffsets;
};
