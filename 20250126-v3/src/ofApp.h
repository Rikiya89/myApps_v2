#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawPulsingBackground();
    void drawStars();
    void drawMandala();
    void drawRadiatingHalo();
    void drawComet();
    void drawAurora();

    vector<ofVec2f> stars;           // Star positions
    vector<ofVec2f> starVelocities; // Star velocities
    vector<float> starAngles;       // Angles for spiral star motion

    float cometAngle = 0;      // Angle for comet animation
    float mandalaRotation = 0; // Rotation for the mandala
    float auroraTime = 0;      // Time offset for aurora animation
};
