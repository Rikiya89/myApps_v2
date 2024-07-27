#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber webcam;
    ofxCvColorImage colorImg;
    ofxPanel gui;
    ofParameter<float> threshold;
};
