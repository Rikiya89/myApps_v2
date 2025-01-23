#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetBackgroundColor(0); // Black background
    ofSetFrameRate(60);      // Smooth animation
    numShapes = 300;         // Number of shapes
    noiseFactor = 0.01;      // Noise factor for movement
    timeOffset = 0.0;        // Time offset for animation
}

//--------------------------------------------------------------
void ofApp::update() {
    timeOffset += 0.002; // Decrease increment for slower animation
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableAlphaBlending(); // Enable transparency
    ofSetLineWidth(1.5);     // Thicker lines for more detail

    for (int i = 0; i < numShapes; i++) {
        float radius = ofMap(i, 0, numShapes, 50, 400); // Map radius size
        float angle = ofNoise(i * noiseFactor, timeOffset) * TWO_PI; // Noise-based angle

        float x = ofGetWidth() / 2 + radius * cos(angle);
        float y = ofGetHeight() / 2 + radius * sin(angle);

        // Draw semi-transparent circles with dynamic size
        ofSetColor(255, ofMap(i, 0, numShapes, 50, 255)); // Gradual transparency
        ofDrawCircle(x, y, ofNoise(i * noiseFactor + timeOffset) * 20);
    }

    for (int i = 0; i < numShapes; i++) {
        float radius = ofMap(i, 0, numShapes, 50, 400);
        float angle = ofNoise(i * noiseFactor + 100, timeOffset) * TWO_PI;

        float x1 = ofGetWidth() / 2 + radius * cos(angle);
        float y1 = ofGetHeight() / 2 + radius * sin(angle);

        float x2 = ofGetWidth() / 2 + radius * cos(angle + PI / 4);
        float y2 = ofGetHeight() / 2 + radius * sin(angle + PI / 4);

        // Draw dynamic lines connecting points
        ofSetColor(255, ofMap(i, 0, numShapes, 50, 150)); // Fading lines
        ofDrawLine(x1, y1, x2, y2);
    }

    ofDisableAlphaBlending(); // Disable transparency
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'r') {
        noiseFactor = ofRandom(0.01, 0.05); // Randomize noise factor
    }
}
