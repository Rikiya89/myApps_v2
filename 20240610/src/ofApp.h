#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    int numShapes;
    float noiseScale;
    vector<ofColor> colors;
    vector<float> rotationSpeeds;
    vector<float> offsets;
};
