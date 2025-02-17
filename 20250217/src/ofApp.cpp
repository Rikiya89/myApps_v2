#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);
    animationTime = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    animationTime += 0.03; // **Faster Expansion Rate**

    float time = ofGetElapsedTimef();

    // **More Frequent Particle Spawning**
    for (int i = 0; i < 8; i++) {  // **Now spawns 8 particles per frame!**
        float goldenAngle = ofRandom(0, TWO_PI);
        float radius = ofRandom(100, 500) + sin(animationTime) * 50;
        float x = ofGetWidth() / 2 + cos(goldenAngle) * radius;
        float y = ofGetHeight() / 2 + sin(goldenAngle) * radius;
        particles.push_back(Particle(x, y));
    }

    // **Update Particles with More Motion**
    for (auto &p : particles) {
        float noiseFactor = ofNoise(p.position.x * 0.002, p.position.y * 0.002, time * 0.1);
        p.update(noiseFactor, time);
    }

    // **Faster Fading of Particles**
    particles.erase(remove_if(particles.begin(), particles.end(), [](Particle &p) {
        return p.alpha <= 50;
    }), particles.end());
}

//--------------------------------------------------------------
void ofApp::draw() {
    // **Soft Glowing Effect**
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto &p : particles) {
        p.draw();
    }
    ofDisableBlendMode();

    // ✨ **Faster Expanding Fractals**
    drawFractalCircle(ofGetWidth() / 2, ofGetHeight() / 2, 220 + sin(animationTime * 0.8) * 60, 5, animationTime);
}

//--------------------------------------------------------------
// 🎇 **Recursive Fractal Function (Now Faster & More Dynamic)**
void drawFractalCircle(float x, float y, float radius, int depth, float time) {
    if (depth <= 0) return;

    float oscillation = sin(time * 1.5 + depth) * 15;
    float dynamicRadius = radius + oscillation;

    ofSetColor(255, 170 + sin(time * 3) * 80);
    ofNoFill();
    ofDrawCircle(x, y, dynamicRadius);

    // **Faster Rotating Fractal Expansion**
    float angleStep = TWO_PI / 6;
    for (int i = 0; i < 6; i++) {
        float angle = i * angleStep + sin(time * 0.8) * 0.5;
        float newX = x + cos(angle) * dynamicRadius * 0.65;
        float newY = y + sin(angle) * dynamicRadius * 0.65;
        drawFractalCircle(newX, newY, dynamicRadius * 0.5, depth - 1, time);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'r') {
        animationTime = 0; // Reset animation
    }
}
