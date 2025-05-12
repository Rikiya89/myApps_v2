#pragma once
#include "ofMain.h"

class Particle {
public:
    ofVec2f pos;
    float angleOffset;
    float baseRadius;
    float frequency;

    void setup(float i, float total);
    void update(float time, float cx, float cy);
    void draw();
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    vector<Particle> particles;
    int numParticles;
    ofFbo fbo;
    float time;
};
