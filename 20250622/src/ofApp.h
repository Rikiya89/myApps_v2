#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    float time;
    std::vector<glm::vec2> points;
    float spacing;
};
