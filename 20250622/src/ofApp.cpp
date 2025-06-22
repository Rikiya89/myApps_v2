#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("Sacred Breathing Field");
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(120);
    ofSetLineWidth(1.0);

    spacing = 70;
    int radius = 7;

    // Hexagonal (flower of life style) grid
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            float px = spacing * (x + y * 0.5);
            float py = spacing * y * sqrt(3) / 2;
            points.push_back(glm::vec2(px, py));
        }
    }

    time = 0;
}

void ofApp::update() {
    time += 0.025;
}

void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    for (auto& p : points) {
        ofPushMatrix();
        ofTranslate(p);

        float d = glm::length(p);
        float offset = sin(time - d * 0.02);
        float radius = ofMap(offset, -1, 1, 10, 45);
        float alpha = ofMap(offset, -1, 1, 30, 180);

        ofSetColor(255, alpha);
        ofNoFill();

        // Concentric shimmer
        for (int i = 0; i < 4; i++) {
            float r = radius + i * 8 + sin(time * 0.5 + i) * 3;
            ofDrawCircle(0, 0, r);
        }

        ofPopMatrix();
    }

    ofPopMatrix();
}
