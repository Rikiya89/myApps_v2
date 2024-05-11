#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::white);
    radius = 90.0;  // Base radius
    numCircles = 6;  // Number of circles
}

//--------------------------------------------------------------
void ofApp::update(){
    // The radius will pulsate based on a sine wave, creating a breathing effect.
    float time = ofGetElapsedTimef();
    radius = 50 + 15 * sin(time * 0.6);
}

//--------------------------------------------------------------
void ofApp::draw(){
    float offsetX = ofGetWidth() / 2;
    float offsetY = ofGetHeight() / 2;

    // Rotate the entire canvas over time for a dynamic effect
    ofPushMatrix();
    ofTranslate(offsetX, offsetY);
    float rotation = ofGetElapsedTimef() * 10;  // Slow rotation over time
    ofRotateDeg(rotation);

    // Draw multiple layers of the Flower of Life pattern with varying radii and colors
    for (int i = 0; i < 12; i++) {
        float alpha = ofMap(i, 0, 9, 255, 10);  // Fade effect for depth
        float currentRadius = radius + i * 5 * sin(ofGetElapsedTimef() * 0.8 + i);  // Each layer has its own animation phase
        ofColor color = ofColor::fromHsb(abs(sin(ofGetElapsedTimef() * 0.1 + i * 0.1)) * 255, 200, 255, alpha);  // Dynamic color changes
        drawFlowerOfLife(0, 0, currentRadius, numCircles, color, 2 + i / 5.0);
    }

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFlowerOfLife(float x, float y, float radius, int numCircles, ofColor color, float lineWidth) {
    ofSetLineWidth(lineWidth);
    ofNoFill();

    for (int i = 0; i < numCircles; i++) {
        float angle = ofDegToRad(360.0 / numCircles * i);
        float newX = x + radius * cos(angle) * 2;
        float newY = y + radius * sin(angle) * 2;

        for (float r = radius; r > 0; r -= radius / 10) {
            float alpha = ofMap(r, 0, radius, 0, color.a);
            ofSetColor(color.r, color.g, color.b, alpha);
            ofDrawCircle(newX, newY, r);
        }
    }
}
