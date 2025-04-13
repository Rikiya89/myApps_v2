#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    vector<ofVec3f> points; // Store 3D points
    float time; // Animation timer
    ofEasyCam cam; // Camera for 3D view
};
