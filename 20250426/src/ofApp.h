#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    vector<ofVec3f> positions;
    vector<ofFloatColor> colors;
    vector<ofVec3f> velocities;
    vector<ofVec3f> stars; // background stars

    int numParticles = 300;
    float rotationAngle = 0.0;
    float cameraAngle = 0.0;
    float pulsePhase = 0.0; // for pulsing effect
};
