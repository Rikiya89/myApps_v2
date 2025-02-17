#pragma once

#include "ofMain.h"
#include <vector>

// 🌟 Particle Class (Increased Density & Faster Motion)
struct Particle {
    ofVec2f position;
    ofVec2f velocity;
    float alpha;
    float size;

    Particle(float x, float y) {
        position.set(x, y);
        velocity.set(ofRandom(-2, 2), ofRandom(-2, 2)); // **Smoother but Faster**
        alpha = 255;
        size = ofRandom(3, 6);
    }

    void update(float noiseFactor, float time) {
        float angle = noiseFactor * TWO_PI * 2;
        velocity += ofVec2f(cos(angle) * 0.5, sin(angle) * 0.5); // **More Active Acceleration**
        velocity *= 0.97; // **Still Smooth, But More Motion**
        position += velocity;
        alpha = 180 + sin(time * 2) * 70; // **Faster Pulsating Glow**
    }

    void draw() {
        ofSetColor(255, alpha);
        ofDrawCircle(position.x, position.y, size);
    }
};

// 🌌 Larger Fractal Sacred Geometry
void drawFractalCircle(float x, float y, float radius, int depth, float time);

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    vector<Particle> particles;
    float animationTime;
};
