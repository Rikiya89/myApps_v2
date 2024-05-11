#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
        
        vector<ofPoint> positions;
        vector<ofColor> colors;
        vector<float> radii;
        vector<float> noiseOffsets;

        ofPoint movingPoint;
        float maxConnectionDistance;

        float backgroundFade; // Variable for background fading
};
