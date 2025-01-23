#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);  // Black background
    ofSetFrameRate(60);  // Smooth animation at 60 FPS
    ofEnableAlphaBlending();  // Enable transparency for layered effects
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic (if any) goes here
}

//--------------------------------------------------------------
void ofApp::draw() {
    float time = ofGetElapsedTimef();  // Elapsed time
    int numLayers = 5;  // Number of circular layers
    int numLines = 300;  // Number of lines per layer
    float maxRadius = ofGetHeight() * 0.5;  // Maximum radius

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);  // Center the artwork

    for (int layer = 0; layer < numLayers; layer++) {
        float layerRadius = ofMap(layer, 0, numLayers, maxRadius * 0.1, maxRadius);
        float opacity = ofMap(layer, 0, numLayers, 255, 50);  // Gradual fade-out

        for (int i = 0; i < numLines; i++) {
            float angle = ofMap(i, 0, numLines, 0, TWO_PI);  // Spread lines evenly
            float x1 = cos(angle + time * (0.5 + layer * 0.1)) * layerRadius;
            float y1 = sin(angle + time * (0.5 + layer * 0.1)) * layerRadius;
            float x2 = cos(angle - time * (0.5 + layer * 0.1)) * layerRadius * 0.8;
            float y2 = sin(angle - time * (0.5 + layer * 0.1)) * layerRadius * 0.8;

            ofSetColor(255, opacity);  // White lines with opacity
            ofSetLineWidth(1.5);  // Slightly thicker lines for clarity
            ofDrawLine(x1, y1, x2, y2);  // Draw the line
        }
    }

    // Add subtle pulsating circles in the background
    for (int i = 0; i < 10; i++) {
        float radius = maxRadius * 0.1 + i * 10 + sin(time * 2 + i) * 5;
        ofSetColor(255, ofMap(i, 0, 10, 20, 100));  // Fainter circles in the background
        ofNoFill();
        ofSetLineWidth(0.5);
        ofDrawCircle(0, 0, radius);
    }
}
