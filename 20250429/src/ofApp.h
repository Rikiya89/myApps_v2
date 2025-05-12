#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawSacredGeometry(float radius, int layers, float breathing);
    void drawBackgroundStars();

    ofEasyCam cam;
    vector<ofVec3f> spherePositions; // store sphere positions
    vector<ofColor> colors;           // color palette
};
