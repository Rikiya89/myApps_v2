#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

private:
    std::vector<glm::vec2> points; // Store random points
    std::vector<glm::vec2> velocities; // Store point velocities
    float gradientShift; // Tracks gradient animation

    void drawAnimatedParticles();
    void drawConnectingLines();
    void drawBackgroundGradient();
};
