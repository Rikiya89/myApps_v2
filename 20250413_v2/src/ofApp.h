#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    struct RingParticle {
        ofVec2f pos;
        float baseAngle;
        float baseRadius;
    };

    vector<RingParticle> innerRing;
    vector<RingParticle> outerRing;

    int numParticles;
    float timeSpeed;
    float globalRotation;
    float zoom;
};
