#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void generateFractalPattern(); // Recursive fractal pattern generator
    void drawGlow(float x, float y, float size, ofColor color); // Glow effect
    void drawParticles(ofPoint p, float size); // Particle trail effect
    void drawRotatingStar(float x, float y, float size, ofColor color); // Dynamic rotating star

    vector<ofPoint> points; // Points for fractal shapes
    int numPoints; // Number of points
    int symmetry; // Radial symmetry divisions
    ofColor baseColor; // Base color for gradient animation
    vector<float> sizes; // Store dynamic sizes for each point
    float hueOffset; // Variable to control the color hue offset for smooth cycling
    bool isMousePressed; // Boolean variable to detect mouse press
    ofFbo trailFbo; // FBO for rendering motion blur/trail effect

    // Mouse interaction functions
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
};
