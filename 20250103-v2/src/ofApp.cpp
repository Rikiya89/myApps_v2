#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("Spiritual Generative Art");
    ofSetWindowShape(1200, 1200);
    ofSetBackgroundColor(0); // Black background
    ofSetFrameRate(60);

    numLines = 500; // Number of radial beams
    time = 0.0f;    // Initialize animation time
}

//--------------------------------------------------------------
void ofApp::update() {
    time += 0.015; // Increment time for smooth animation
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Center the drawing

    // Mandala layers
    for (int layer = 1; layer <= 8; layer++) {
        float mandalaRadius = 50 + layer * 40 + 20 * sin(time + layer * 0.5);
        ofSetColor(255, 100 - layer * 10); // Fading brightness for outer layers
        ofSetLineWidth(2);
        ofNoFill();
        for (int i = 0; i < 12; i++) { // 12 segments per layer
            float angle1 = ofMap(i, 0, 12, 0, TWO_PI);
            float angle2 = ofMap(i + 1, 0, 12, 0, TWO_PI);
            float x1 = mandalaRadius * cos(angle1);
            float y1 = mandalaRadius * sin(angle1);
            float x2 = mandalaRadius * cos(angle2);
            float y2 = mandalaRadius * sin(angle2);
            ofDrawLine(x1, y1, x2, y2); // Connect mandala segments
        }
    }

    // Radiating beams
    for (int i = 0; i < numLines; i++) {
        float angle = ofMap(i, 0, numLines, 0, TWO_PI);
        float radius = 200 + 50 * sin(time + i * 0.03);
        float waveRadius = radius + 20 * sin(time * 2 + i * 0.1);

        float x1 = waveRadius * cos(angle);
        float y1 = waveRadius * sin(angle);
        float x2 = (waveRadius + 50) * cos(angle + 0.05);
        float y2 = (waveRadius + 50) * sin(angle + 0.05);

        float lineWidth = ofMap(sin(time + i * 0.05), -1, 1, 1, 3);
        float alpha = ofMap(cos(time + i * 0.1), -1, 1, 50, 200);

        ofSetColor(255, alpha);
        ofSetLineWidth(lineWidth);
        ofDrawLine(x1, y1, x2, y2);
    }

    // Orbital particles
    for (int p = 0; p < 150; p++) {
        float angle = time * 0.3 + p * TWO_PI / 150; // Orbital motion
        float orbitalRadius = 100 + 50 * sin(time + p * 0.05);
        float x = orbitalRadius * cos(angle);
        float y = orbitalRadius * sin(angle);

        ofSetColor(255, 100); // Faint particles
        ofDrawCircle(x, y, 3); // Small particle size
    }

    // Starburst patterns
    int numDots = 300;
    for (int d = 0; d < numDots; d++) {
        float angle = ofMap(d, 0, numDots, 0, TWO_PI);
        float starRadius = 400 + 30 * sin(time + d * 0.05);
        float x = starRadius * cos(angle);
        float y = starRadius * sin(angle);

        ofSetColor(255, 50);
        ofDrawCircle(x, y, 1.5);
    }

    // Central radiant glow
    ofSetColor(255, 150 + 50 * sin(time * 3)); // Pulsating glow
    ofDrawCircle(0, 0, 50 + 10 * sin(time * 2)); // Larger, dynamic glow
}
