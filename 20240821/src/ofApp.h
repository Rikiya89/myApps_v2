#pragma once

#include "ofMain.h"
#include "ofxFluid.h"
#include "ParticleSystem.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void mouseDragged(int x, int y, int button);
    void audioIn(ofSoundBuffer &input);

private:
    ofxFluid fluid;                       // Fluid simulation object
    ParticleSystem particleSystem;        // Particle system following the fluid flow
    ofSoundStream soundStream;            // Sound stream for audio input

    ofColor baseColor;          // Base color for the fluid forces
    float colorChangeSpeed;     // Speed at which the fluid color changes
    float time;                 // Internal time counter for color cycling
    float audioLevel;           // Audio input level

    void addDynamicForce(int x, int y);  // Adds a dynamic force to the fluid
    void addParticles(int x, int y);     // Adds particles at the specified location
};
