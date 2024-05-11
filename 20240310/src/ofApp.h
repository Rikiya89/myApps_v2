#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
        void drawLayer(float radius, int layerIndex, int totalLayers);

        float growth = 0; // Initialize growth factor
        float time = 0; // Time variable for animation looping
};
