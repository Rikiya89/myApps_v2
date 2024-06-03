#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y );

private:
    int numShapes;
    float angle;
    float angleIncrement;
    vector<ofColor> colors;
    vector<float> radii;
    vector<float> speeds;
    vector<float> offsets;
    vector<float> depths;
    float mouseXFactor;
    float mouseYFactor;
};
