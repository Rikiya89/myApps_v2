#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60); // Set a smooth frame rate
    ofBackground(0); // Start with a black background
}

void ofApp::update(){
    // This method can be more complex in future iterations
}

void ofApp::draw(){
    float time = ofGetElapsedTimef(); // Get the current time for dynamic changes

    // Use Perlin noise to generate organic movement
    for (int i = 0; i < ofGetWidth(); i += 15) {
        for (int j = 0; j < ofGetHeight(); j += 15) {
            float noiseValue = ofNoise(i * 0.05, j * 0.05, time * 0.5);
            ofColor color;
            color.setHsb(noiseValue * 255, 255, 255); // Create a color based on the noise value
            ofSetColor(color);
            float radius = noiseValue * 10; // Dynamic radius based on noise
            ofDrawCircle(i, j, radius); // Draw circles with dynamic radius
        }
    }
}
