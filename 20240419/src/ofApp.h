#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void drawMetatronCube(float centerX, float centerY, float size);
    
    // Variables for animation and aesthetics
    float centerX;
    float centerY;
    float size;
    float rotation;    // Rotation angle for animation
    float pulse;       // Pulsating effect
    ofColor startColor;  // Start color for gradient
    ofColor endColor;    // End color for gradient
    ofFbo fbo;         // Framebuffer for motion blur effect
    float blurAmount;  // Amount of motion blur
};
