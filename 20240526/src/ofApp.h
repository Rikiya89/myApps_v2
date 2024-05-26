#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawStarMap();
    void generateStarMap();

    ofEasyCam cam;
    ofSpherePrimitive sphere;
    vector<ofVec3f> stars;
    vector<pair<int, int>> starConnections;

    float rotationAngleX;
    float rotationAngleY;
};
