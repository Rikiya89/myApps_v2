#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetLineWidth(2); // Set the line width

    numWaves = 5; // Total number of waves
    for(int i = 0; i < numWaves; i++) {
        phase.push_back(ofRandom(0, TWO_PI)); // Random starting phase
        amplitude.push_back(ofRandom(100, 200)); // Random amplitude
        frequency.push_back(ofRandom(0.01, 0.05)); // Random frequency

        // Generate a random color for each wave
        colors.push_back(ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < numWaves; i++) {
        phase[i] += 0.03; // Speed of the wave
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int j = 0; j < numWaves; j++) {
        ofSetColor(colors[j]); // Set color for each wave
        for(int i = 0; i < ofGetWidth(); i+=5){ // Closer lines
            float y = sin(i * frequency[j] + phase[j]) * amplitude[j] + ofGetHeight()/(numWaves+1) * (j+1);
            ofDrawLine(i, ofGetHeight()/(numWaves+1) * (j+1), i, y);
        }
    }
}
