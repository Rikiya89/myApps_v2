#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    int numLines;          // Number of lines in the artwork
    float time;            // Animation time variable
};
