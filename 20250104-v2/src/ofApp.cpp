#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);  // Set background color to black
    ofSetFrameRate(60);  // Smooth animation at 60 FPS
    ofEnableAlphaBlending();  // Enable transparency blending
}

//--------------------------------------------------------------
void ofApp::update() {
    // Nothing to update in this version
}

//--------------------------------------------------------------
void ofApp::draw() {
    float time = ofGetElapsedTimef();  // Time variable
    int numLayers = 8;  // Number of radiating layers
    int numLines = 400;  // Number of lines per layer
    float maxRadius = ofGetHeight() * 0.5;  // Maximum radius

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);  // Center the artwork

    for (int layer = 0; layer < numLayers; layer++) {
        float layerRadius = ofMap(layer, 0, numLayers, maxRadius * 0.1, maxRadius);
        float rotationSpeed = ofMap(layer, 0, numLayers, 0.5, 2.0);  // Layers rotate at different speeds
        float opacity = ofMap(layer, 0, numLayers, 255, 50);  // Gradual fade for outer layers

        ofPushMatrix();
        ofRotateDeg(sin(time * rotationSpeed + layer) * 20);  // Dynamic rotation

        for (int i = 0; i < numLines; i++) {
            float angle = ofMap(i, 0, numLines, 0, TWO_PI);  // Spread lines evenly
            float noise = ofNoise(i * noiseFactor, layer * noiseFactor, time * 0.3) * 100;  // Perlin noise
            float x1 = cos(angle + time * 0.1) * (layerRadius + noise);
            float y1 = sin(angle + time * 0.1) * (layerRadius + noise);
            float x2 = cos(angle - time * 0.1) * (layerRadius * 0.8 + noise * 0.5);
            float y2 = sin(angle - time * 0.1) * (layerRadius * 0.8 + noise * 0.5);

            ofSetColor(255, opacity);  // White lines with varying opacity
            ofSetLineWidth(ofMap(layer, 0, numLayers, 0.5, 2));  // Thicker lines for inner layers
            ofDrawLine(x1, y1, x2, y2);  // Draw the line
        }

        ofPopMatrix();
    }

    // Add flowing particle-like circles for elegance
    for (int i = 0; i < 100; i++) {
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        float radius = maxRadius * 0.5 + sin(time + i * 0.1) * 50;
        float x = cos(angle + time * 0.2) * radius;
        float y = sin(angle + time * 0.2) * radius;

        ofSetColor(255, ofMap(i, 0, 100, 20, 100));  // Fainter circles
        ofDrawCircle(x, y, ofNoise(i * 0.1, time) * 3);  // Pulsating circles
    }
}
