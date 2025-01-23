#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    float noiseFactor = 0.02;  // Control noise variation
};
