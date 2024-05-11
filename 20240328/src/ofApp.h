#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    // Variables for geometry and lines
    vector<ofPoint> points; // Stores the points of our geometry
    vector<ofPoint> speeds; // Speeds for dynamic movement
    int numberOfPoints; // Number of points to generate
    float connectionDistance; // Max distance to connect points with lines
};
