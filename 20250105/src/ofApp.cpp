#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetBackgroundColor(0); // Black background for contrast
    ofSetFrameRate(60);      // Smooth animations
    timeElapsed = 0;         // Initialize time variable

    // Initialize particles
    for (int i = 0; i < 200; i++) {
        Particle p;
        p.position = ofPoint(ofRandomWidth(), ofRandomHeight());
        p.velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        p.size = ofRandom(2, 5);
        p.color = ofColor(255, 255, 255, ofRandom(50, 150)); // White particles with varying transparency
        particles.push_back(p);
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    timeElapsed += 0.01; // Increment time for animation updates

    // Update particle positions
    for (auto &p : particles) {
        p.position += p.velocity;
        if (p.position.x < 0 || p.position.x > ofGetWidth()) p.velocity.x *= -1;
        if (p.position.y < 0 || p.position.y > ofGetHeight()) p.velocity.y *= -1;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255); // White color for all shapes

    // **Layer 1: Rotating Flower of Life**
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Center the pattern
    int numCircles = 12;
    float baseRadius = 100 + sin(timeElapsed) * 20;
    for (int i = 0; i < 360; i += 30) {
        float angle = ofDegToRad(i);
        float x = cos(angle) * baseRadius;
        float y = sin(angle) * baseRadius;
        ofNoFill();
        ofSetColor(200); // Subtle gray for circles
        ofDrawCircle(x, y, baseRadius / 2); // Smaller glowing circles
    }
    ofDrawCircle(0, 0, baseRadius); // Central circle
    ofPopMatrix();

    // **Layer 2: Multi-Layered Mandalas**
    for (int layer = 0; layer < 3; layer++) {
        float radius = 150 + layer * 50 + sin(timeElapsed * (layer + 1)) * 30;
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotateDeg(timeElapsed * (layer + 1) * 30);
        ofSetColor(150 + layer * 25); // Gradual grayscale effect
        ofNoFill();
        ofSetLineWidth(1.5);
        ofDrawCircle(0, 0, radius);

        for (int j = 0; j < 360; j += 45) {
            float angle = ofDegToRad(j);
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            ofDrawLine(0, 0, x, y); // Radiating lines
            ofDrawCircle(x, y, 10); // Dots at line ends
        }
        ofPopMatrix();
    }

    // **Layer 3: Particle Trails**
    for (auto &p : particles) {
        ofSetColor(p.color);
        ofDrawCircle(p.position, p.size);
    }

    // **Layer 4: Rotating Halos**
    for (int i = 0; i < 4; i++) {
        float radius = 300 + i * 30 + cos(timeElapsed * 0.5) * 20;
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotateDeg(timeElapsed * (i + 1) * 20);
        ofSetColor(100 + i * 20, 100); // Semi-transparent gray halos
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawCircle(0, 0, radius);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}
