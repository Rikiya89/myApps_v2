#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    circleResolution = 100;
    ofSetCircleResolution(circleResolution);
    ofSetFrameRate(60); // Smooth rendering at 60 frames per second
}

void ofApp::update(){
    // Update baseHue for color changes
    baseHue += 0.05;
    if (baseHue > 255) {
        baseHue = 0;
    }

    // Update the animation phase
    animationPhase += 0.03;
}

void ofApp::draw(){
    float radius = 50.0; // Base radius for the circles
    int layers = 6;  // Increase for a more complex pattern
    float xOffset = ofGetWidth() / 2;
    float yOffset = ofGetHeight() / 2;

    // Apply a subtle rotation over time to the entire pattern
    float rotation = ofGetElapsedTimef() * 10;  // Slow rotation speed

    for (int layer = 0; layer <= layers; layer++) {
        for (int i = 0; i < 6 * layer; i++) {
            float angle = (TWO_PI / (6 * layer) * i) + ofDegToRad(rotation);
            float layerRadius = radius * layer * sqrt(3) + cos(animationPhase + layer * 0.5) * 10;
            float x = xOffset + cos(angle) * layerRadius;
            float y = yOffset + sin(angle) * layerRadius;

            ofColor circleColor;
            float hue = fmod(baseHue + 360 * (sin(ofGetElapsedTimef() * 0.2) + 1) / 2 + 255 * layer / (float)layers, 255);
            float brightness = 255 * (0.5 + 0.5 * sin(animationPhase + layer));
            circleColor.setHsb(hue, 180, brightness, 120 - layer * 15);  // Dynamic brightness and transparency
            ofSetColor(circleColor);

            float dynamicRadius = radius + sin(animationPhase + layer * 0.5) * 10;  // Animated radius for wave effect
            ofDrawCircle(x, y, dynamicRadius);
        }
    }
}
