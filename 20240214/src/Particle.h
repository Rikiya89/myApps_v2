//
//  Particle.hpp
//  20240214
//
//  Created by okawa_rikiya on 2024/02/14.
//

#define Particle_hpp

#pragma once
#include "ofMain.h"

class Particle {
public:
    ofVec2f position;
    ofVec2f velocity;
    ofColor startColor, endColor;
    float radius;
    float lifeTime; // For color transition over time
    float age; // Current age of the particle
    float maxLifeTime; // Maximum age before resetting

    Particle();
    void setup(ofVec2f startPosition, ofVec2f startVelocity, ofColor startColor, ofColor endColor, float startRadius, float maxLife);
    void update();
    void draw();
    void applyForces();
};




