#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        // Webcam
        ofVideoGrabber webcam;

        // Add variables for your generative art here
        // Example: ofMesh mesh;
};
