#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofxSandLine sandLine; // Instance of ofxSandLine
    vector<ofPoint> controlPoints; // Control points for the spline
    float lastTime; // Last time update was called
};
