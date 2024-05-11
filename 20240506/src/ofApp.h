#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);

    struct Particle {
        ofPoint position;
        ofVec2f velocity;
        float radius;
        ofColor color;
        list<ofPoint> trail;
    };

    vector<Particle> particles;
    int numParticles = 100;
    ofPoint mousePos;
    ofFbo sceneFbo;  // Framebuffer for advanced effects
    float lastUpdateTime;  // Time tracking for smooth animation
};
