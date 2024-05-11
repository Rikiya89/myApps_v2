#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam; // Camera for 3D perspective
    vector<ofLight> lights; // Multiple light sources for dynamic lighting effects
};
