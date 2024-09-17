#pragma once

#include "ofMain.h"

// Enhanced Particle Class Definition
class Particle {
public:
    // Constructor accepting position and color palette
    Particle(ofVec2f position, const std::vector<ofColor> &palette);

    // Update particle state
    void update(float time, ofVec2f attractor);

    // Draw the particle
    void draw();

    // Getter methods for private members
    float getAge() const { return age; }
    float getLifespan() const { return lifespan; }

private:
    ofVec2f pos;          // Current position of the particle
    ofVec2f velocity;     // Current velocity influenced by Perlin noise
    float size;           // Current size of the particle
    float initialSize;    // Initial size for reference
    ofColor color;        // Current color of the particle
    float hueOffset;      // Offset for color shifting
    float lifespan;       // Total lifespan of the particle
    float age;            // Current age of the particle
    float opacity;        // Current opacity based on age
    float layer;          // Layer depth for varying behaviors
};

// ofApp Class Definition
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    std::vector<Particle> particles; // Vector holding all active particles
    int maxParticles;                // Maximum number of unique particles for performance
    float resetProbability;          // Probability of resetting a particle each frame
    ofVec2f attractor;               // Central attractor point

    // Radial symmetry parameters
    int symmetryCount;               // Number of symmetry axes

    // Color palette
    std::vector<ofColor> colorPalette;

    // Attractor movement parameters
    float attractorSpeed;            // Speed of attractor rotation
    float attractorRadius;           // Radius of attractor's circular path
    float attractorAngle;            // Current angle for attractor movement
};
