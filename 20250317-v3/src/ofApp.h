// ofApp.h
#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    int numLayers;
    int numRings;
    int numConnections;
    float maxRadius;
    float rotation;
    float pulseSpeed;
    float waveAmplitude;
    float glowIntensity;
};
