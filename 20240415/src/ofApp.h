#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    float time;
    ofEasyCam easyCam;
    ofxPostProcessing post;
    int numParticles;
    vector<ofVec3f> particles;
    vector<ofColor> colors;
    vector<float> phase;  // To control size pulsation
    ofMesh backgroundMesh;  // Mesh for background effects
    float meshWaveAmplitude;  // Amplitude of the wave effect on the mesh
};
