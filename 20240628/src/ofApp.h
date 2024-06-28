#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        void drawFlowerOfLife(float x, float y, float radius, float spacing, float time);
};
