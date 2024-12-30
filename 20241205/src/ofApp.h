#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseMoved(int x, int y);

    int numLayers;       // Number of geometry layers
    float baseRadius;    // Base radius for shapes
    float rotationSpeed; // Speed of rotational animation
    float time;          // Time for animation
    ofColor primaryColor, secondaryColor; // Color gradients

    ofEasyCam cam;       // Camera for 3D view
    ofLight pointLight;  // Dynamic point light
    ofVboMesh particleMesh; // Mesh for particles
    vector<glm::vec3> particlePositions; // Particle positions
    vector<float> particleSpeeds;        // Speeds of particles

    ofSoundPlayer soundPlayer; // Audio player
    float *fftSmoothed;        // FFT analysis data
    int nBandsToGet;           // Number of frequency bands

    void drawRecursiveLayer(float x, float y, float z, float size, int depth);
};
