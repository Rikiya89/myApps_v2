#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);      // Black background
    ofSetLineWidth(1);    // Fine lines for a delicate look
    time = 0.0;

    // Create a grid of starting points
    int gridX = 30;
    int gridY = 30;
    float spacingX = ofGetWidth() / (gridX + 1);
    float spacingY = ofGetHeight() / (gridY + 1);

    for (int i = 1; i <= gridX; i++){
        for (int j = 1; j <= gridY; j++){
            float x = i * spacingX;
            float y = j * spacingY;
            startingPoints.push_back(ofVec2f(x, y));
        }
    }
}

void ofApp::update(){
    // Slowly increment time to animate the noise field
    time += 0.005;
}

void ofApp::draw(){
    // Draw white curves with a slight transparency for blending
    ofSetColor(255, 30);

    // For each starting point, trace a flowing path through the noise field
    for (auto &pt : startingPoints){
        ofVec2f current = pt;
        ofBeginShape();
        ofVertex(current.x, current.y);

        // Follow the noise field for a number of steps
        int steps = 100;
        for (int i = 0; i < steps; i++){
            // Compute a noise-based angle
            float noiseVal = ofNoise(current.x * 0.005, current.y * 0.005, time);
            float angle = noiseVal * TWO_PI * 4;  // Increase variation with a multiplier

            // Step length controls the smoothness of the curve
            float stepLength = 2;
            current.x += cos(angle) * stepLength;
            current.y += sin(angle) * stepLength;
            ofVertex(current.x, current.y);
        }
        ofEndShape();
    }
}
