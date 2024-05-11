#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber webcam; // Webcam object to capture video
    ofImage previousFrame; // Store the previous frame
    ofImage diffImage;     // Image to store the difference between frames
};
