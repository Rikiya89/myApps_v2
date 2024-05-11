#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    // Include elapsedTime in the declarations
    void drawFibonacciSpirals(int x, int y, int n, float size, float goldenRatio, float elapsedTime);
    void drawStars(int centerX, int centerY, int radius, int numStars, int layers, float elapsedTime);
    void drawStar(float x, float y, int points, float innerRadius, float outerRadius);
};
