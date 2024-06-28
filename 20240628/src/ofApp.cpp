#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackgroundGradient(ofColor(255, 223, 186), ofColor(255, 255, 255), OF_GRADIENT_CIRCULAR);  // Set a circular gradient background
    ofSetCircleResolution(100);  // Higher resolution for circles
    ofEnableAlphaBlending();  // Enable transparency
    ofSetFrameRate(60);  // Set frame rate for smooth animation
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float radius = 50;  // Radius of each circle
    float spacing = radius * sqrt(3);  // Spacing between circles
    float time = ofGetElapsedTimef();  // Get elapsed time for animation

    drawFlowerOfLife(ofGetWidth() / 2, ofGetHeight() / 2, radius, spacing, time);
}

void ofApp::drawFlowerOfLife(float centerX, float centerY, float radius, float spacing, float time) {
    for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += spacing) {
        for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += spacing) {
            float distance = ofDist(0, 0, x, y);
            float colorValue = ofMap(distance, 0, ofGetWidth() / 2, 0, 255);
            float alphaValue = ofMap(distance, 0, ofGetWidth() / 2, 255, 50);
            float dynamicRadius = ofMap(distance, 0, ofGetWidth() / 2, radius, radius / 2) * (1 + 0.1 * sin(time + distance / 10));

            ofColor color = ofColor::fromHsb(colorValue, 255, 255, alphaValue);
            ofColor fillColor = ofColor::fromHsb(colorValue, 255, 255, alphaValue / 2);

            // Draw filled circle with gradient
            ofSetColor(fillColor);
            ofDrawCircle(centerX + x, centerY + y, dynamicRadius);
            ofDrawCircle(centerX + x + radius, centerY + y, dynamicRadius);
            ofDrawCircle(centerX + x + radius / 2, centerY + y + spacing / 2, dynamicRadius);

            // Draw circle outline with varying thickness
            ofSetColor(color);
            ofSetLineWidth(ofMap(distance, 0, ofGetWidth() / 2, 1, 3));
            ofNoFill();
            ofDrawCircle(centerX + x, centerY + y, dynamicRadius);
            ofDrawCircle(centerX + x + radius, centerY + y, dynamicRadius);
            ofDrawCircle(centerX + x + radius / 2, centerY + y + spacing / 2, dynamicRadius);
            ofFill();
        }
    }
}
