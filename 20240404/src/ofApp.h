#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    struct Particle {
        glm::vec2 position;
        glm::vec2 velocity;
        ofColor color;
        float radius;
    };

    vector<Particle> particles;
    void addParticle();
    void connectParticles();
    ofFbo fbo; // Framebuffer object for rendering effects
    float time; // For background animation
};
