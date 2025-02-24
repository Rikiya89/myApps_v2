#pragma once

#include "ofMain.h"
#include "ofxFluid.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);

    ofxFluid fluid;
    ofVec2f oldMouse;
};
