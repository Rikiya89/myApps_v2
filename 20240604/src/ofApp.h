#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofImage image;
    ofVboMesh mesh;
    vector<ofVec3f> originalVertices;
};
