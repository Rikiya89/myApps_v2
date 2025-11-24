#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // Color palette
    vector<ofColor> colors;

    // 3D elements
    ofEasyCam cam;
    vector<ofVec3f> particles;
    vector<ofVec3f> velocities;
    vector<ofColor> particleColors;
    vector<float> particleSizes;
    vector<float> particlePhases;

    // Particle trails
    vector<deque<ofVec3f>> particleTrails;
    int maxTrailLength;

    // Meshes for generative forms
    vector<ofMesh> flowingMeshes;
    vector<ofMesh> ribbonMeshes;
    vector<ofMesh> orbitalRings;

    // Visual effects
    ofLight pointLight;
    ofMaterial material;
    vector<ofVec3f> floatingOrbs;
    vector<ofColor> orbColors;
    vector<float> orbPhases;

    // Animation
    float time;
    float rotationAngle;
    float cameraRotation;

    // Parameters
    int numParticles;
    int numLayers;
    int numRibbons;
    int numOrbs;
    float noiseScale;
    float flowSpeed;
};
