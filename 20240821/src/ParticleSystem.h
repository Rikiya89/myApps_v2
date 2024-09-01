#pragma once

#include "ofMain.h"
#include "Particle.h"

class ParticleSystem {
public:
    void setup();
    void update();
    void draw();
    
    void addParticle(ofVec2f position, ofVec2f velocity, ofColor color);
    void applyForce(const ofVec2f& force);

private:
    vector<Particle> particles; // Vector to store all particles
};
