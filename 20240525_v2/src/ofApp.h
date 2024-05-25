#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key); // Declare the keyPressed function

    ofImage birdImage;
    ofMesh mesh;
    int imgWidth, imgHeight;
    ofEasyCam cam;
    ofLight light; // Add a light source
    float time; // Time variable for animation
    float amplitude; // Amplitude for the wave
    float frequency; // Frequency for the wave
    float rotationAngle; // Angle for rotation
    float colorCycle; // Variable for color cycling
    float animationSpeed; // Variable to control the speed of the animation
};
