#pragma once

#include "ofMain.h"
#include "ofSoundPlayer.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofEasyCam cam;
    ofMesh torusMesh;
    ofMesh sacredGeometryMesh;
    vector<glm::vec3> particles;

    ofShader glowShader;
    ofSoundPlayer cosmicSound;
    float soundLevel;
    
    int numRings = 60;
    int numSides = 120;
    float baseRadiusMajor = 200;
    float baseRadiusMinor = 60;
    float radiusMajor;
    float radiusMinor;
    float noiseFactor = 0.1;
    float timeOffset = 0.0;
    float rotationSpeed = 0.02;

    void generateTorus();
    void generateSacredGeometry();
    void generateParticles();
};
