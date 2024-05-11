#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0); // Set the background to black
    ofSetCircleResolution(50); // Good balance between smoothness and performance
    ofSetFrameRate(60); // Set the frame rate to 60 fps for a smooth animation
}

void ofApp::update(){
    // Update logic can go here
}

void ofApp::draw(){
    float time = ofGetElapsedTimef(); // Get the elapsed time for dynamic effects

    // Create a pulsating background aura with a subtle gradient
    for (int k = 0; k < 100; k++) {
        float alpha = 100 * ofNoise(k, time * 0.1) * ofMap(k, 0, 100, 1, 0);
        ofSetColor(255, 255, 255, alpha);
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, k * 3);
    }

    // Reduced number of layers for better performance
    int numLayers = 5;
    for (int j = 0; j < numLayers; j++) {
        float layerFactor = float(j + 1) / numLayers;
        float rotation = time * 5 * layerFactor; // Slower rotation for a more relaxed effect
        float scale = 1 + 0.05 * sin(time * 0.5 * layerFactor); // Subtle scaling effect

        ofPushMatrix(); // Save the current coordinate system
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotateDeg(rotation);
        ofScale(scale, scale);

        // Reduced number of circles for each layer to lighten the load
        for (int i = 0; i < 6; i++) {
            float size = 50 + (40 * i) + 10 * sin(time * 0.2 * layerFactor + i); // Dynamic size change
            float alpha = ofMap(i, 0, 5, 255, 50) * (1 - layerFactor); // Adjust alpha based on layer
            ofColor color = ofColor::fromHsb(fmod((time * 20 * layerFactor + i * 45), 255), 255, 255, alpha);
            ofSetColor(color);
            drawFlowerOfLife(0, 0, size, 3); // Reduced recursion for performance
        }
        
        ofPopMatrix(); // Restore the original coordinate system
    }
}

void ofApp::drawFlowerOfLife(float x, float y, float size, int levels){
    if (levels <= 0) return;

    ofDrawCircle(x, y, size); // Draw the central circle

    float angleStep = TWO_PI / 6; // Six circles around the central one
    for (int i = 0; i < 6; i++) {
        float nx = x + cos(angleStep * i) * size;
        float ny = y + sin(angleStep * i) * size;
        ofDrawCircle(nx, ny, size);
        if (levels > 1) {
            drawFlowerOfLife(nx, ny, size / 2, levels - 1); // Adjust for less depth in recursion
        }
    }
}
