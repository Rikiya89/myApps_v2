#pragma once

#include "ofMain.h"
#include <vector>

// Particle class definition
class Particle {
public:
    ofPoint pos;
    ofVec2f velocity;
    ofColor color;
    float radius;
    float lifespan;

    Particle(ofPoint p, ofVec2f v, ofColor c, float r, float life)
        : pos(p), velocity(v), color(c), radius(r), lifespan(life) {}

    void update() {
        pos += velocity;
        lifespan -= 1.0;
        // Additional behaviors (e.g., gravity, bouncing) can be added here
    }

    bool isDead() const {
        return lifespan <= 0;
    }

    void draw() const {
        ofSetColor(color, lifespan);
        ofDrawCircle(pos, radius);
        // Optional: Add more sophisticated graphics (e.g., glow effect)
    }
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

private:
    ofVideoGrabber webcam;
    ofPixels processedPixels;
    ofTexture texture;

    ofPixels previousPixels;
    ofPixels motionPixels;
    ofTexture motionTexture;

    std::vector<Particle> particles;
    const int MAX_PARTICLES = 1000;
    void addParticle(int x, int y);
};
