#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowShape(720, 1080);
    ofBackground(0);  // Black background
    ofSetFrameRate(60);
    
    time = 0.0f; // Start animation time
    cam.setDistance(600); // Set initial camera distance
    
    // Generate initial 3D points
    for (int i = 0; i < 600; i++) {
        float x = ofRandom(-300, 300);
        float y = ofRandom(-500, 500);
        float z = ofRandom(-300, 300);
        points.push_back(ofVec3f(x, y, z));
    }
}

void ofApp::update() {
    time += 0.01; // Increment time for animation

    for (auto& p : points) {
        float noiseFactor = ofNoise(p.x * 0.005, p.y * 0.005, time) * 2.0 - 1.0;
        p.z += noiseFactor * 2.0;  // Apply noise-based displacement
        p.x += sin(time + p.y * 0.01) * 0.5;  // Wavy motion
        p.y += cos(time + p.x * 0.01) * 0.5;
    }
}

void ofApp::draw() {
    cam.begin();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Glow effect
    ofSetColor(255, 255, 255, 150);  // Semi-transparent white

    for (size_t i = 0; i < points.size(); i++) {
        ofDrawSphere(points[i], 2);  // Small glowing spheres

        // Draw lines connecting nearby points
        for (size_t j = i + 1; j < points.size(); j++) {
            float distance = points[i].distance(points[j]);
            if (distance < 50) {
                ofSetColor(255, 255, 255, ofMap(distance, 0, 50, 255, 0)); // Fade lines
                ofDrawLine(points[i], points[j]);
            }
        }
    }

    ofDisableBlendMode();
    cam.end();
}

void ofApp::keyPressed(int key) {
    if (key == 'r') {
        points.clear();
        setup(); // Reset scene
    }
}
