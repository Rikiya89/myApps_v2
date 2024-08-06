#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    int numLayers;
    vector<ofColor> colors;
    vector<float> radii;
    vector<float> speeds;
    float baseRadius;
    int numShapes;
    float rotationSpeed;
    float globalRotation;
    vector<float> offsets;
};
