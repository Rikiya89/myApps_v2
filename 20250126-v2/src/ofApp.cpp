#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);         // Smooth animations
    ofBackground(0);            // Black background
    ofSetCircleResolution(100); // High-res circles
    ofSetLineWidth(1.5);        // Elegant, thin lines

    numPoints = 200; // Increase number of points for richer visuals

    // Initialize random points
    for (int i = 0; i < numPoints; ++i) {
        points.push_back(ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
    }

    waveOffset = 0.0;
    rotationAngle = 0.0;
}

void ofApp::update() {
    // Update wave offset and rotation angle for animations
    waveOffset += 0.05;
    rotationAngle += 0.3;

    // Slightly move points for dynamic patterns
    for (auto &point : points) {
        point.x += ofRandom(-0.5, 0.5);
        point.y += ofRandom(-0.5, 0.5);

        // Wrap points around screen edges
        if (point.x < 0) point.x += ofGetWidth();
        if (point.x > ofGetWidth()) point.x -= ofGetWidth();
        if (point.y < 0) point.y += ofGetHeight();
        if (point.y > ofGetHeight()) point.y -= ofGetHeight();
    }
}

void ofApp::draw() {
    float time = ofGetElapsedTimef();

    // **Layer 1: Flowing Network of Lines**
    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            float distance = ofDist(points[i].x, points[i].y, points[j].x, points[j].y);
            if (distance < 120) { // Draw only nearby connections
                ofSetColor(255, ofMap(distance, 0, 120, 255, 50)); // Gradient fade
                ofDrawLine(points[i], points[j]);
            }
        }
    }

    // **Layer 2: Pulsating Circles**
    for (auto &point : points) {
        float radius = 3 + 2 * sin(time * 2.0 + point.x * 0.01); // Pulsate radius
        ofSetColor(255, 120); // Semi-transparent white
        ofDrawCircle(point, radius);
    }

    // **Layer 3: Dynamic Wave of Circles**
    for (int i = 0; i < ofGetWidth(); i += 15) {
        float y = ofGetHeight() / 2 + 120 * sin((i * 0.02) + waveOffset); // Wave formula
        ofSetColor(255, ofMap(sin(i * 0.1 + waveOffset), -1, 1, 50, 200)); // Soft gradient
        ofDrawCircle(i, y, 8); // Draw circles
    }

    // **Layer 4: Rotating Star-Like Shape**
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(rotationAngle); // Continuous rotation
    for (int i = 0; i < 8; ++i) {
        ofRotateDeg(45); // Rotate by 45 degrees for each arm
        ofSetColor(255, 100); // Transparent white
        ofNoFill();
        ofDrawLine(0, 0, 300, 300); // Draw lines from center outward
        ofDrawCircle(300, 300, 20); // Add small circles at the ends
    }
    ofPopMatrix();

    // **Layer 5: Concentric Noise Rings**
    for (int i = 1; i <= 5; ++i) {
        ofSetColor(255, ofMap(i, 1, 5, 50, 150)); // Gradient transparency
        float radius = 100 + i * 30 + 10 * sin(time * 1.5 + i); // Animate size
        ofNoFill();
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radius);
    }
}
