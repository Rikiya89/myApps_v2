#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;
    ofVboMesh mesh;

    int radialSteps;
    int circleSteps;
    float radius;
    float time;
};
