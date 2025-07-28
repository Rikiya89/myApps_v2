#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    float laplace(const std::vector<std::vector<float>>& grid, int x, int y);
    void seed();

    int width, height;
    ofImage img;

    std::vector<std::vector<float>> a, b, nextA, nextB;

    float dA = 1.0f;
    float dB = 0.5f;
    float feed, kill;

    // GUI
    ofxPanel gui;
    ofParameter<float> feedParam;
    ofParameter<float> killParam;
    ofParameter<int> stepsPerFrameParam;
    ofxButton resetButton;

    void resetSimulation();
};
