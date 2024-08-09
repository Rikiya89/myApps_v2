// ofApp.h
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseMoved(int x, int y );

    ofMesh mesh;
    ofImage image;

    vector<ofVec3f> particles;  // Store particle positions
    vector<ofVec3f> velocities; // Store particle velocities

    float width, height;

    // Audio variables
    ofSoundPlayer music;
    vector<float> spectrum;
    int nBandsToGet;

    // Interaction variables
    ofVec3f mouseAttractor;
    ofVec3f previousMouse; // To create trails
};
