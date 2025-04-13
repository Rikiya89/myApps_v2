#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;
    vector<ofVec3f> spherePositions;
};
