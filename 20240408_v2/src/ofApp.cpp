#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    int numCircles = 100;
    for(int i = 0; i < numCircles; i++) {
        positions.push_back(ofPoint(ofRandomWidth(), ofRandomHeight()));
        colors.push_back(ofColor::fromHsb(ofRandom(255), 255, 255, 100)); // Initialize with HSB color
        radii.push_back(ofRandom(10, 50));
        noiseOffsets.push_back(ofRandom(0, 1000));
    }

    movingPoint = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
    maxConnectionDistance = 200.0; // Increase for a wider range of interaction
    backgroundFade = 10; // More pronounced trail effect
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < positions.size(); i++) {
        positions[i].x += ofMap(ofNoise(noiseOffsets[i]), 0, 1, -1, 1);
        positions[i].y += ofMap(ofNoise(noiseOffsets[i] + 1000), 0, 1, -1, 1);
        noiseOffsets[i] += 0.01;

        // Change size based on the distance to the moving point
        float distance = positions[i].distance(movingPoint);
        radii[i] = ofMap(distance, 0, maxConnectionDistance, 50, 10, true);

        // Change color based on the distance to the moving point
        float hue = ofMap(distance, 0, maxConnectionDistance, 0, 255, true);
        colors[i].setHue(int(hue + ofGetElapsedTimef() * 10) % 255);
    }

    movingPoint.x = ofGetWidth() / 2 + 300 * sin(ofGetElapsedTimef() * 0.5);
    movingPoint.y = ofGetHeight() / 2 + 300 * cos(ofGetElapsedTimef() * 0.5);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, backgroundFade);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    for(int i = 0; i < positions.size(); i++) {
        ofSetColor(colors[i]);
        ofDrawCircle(positions[i], radii[i]);

        // Draw lines for a more connected and dynamic effect
        for(int j = 0; j < positions.size(); j++) {
            if (i != j && positions[i].distance(positions[j]) < maxConnectionDistance) {
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }
    ofDisableBlendMode();
}
