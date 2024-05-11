#pragma once

#include "ofMain.h"

class Particle {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    float radius;
    ofColor color;
    float lifespan; // Lifespan of the particle

    Particle(glm::vec2 startPosition, glm::vec2 startVelocity, float startRadius, ofColor startColor)
    : position(startPosition), velocity(startVelocity), radius(startRadius), color(startColor), lifespan(255) {}

    void update() {
        position += velocity;
        lifespan -= 2; // Decrease lifespan
        color.a = lifespan; // Update alpha based on lifespan
    }

    // Mark isAlive as const because it does not modify the object
    bool isAlive() const {
        return lifespan > 0;
    }
};


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    vector<Particle> particles;
    void addParticle();
};
