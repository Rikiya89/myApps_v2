#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofImage image;
    vector<ofVec3f> points;
    vector<ofFloatColor> colors; // Store colors for each point
    vector<ofVec3f> flowerOfLife;
    ofEasyCam cam;
    ofLight light; // Declare light as a member variable

    float time; // Variable to store elapsed time for animation
};
