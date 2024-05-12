#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void updateMesh(ofMesh& meshToUpdate, float time, float noiseScale, float displacementScale);

    // 3D camera and light
    ofEasyCam easyCam;
    ofLight light;

    // Meshes for drawing
    ofMesh mesh;
    ofMesh secondaryMesh;
    ofMesh tertiaryMesh; // Third layer of geometry

    // For rotating the geometry
    float rotationSpeed;
};
