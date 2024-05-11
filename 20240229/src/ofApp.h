#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
        
        ofEasyCam easyCam;
        ofMesh mesh;
        ofLight light;
        ofLight ambientLight;
        float radius;
        float noiseFactor;
        vector<ofColor> colors;
};
