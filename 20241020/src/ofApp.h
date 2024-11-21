#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        ofEasyCam cam;                   // Camera for the 3D scene
        ofLight pointLight, pointLight2; // Two dynamic lights
        ofMaterial material;             // Material for reflection and shininess
        ofMesh mesh;                     // Dynamic mesh
        ofSpherePrimitive sphere;        // Center sphere
        vector<ofVec3f> particles;       // Particle system
        vector<ofVec3f> particleSpeeds;  // Speed vectors for the particles
        int numParticles = 500;          // Number of particles
        float timeSpeed = 0.05;          // Slower time speed for smoother effects
};
