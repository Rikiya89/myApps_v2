#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawStarMap();
    void generateStarMap();
    void updateComet();
    void drawComet();
    void drawNebula();
    void drawAurora();
    void drawGalaxyDust();

    ofEasyCam cam;
    ofSpherePrimitive sphere;
    vector<ofVec3f> stars;
    vector<pair<int, int>> starConnections;

    float rotationAngleX;
    float rotationAngleY;

    // Comet properties
    ofVec3f cometPosition;
    vector<ofVec3f> cometTrail;
    float cometAngle;

    // Nebula properties
    vector<ofVec3f> nebulaParticles;

    // Aurora properties
    vector<ofVec3f> auroraWaves;

    // Galaxy dust properties
    vector<ofVec3f> galaxyDustParticles;
};
