// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofSetFrameRate(60);
    ofBackground(0);
    globalTimeOffset = ofRandom(0, TWO_PI); // Adds variety in animation start
    rotationSpeed = 0.02; // Base rotation speed
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update logic for smooth animation
    globalTimeOffset += rotationSpeed * 0.2;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255); // White elements on black background
    ofNoFill();

    int numCircles = 50;
    float maxRadius = 400;
    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;
    float time = ofGetElapsedTimef() + globalTimeOffset;
    
    // Draw sacred geometry-inspired nested circles with pulsing effect
    for (int i = 0; i < numCircles; i++) {
        float pulse = sin(time * 0.5 + i * 0.2) * 10;
        float radius = maxRadius * (i + 1) / numCircles + pulse;
        float weight = ofMap(sin(time * 0.3 + i * 0.4), -1, 1, 1, 4);
        ofSetLineWidth(weight);
        ofDrawCircle(centerX, centerY, radius);
    }
    
    // Draw radial lines forming a rotating mandala pattern with dynamic spiraling
    int numLines = 72;
    for (int i = 0; i < numLines; i++) {
        float angle = ofDegToRad(i * (360.0 / numLines)) + sin(time * 0.3) * 0.5;
        float variation = sin(time * 0.6 + i * 0.2) * 10;
        float x1 = centerX + cos(angle) * (maxRadius + variation);
        float y1 = centerY + sin(angle) * (maxRadius + variation);
        float x2 = centerX - cos(angle) * (maxRadius + variation);
        float y2 = centerY - sin(angle) * (maxRadius + variation);
        ofSetLineWidth(ofMap(sin(time * 0.2 + i * 0.3), -1, 1, 1, 3));
        ofDrawLine(x1, y1, x2, y2);
    }
    
    // Draw rotating and expanding Flower of Life pattern
    int numDots = 42;
    for (int i = 0; i < numDots; i++) {
        float angle = ofDegToRad(i * (360.0 / numDots) + time * 50);
        float radius = maxRadius * 0.5 + sin(time * 1.0 + i * 0.3) * 15;
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        float dotSize = ofMap(sin(time * 0.8 + i * 0.6), -1, 1, 2, 6);
        ofDrawCircle(x, y, dotSize);
    }
    
    // Draw expanding and contracting star-shaped energy waves with rotating effect
    int numStarLines = 18;
    float starRadius = maxRadius * 0.7 + sin(time * 0.5) * 25;
    for (int i = 0; i < numStarLines; i++) {
        float angle = ofDegToRad(i * (360.0 / numStarLines) + time * 15);
        float x1 = centerX + cos(angle) * starRadius;
        float y1 = centerY + sin(angle) * starRadius;
        float x2 = centerX - cos(angle) * starRadius;
        float y2 = centerY - sin(angle) * starRadius;
        ofSetLineWidth(1.5);
        ofDrawLine(x1, y1, x2, y2);
    }
    
    // Central glowing aura with smooth fading effect
    for (int i = 0; i < 5; i++) {
        float auraRadius = ofMap(sin(time * 0.6 + i * 0.4), -1, 1, 20, 40);
        ofSetColor(255, ofMap(sin(time * 0.5 + i * 0.3), -1, 1, 50, 150));
        ofDrawCircle(centerX, centerY, auraRadius);
    }
    
    // Rotating outer ring to create a mesmerizing motion effect
    int numOuterDots = 36;
    float outerRadius = maxRadius * 1.2 + sin(time * 0.4) * 20;
    for (int i = 0; i < numOuterDots; i++) {
        float angle = ofDegToRad(i * (360.0 / numOuterDots) - time * 30);
        float x = centerX + cos(angle) * outerRadius;
        float y = centerY + sin(angle) * outerRadius;
        ofDrawCircle(x, y, 3);
    }
    
    ofSetColor(255); // Reset color
}
