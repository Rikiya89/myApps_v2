#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        ofVideoGrabber webcam; // Webcam for capturing live video
        ofShader shader; // Shader for applying effects
};
