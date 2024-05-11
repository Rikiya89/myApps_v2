#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        float baseHue; // For color animation
        float animationPhase = 0; // For breathing animation

        int circleResolution;
};
