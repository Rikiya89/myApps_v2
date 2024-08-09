#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawCirclePattern(float x, float y, float size);
    void drawSpiralPattern(float x, float y, float size);
    void drawIslamicPattern(float x, float y, float size);
    void drawGradientBackground();

    ofColor interpolateColor(float t);

    float animationOffset;  // Variable for animation effect
    float colorOffset;      // Variable for color transition
    int blurAmount;         // Blur strength

    ofVideoGrabber cam;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage blurredImg;  // Image to hold blurred result
    ofxCvGrayscaleImage prevGrayImg; // Previous frame for motion detection
    ofxCvGrayscaleImage diffImg;     // Difference image for motion

    ofVboMesh particles;    // Particle system
    int numParticles;
};
