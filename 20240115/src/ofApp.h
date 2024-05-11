#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        // Shader for advanced effects
        ofShader shader;

        // Interactive elements
        float mouseX, mouseY;

        // Function for the pattern
        void drawFlowerOfLife(float x, float y, float radius, int layers);

        // Variables for the pattern
        float centerX;
        float centerY;
        float radius;
        int layers;
};
