#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Particle {
public:
    ofVec3f position;
    ofVec3f velocity;
    float lifeTime;
    bool alive;

    Particle() : position(0, 0, 0), velocity(0, 0, 0), lifeTime(0), alive(false) {}
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void resetParticle(Particle &particle);

    ofEasyCam easyCam;
    vector<Particle> particles;
    ofxPanel gui;
    ofParameter<float> speed;
    ofParameter<int> numParticles;
    ofParameter<ofColor> startColor;
    ofParameter<ofColor> endColor;
    ofParameter<float> size;
};
