#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        int numWidth;
        int numHeight;
        float phase;
        float speed;
};
