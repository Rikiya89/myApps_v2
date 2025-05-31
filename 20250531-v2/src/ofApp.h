#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    float time;
    vector<ofVec3f> points;
    ofEasyCam cam;
};
