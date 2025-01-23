#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0); // Black background
    ofSetCircleResolution(100);

    // Initialize points and velocities
    for (int i = 0; i < numPoints; i++) {
        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        points.push_back(ofPoint(x, y));
        velocities.push_back(ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)));
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update particle positions and apply noise-based motion
    for (int i = 0; i < points.size(); i++) {
        float noiseX = ofNoise(points[i].x * noiseScale, points[i].y * noiseScale, ofGetElapsedTimef());
        float noiseY = ofNoise(points[i].y * noiseScale, points[i].x * noiseScale, ofGetElapsedTimef());

        velocities[i].x += ofMap(noiseX, 0, 1, -0.5, 0.5);
        velocities[i].y += ofMap(noiseY, 0, 1, -0.5, 0.5);

        // Add slight attraction to the mouse position
        ofPoint attraction = mousePos - points[i];
        float distance = attraction.length();
        if (distance < 200) {
            attraction.normalize();
            velocities[i] += attraction * ofMap(distance, 0, 200, 0.1, 0); // Stronger attraction when closer
        }

        points[i] += velocities[i];

        // Wrap-around boundaries
        if (points[i].x < 0) points[i].x = ofGetWidth();
        if (points[i].x > ofGetWidth()) points[i].x = 0;
        if (points[i].y < 0) points[i].y = ofGetHeight();
        if (points[i].y > ofGetHeight()) points[i].y = 0;

        // Dampen velocity slightly for smoother motion
        velocities[i] *= 0.98;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255, 20); // Semi-transparent white for trails
    ofFill();

    // Draw particle trails
    for (auto &p : points) {
        ofDrawCircle(p, 1.5);
    }

    // Draw connecting lines with gradients
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            float distance = points[i].distance(points[j]);
            if (distance < 150) {
                float alpha = ofMap(distance, 0, 150, 255, 0);
                ofSetColor(255, alpha); // Gradient fading effect
                ofSetLineWidth(ofMap(distance, 0, 150, 2, 0.5));
                ofDrawLine(points[i], points[j]);
            }
        }
    }

    // Highlight mouse attraction area
    ofSetColor(255, 50);
    ofNoFill();
    ofDrawCircle(mousePos, 200);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    mousePos.set(x, y); // Update mouse position for interaction
}
