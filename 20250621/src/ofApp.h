#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;

    ofEasyCam cam;
    std::vector<ofVec3f> points;
    float time;
};
