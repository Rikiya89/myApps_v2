// ofApp.h
#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;
    vector<ofVec3f> points;
    vector<float> angles;
    vector<float> speeds;
    float time;
};
