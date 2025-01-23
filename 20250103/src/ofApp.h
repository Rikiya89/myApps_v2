#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;

    void mouseMoved(int x, int y) override;
    void mousePressed(int x, int y, int button) override;

private:
    struct Particle {
        ofVec2f position;
        ofVec2f velocity;
        ofColor startColor;
        ofColor endColor;
        float radius;
        float depth;
        float life; // Used for fading out
        int shapeType; // 0: Circle, 1: Triangle, 2: Star
    };

    vector<Particle> particles; // Store all particles
    float baseRadius;           // Base radius for size oscillation
    float timeOffset;           // Time offset for dynamic changes
    ofColor backgroundColor;    // Dynamic background color

    void drawShape(const Particle& particle); // Helper to draw different shapes
    ofVec2f getPerlinNoise(float x, float y); // Helper for organic movement
};
