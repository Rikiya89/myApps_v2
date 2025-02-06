// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowShape(1280, 960);
    ofBackground(0);

    cols = ofGetWidth() / 12;
    rows = ofGetHeight() / 12;
    scale = 0.015;
    timeOffset = 0;
    lineLength = 12;
    animationSpeed = 0.006;
    rotationFactor = 4.0; // Enhance rotation complexity
}

//--------------------------------------------------------------
void ofApp::update(){
    timeOffset += animationSpeed; // Smooth animation speed
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetLineWidth(2);

    for(int x = 0; x < cols; x++){
        for(int y = 0; y < rows; y++){
            float noiseVal = ofNoise(x * scale, y * scale, timeOffset);
            float angle = noiseVal * TWO_PI * rotationFactor; // Enhance rotation dynamics
            ofVec2f dir = ofVec2f(cos(angle), sin(angle));
            ofVec2f pos = ofVec2f(x * (ofGetWidth() / cols), y * (ofGetHeight() / rows));

            // Dynamic gradient effect based on position and time
            float gradient = ofMap(sin(timeOffset + x * 0.1 + y * 0.1), -1, 1, 100, 255);
            float alpha = ofMap(noiseVal, 0, 1, 50, 180);

            ofSetColor(gradient, gradient, gradient, alpha);
            ofDrawLine(pos, pos + dir * lineLength);

            // Add points for extra flair
            ofSetColor(gradient, alpha);
            ofDrawCircle(pos + dir * lineLength, 2);
        }
    }
}
