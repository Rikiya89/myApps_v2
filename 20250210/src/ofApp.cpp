#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowShape(1280, 960);
    ofBackground(0);
    ofEnableSmoothing();
    rotationAngle = 0;
    pulse = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += 0.1; // Smooth rotation
    pulse = sin(ofGetElapsedTimef() * 2) * 10; // Pulsating effect
}

//--------------------------------------------------------------
void ofApp::draw(){
    int numCircles = 220;
    float time = ofGetElapsedTimef();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(rotationAngle);

    for (int i = 0; i < numCircles; i++) {
        float angle = ofNoise(i * 0.02, time * 0.05) * TWO_PI * 6;
        float distance = ofNoise(i * 0.01, time * 0.1) * 350 + pulse;
        float x = cos(angle) * distance;
        float y = sin(angle) * distance;
        float radius = ofNoise(i * 0.02, time * 0.07) * 20 + pulse * 0.5;
        
        // Glow effect
        ofSetColor(255, 255, 255, 120);
        ofDrawCircle(x, y, radius + 5);
        ofSetColor(255, 255, 255, 200);
        ofDrawCircle(x, y, radius);
        
        // Sacred geometry fractal connections
        if (i % 5 == 0) {
            float x2 = cos(angle + PI / 3) * distance * 0.7;
            float y2 = sin(angle + PI / 3) * distance * 0.7;
            ofSetColor(255, 150);
            ofDrawLine(x, y, x2, y2);
        }
        
        // Additional connections forming star-like geometry
        if (i % 7 == 0) {
            float x3 = cos(angle - PI / 6) * distance * 0.5;
            float y3 = sin(angle - PI / 6) * distance * 0.5;
            ofSetColor(255, 100);
            ofDrawLine(x, y, x3, y3);
        }

        // Subtle hexagonal pattern
        if (i % 11 == 0) {
            float x4 = cos(angle + PI / 2) * distance * 0.4;
            float y4 = sin(angle + PI / 2) * distance * 0.4;
            ofSetColor(255, 80);
            ofDrawLine(x, y, x4, y4);
        }
    }
    
    ofPopMatrix();
}
