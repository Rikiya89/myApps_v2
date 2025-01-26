#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

private:
    std::vector<ofPoint> points; // Points for dynamic patterns
    int numPoints;               // Number of points

    float waveOffset;            // Offset for wave motion
    float rotationAngle;         // Angle for rotating patterns
};
