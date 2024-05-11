#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        // Advanced visual elements
        ofShader shader; // Shader for sophisticated effects
        float time;

        // Color transitions
        ofColor startColor, endColor;
        float colorTransitionSpeed;
};
