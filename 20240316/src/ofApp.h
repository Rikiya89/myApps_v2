#pragma once

#include "ofMain.h"

class Particle {
public:
    ofPoint pos;
    ofPoint vel;
    float lifespan;
    ofColor color; // Color of the particle

    Particle(ofPoint startPosition) {
        pos = startPosition;
        vel = ofPoint(ofRandom(-2, 2), ofRandom(-2, 2));
        lifespan = 255;

        // Assign a cherry blossom-like color
        color = ofColor(ofRandom(200, 255), ofRandom(175, 200), ofRandom(200, 255));
    }

    void update() {
        pos += vel;
        lifespan -= 3.5;
    }

    void draw() {
        ofSetColor(color, lifespan);
        ofDrawCircle(pos, 3);
    }

    bool isDead() {
        return lifespan < 0;
    }
};


class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        ofVideoGrabber cam;
        ofImage prevFrame;
        ofImage diff;
        vector<Particle> particles;

        void drawGenerativeShapes();
        void addParticle(int x, int y);
};
