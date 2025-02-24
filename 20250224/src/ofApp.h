// ofApp.h
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void drawPattern(float x, float y, float radius, int depth);

private:
    float time = 0;
};
