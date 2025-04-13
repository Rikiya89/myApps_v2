// ofApp.h
#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
private:
    vector<ofVec2f> points;
    vector<float> radii;
    vector<ofColor> colors;
    int numCircles;
    float timeOffset;
};
