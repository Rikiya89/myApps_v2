#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Starting positions for our flow paths
    vector<ofVec2f> startingPoints;

    // Time variable to animate the noise field
    float time;
};
