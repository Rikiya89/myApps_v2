#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0); // Set black background
    fluid.allocate(ofGetWidth(), ofGetHeight(), 0.5); // Allocate fluid buffer

    // Set fluid parameters
    fluid.dissipation = 0.99;    // Controls how fast the fluid dissipates
    fluid.velocityDissipation = 0.99;
    fluid.setGravity(ofVec2f(0, 0.00098)); // Apply slight downward gravity

    // Enable obstacles (edges will act as barriers)
    fluid.begin();
    ofSetColor(255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    fluid.end();
}

//--------------------------------------------------------------
void ofApp::update() {
    fluid.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    fluid.draw();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    ofVec2f mouse(x, y);
    ofVec2f force = mouse - oldMouse;  // Calculate movement force
    force *= 5.0;  // Scale force

    // Add force to the fluid
    fluid.addVelocity(mouse, force);
    fluid.addColor(mouse, ofFloatColor(0.1, 0.5, 1.0)); // Blue color effect

    oldMouse = mouse;
}
