#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Parameters for dynamic sacred geometry
    float rotationSpeed;   // Speed of overall rotation
    int numRings;          // Number of rings in the Flower of Life
    int numPetals;         // Number of petals per ring
    float baseRadius;      // Base radius of the smallest circle
    ofEasyCam cam;         // Camera for interaction

    // Particles for ethereal beauty
    vector<glm::vec3> particles;
    vector<ofColor> particleColors;
    void drawParticles();

    // Utility for glow effect
    void drawGlowingCircle(float x, float y, float z, float size, ofColor color);
};
