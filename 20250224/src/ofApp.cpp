// ofApp.cpp
#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
}

void ofApp::update(){
    time += 0.02; // Increase speed for smoother animation
}

void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    drawPattern(0, 0, 200, 6);
}

void ofApp::drawPattern(float x, float y, float radius, int depth) {
    if (depth <= 0) return;

    float angleStep = TWO_PI / 6; // Hexagonal symmetry
    float hue = fmod(time * 50, 255); // Animated color shift

    ofSetColor(ofColor::fromHsb(hue, 200, 255, 200)); // Adjusted saturation
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(x, y, radius);

    for (int i = 0; i < 6; i++) {
        float angle = angleStep * i + time * 2; // Dynamic rotation
        float newX = x + cos(angle) * radius;
        float newY = y + sin(angle) * radius;

        ofSetColor(ofColor::fromHsb(fmod(hue + i * 30, 255), 200, 255, 150)); // Maintain color vibrancy
        ofDrawLine(x, y, newX, newY);

        ofPushMatrix();
        ofTranslate(newX, newY);
        ofRotateDeg(ofGetElapsedTimef() * 20); // Subtle rotation effect
        drawPattern(0, 0, radius * 0.5, depth - 1);
        ofPopMatrix();
    }
}
