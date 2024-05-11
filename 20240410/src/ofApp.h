#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Enhanced function to draw a single flower of life pattern with additional styling parameters
    void drawFlowerOfLife(float x, float y, float radius, int numCircles, ofColor color, float lineWidth);

    float radius;  // Radius of the circles
    int numCircles;  // Number of circles to draw in the Flower of Life pattern
};
