#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
        
        void drawFlowerOfLife(float x, float y, float radius, int generations, float alpha);
        void drawBackground();
        void drawVignette();  // Declaration for the vignette drawing function

        float initialRadius;
        int generations;
        ofColor baseColor;
        float animationPhase;
        float rotationSpeed;
        float scale;
};
