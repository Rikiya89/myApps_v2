#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    int gridSizeX, gridSizeY;
    float spacing;

    vector<glm::vec3> points;
    vector<float> sizes;

    ofEasyCam cam;
};
