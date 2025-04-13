#pragma once
#include "ofMain.h"

class Particle {
public:
    ofVec2f position, velocity, acceleration;
    float maxSpeed, noiseOffset, size, smoothingFactor;
    
    Particle();
    void update(float timeFactor);
    void applyForce(ofVec2f force);
    void edges();
    void draw();
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    vector<Particle> particles;
    ofFbo fbo;
    float baseNoiseScale;
    bool useLines;
};
