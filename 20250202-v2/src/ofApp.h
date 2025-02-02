#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    // A camera to navigate the 3D scene.
    ofEasyCam cam;

    // A collection of 3D boxes.
    vector<ofBoxPrimitive> boxes;
    int numBoxes = 100;

    // A random offset for the noise function.
    float timeOffset;
};
