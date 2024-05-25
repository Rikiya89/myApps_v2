#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    int numShapes;
    vector<ofPoint> positions;
    vector<float> radii;
    vector<ofColor> colors;
    vector<float> angles;
    vector<int> shapes;
    ofFbo fbo;
    float hueOffset;
};
