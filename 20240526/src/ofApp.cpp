#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(0, 0, 51); // Set background to dark blue (#000033)
    ofSetFrameRate(60);

    // Create the sphere
    sphere.setRadius(200);
    sphere.setResolution(20);

    // Generate star map
    generateStarMap();

    // Initialize rotation angles
    rotationAngleX = 0.0f;
    rotationAngleY = 0.0f;
}

void ofApp::update() {
    // Update rotation angles
    rotationAngleX += 0.1f;
    rotationAngleY += 0.15f;
}

void ofApp::draw() {
    cam.begin();

    // Apply rotations
    ofPushMatrix();
    ofRotateXDeg(rotationAngleX);
    ofRotateYDeg(rotationAngleY);

    // Draw the sphere
    sphere.drawWireframe();

    // Draw the star map
    drawStarMap();

    ofPopMatrix();

    cam.end();
}

void ofApp::generateStarMap() {
    int numStars = 100;

    for (int i = 0; i < numStars; ++i) {
        float theta = ofRandom(0, TWO_PI);
        float phi = ofRandom(0, PI);

        float x = sphere.getRadius() * sin(phi) * cos(theta);
        float y = sphere.getRadius() * sin(phi) * sin(theta);
        float z = sphere.getRadius() * cos(phi);

        stars.push_back(ofVec3f(x, y, z));
    }

    // Create random connections between stars
    for (int i = 0; i < numStars; ++i) {
        int numConnections = ofRandom(1, 4);
        for (int j = 0; j < numConnections; ++j) {
            int targetIndex = ofRandom(0, numStars);
            if (targetIndex != i) {
                starConnections.push_back(make_pair(i, targetIndex));
            }
        }
    }
}

void ofApp::drawStarMap() {
    // Set the color to #996515
    ofSetColor(153, 101, 21);

    // Draw stars with glow effect
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (const auto& star : stars) {
        ofSetColor(153, 101, 21, 128); // Semi-transparent for glow
        ofDrawSphere(star, 4); // Larger radius for glow
        ofSetColor(255, 223, 0); // Bright yellow for core
        ofDrawSphere(star, 2); // Original radius
    }
    ofDisableBlendMode();

    // Draw connections with smoother lines
    ofSetLineWidth(2.0);
    ofSetColor(153, 101, 21);
    for (const auto& connection : starConnections) {
        ofDrawLine(stars[connection.first], stars[connection.second]);
    }
    ofSetLineWidth(1.0);
}
