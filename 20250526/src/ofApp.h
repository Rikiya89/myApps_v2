#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofxBox2d box2d;
    vector<shared_ptr<ofxBox2dCircle>> circles;
    float colorHue = 0;
    float time = 0;
};
