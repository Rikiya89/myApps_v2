#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);  // Set the background color to black
    ofSetCircleResolution(100);  // Higher resolution for smoother circles

    rotationAngle = 0;  // Initialize rotation angle
    scaleFactor = 1.0;  // Initialize scale factor
    pulse = 0;  // Initialize pulse effect
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += 0.5;  // Increment rotation angle
    if (rotationAngle >= 360) {
        rotationAngle = 0;  // Reset angle after a full rotation
    }

    // Oscillate the scale factor between 0.5 and 1.5
    scaleFactor = 1.0 + 0.5 * sin(ofGetElapsedTimef() * 2);

    // Pulse effect for glow
    pulse = ofMap(sin(ofGetElapsedTimef() * 2), -1, 1, 0.5, 1.5);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw gradient background
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addVertex(ofPoint(0, 0));
    mesh.addColor(ofColor(10, 10, 50));
    mesh.addVertex(ofPoint(ofGetWidth(), 0));
    mesh.addColor(ofColor(0, 0, 0));
    mesh.addVertex(ofPoint(0, ofGetHeight()));
    mesh.addColor(ofColor(0, 0, 0));
    mesh.addVertex(ofPoint(ofGetWidth(), ofGetHeight()));
    mesh.addColor(ofColor(10, 10, 50));
    mesh.draw();

    // Additional gradient layer
    ofMesh mesh2;
    mesh2.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh2.addVertex(ofPoint(0, 0));
    mesh2.addColor(ofColor(30, 30, 80, 100));
    mesh2.addVertex(ofPoint(ofGetWidth(), 0));
    mesh2.addColor(ofColor(10, 10, 50, 50));
    mesh2.addVertex(ofPoint(0, ofGetHeight()));
    mesh2.addColor(ofColor(10, 10, 50, 50));
    mesh2.addVertex(ofPoint(ofGetWidth(), ofGetHeight()));
    mesh2.addColor(ofColor(30, 30, 80, 100));
    mesh2.draw();

    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;
    float radius = 50;  // Radius of the circles

    ofPushMatrix();
    ofTranslate(centerX, centerY);
    ofRotateDeg(rotationAngle);  // Apply rotation
    ofScale(scaleFactor, scaleFactor);  // Apply scaling
    drawFlowerOfLife(0, 0, radius, 4);  // Adjust depth as needed
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFlowerOfLife(float x, float y, float radius, int depth) {
    if(depth == 0) return;

    float time = ofGetElapsedTimef();
    ofSetColor(getColor(depth, time));  // Get color based on depth and time
    ofNoFill();
    ofSetLineWidth(2);  // Set the line width for the circles

    // Glow effect
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(getColor(depth, time));  // Use the same color with additive blend mode for glow effect
    ofDrawCircle(x, y, radius * pulse);  // Draw a slightly larger circle for the glow with pulse effect
    ofDisableBlendMode();

    ofDrawCircle(x, y, radius);  // Draw the center circle

    float nextRadius = radius * sin(PI / 3);  // Calculate the radius for the next layer

    // Draw six surrounding circles
    for(int i = 0; i < 6; ++i) {
        float angle = PI / 3 * i;
        float newX = x + nextRadius * cos(angle);
        float newY = y + nextRadius * sin(angle);

        drawFlowerOfLife(newX, newY, radius, depth - 1);  // Recursive call
    }
}

//--------------------------------------------------------------
ofColor ofApp::getColor(int depth, float time) {
    // Generate a color based on depth and time for dynamic effect using Perlin noise
    float hue = ofMap(ofNoise(depth * 0.1, time * 0.1), 0, 1, 0, 255);  // Map Perlin noise to hue range
    return ofColor::fromHsb(hue, 255, 255);  // Return an HSB color with dynamic hue
}
