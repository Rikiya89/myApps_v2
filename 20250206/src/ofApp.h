// ofApp.h
#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

private:
    int cols, rows;
    float scale;
    float timeOffset;
    float lineLength;
    float animationSpeed;
    float rotationFactor;
};
