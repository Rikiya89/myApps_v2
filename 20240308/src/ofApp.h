#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void drawFlowerOfLife(float x, float y, int layers, float radius, bool primary); // Updated declaration
    ofPoint getCircleCenter(float x, float y, float radius, int index, int total);
};
