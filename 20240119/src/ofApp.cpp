#include "ofApp.h"

void ofApp::setup(){
    // Initial setup for colors
    startColor = ofColor(255, 0, 0);
    endColor = ofColor(0, 255, 255);
    colorTransitionSpeed = 0.005;

    // Load your shader
    shader.load("bin/data/shader.frag");

    time = 0;
}

void ofApp::update(){
    // Update time and color
    time += 0.01;
    startColor = startColor.getLerped(endColor, colorTransitionSpeed);
    if(startColor == endColor){
        endColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
    }
}

void ofApp::draw(){
    ofBackground(0);
    shader.begin();
    shader.setUniform1f("u_time", time);

    // Draw a full-screen quad
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    shader.end();
}
