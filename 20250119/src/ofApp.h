#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    void drawSacredGeometry(float x, float y, float radius, int levels, float rotation);
    void drawBackground();

    float time;
    int numCircles;
    float radiusMultiplier;
    ofColor baseColor;
    ofColor secondaryColor;
};
