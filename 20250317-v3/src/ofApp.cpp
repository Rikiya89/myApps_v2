// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofBackground(0);
    ofSetFrameRate(60);
    
    numLayers = 5; // More complex depth
    numRings = 14; // More intricate circle patterns
    numConnections = 24; // More radial lines
    maxRadius = 350;
    rotation = 0;
    pulseSpeed = 0.5;
    waveAmplitude = 25;
    glowIntensity = 180;
}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 0.3; // Subtle rotation effect
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(rotation);
    
    float time = ofGetElapsedTimef();
    
    for (int layer = 0; layer < numLayers; layer++) {
        float layerOffset = sin(time * 0.3 + layer * 0.5) * 10;
        
        for (int i = 0; i < numRings; i++) {
            float radius = (maxRadius + layerOffset) * (i + 1) / numRings;
            float offset = sin(time * pulseSpeed + i * 0.3) * waveAmplitude;
            
            ofSetColor(255, glowIntensity - i * 8);
            ofNoFill();
            ofSetLineWidth(2);
            ofDrawCircle(0, 0, radius + offset);
            
            for (int j = 0; j < numConnections; j++) {
                float angle = ofDegToRad(j * (360.0 / numConnections));
                float x = cos(angle) * (radius + offset);
                float y = sin(angle) * (radius + offset);
                
                float waveOffset = sin(time * 1.5 + j * 0.5) * 15; // Stronger movement
                x += cos(angle) * waveOffset;
                y += sin(angle) * waveOffset;
                
                ofSetColor(255, 255 - j * 8);
                ofDrawLine(0, 0, x, y);
                ofDrawCircle(x, y, 5 + sin(time * 2 + j) * 3); // More dynamic pulsing
                
                // Create additional glowing effect
                for (int k = 1; k <= 4; k++) {
                    ofSetColor(255, (glowIntensity / k) - j * 5);
                    ofDrawCircle(x, y, (5 + sin(time * 2 + j) * 3) + k * 2);
                }
            }
        }
    }
}
