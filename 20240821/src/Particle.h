#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle(ofVec2f position, ofVec2f velocity, ofColor color);

    void update();
    void draw();

    bool isDead() const;

    void applyForce(const ofVec2f& force); // Method to apply a force to the velocity

private:
    ofVec2f position;
    ofVec2f velocity;
    ofColor color;

    float lifespan;
    float maxLifespan;
    float size;
    float initialSize;
};
