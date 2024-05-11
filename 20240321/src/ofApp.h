#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        void drawSeedOfLife(float x, float y, float size, int levels, float phase);
        void drawBackgroundGradient(ofColor innerColor, ofColor outerColor);

        float animationPhase;
};
