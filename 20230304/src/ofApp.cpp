#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(120);
    circleCount = 1000; // Increase for more complexity

    for (int i = 0; i < circleCount; i++) {
        circlePositions.push_back(glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
        circleSizes.push_back(ofRandom(6, 30));
        circleColors.push_back(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 75)); // Add alpha for blending
        noiseOffsets.push_back(ofRandom(0, 1000));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    for (int i = 0; i < circleCount; i++) {
        // Update position using Perlin noise for smooth, organic movement
        float noiseX = ofNoise(noiseOffsets[i], time * 0.1);
        float noiseY = ofNoise(noiseOffsets[i] + 1000, time * 0.1); // Offset Y noise for independent x/y movement
        circlePositions[i].x = ofMap(noiseX, 0, 1, 0, ofGetWidth());
        circlePositions[i].y = ofMap(noiseY, 0, 1, 0, ofGetHeight());

        // Dynamic size changes
        circleSizes[i] = ofMap(sin(time + noiseOffsets[i]), -1, 1, 10, 50);

        // Color transitions
        circleColors[i].setHue(int(180 + 180 * sin(noiseOffsets[i] + time * 0.3)) % 255);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Enable blending for more dynamic visuals

    for (int i = 0; i < circleCount; i++) {
        ofSetColor(circleColors[i]);
        ofDrawCircle(circlePositions[i], circleSizes[i]);
    }

    ofDisableBlendMode();
}
