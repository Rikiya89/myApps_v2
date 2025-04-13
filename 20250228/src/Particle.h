#pragma once
#include "ofMain.h"

class Particle {
public:
    Particle();
    Particle(glm::vec2 pos, ofColor col);
    
    void update();
    void draw();
    bool isDead();

    glm::vec2 position;
    glm::vec2 velocity;
    float lifespan;  // Remaining life (used for fading)
    ofColor color;

    // Dynamic properties for rotation and scaling
    float rotation;         // Current rotation angle (in degrees)
    float angularVelocity;  // Angular velocity (degrees per frame)
    float scale;            // Scale factor for the petal

    // Bloom effect: a value from 0 to 1 representing how fully the petal has bloomed
    float bloom;
    
    // Spiritual aura intensity for a glowing halo effect
    float auraIntensity;
};
