#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0); // Start with black background
    ofSetFrameRate(60); // Smooth animations
    ofSetCircleResolution(100);

    // Initialize random points and velocities
    int numPoints = 150;
    for (int i = 0; i < numPoints; i++) {
        points.push_back(glm::vec2(ofRandomWidth(), ofRandomHeight()));
        velocities.push_back(glm::vec2(ofRandom(-2, 2), ofRandom(-2, 2)));
    }

    gradientShift = 0.0f; // Initialize gradient shift
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update particle positions
    for (size_t i = 0; i < points.size(); i++) {
        points[i] += velocities[i];

        // Bounce off walls
        if (points[i].x < 0 || points[i].x > ofGetWidth()) {
            velocities[i].x *= -1;
        }
        if (points[i].y < 0 || points[i].y > ofGetHeight()) {
            velocities[i].y *= -1;
        }
    }

    // Animate gradient shift
    gradientShift += 0.5;
    if (gradientShift > 360.0f) {
        gradientShift = 0.0f; // Loop the shift
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    drawBackgroundGradient();
    drawAnimatedParticles();
    drawConnectingLines();
}

//--------------------------------------------------------------
void ofApp::drawBackgroundGradient() {
    for (int y = 0; y < ofGetHeight(); y++) {
        float brightness = ofMap(sin(ofDegToRad(gradientShift + y * 0.1)), -1, 1, 20, 50);
        ofSetColor(brightness);
        ofDrawLine(0, y, ofGetWidth(), y);
    }
}

//--------------------------------------------------------------
void ofApp::drawAnimatedParticles() {
    for (size_t i = 0; i < points.size(); i++) {
        if (i % 3 == 0) {
            ofSetColor(255, 200); // Semi-transparent white
            ofFill();
        } else {
            ofSetColor(255);
            ofNoFill();
        }
        ofDrawCircle(points[i].x, points[i].y, ofRandom(6, 15));
    }
}

//--------------------------------------------------------------
void ofApp::drawConnectingLines() {
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            float dist = glm::distance(points[i], points[j]);
            if (dist < 100) { // Connect only nearby points
                ofSetColor(255, ofMap(dist, 0, 100, 150, 50)); // Fade lines based on distance
                ofSetLineWidth(1);
                ofDrawLine(points[i].x, points[i].y, points[j].x, points[j].y);
            }
        }
    }
}
