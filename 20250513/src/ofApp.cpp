#include "ofApp.h"

// ------------------- Particle -------------------
void Particle::setup(float i, float total) {
    float phi = (sqrt(5.0) + 1.0) / 2.0;  // Golden ratio
    angleOffset = i * TWO_PI / phi;
    baseRadius = ofMap(i, 0, total, 50, 320);  // fits 1080 height
    frequency = ofMap(i, 0, total, 0.2, 1.0);
}

void Particle::update(float time, float cx, float cy) {
    float r = baseRadius + 40 * sin(time * frequency);
    float angle = time * frequency + angleOffset;
    pos.set(cx + r * cos(angle), cy + r * sin(angle));
}

void Particle::draw() {
    float brightness = ofMap(baseRadius, 50, 320, 160, 255);
    ofSetColor(255, brightness);
    ofDrawCircle(pos, 2);
}

// ------------------- ofApp -------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetCircleResolution(100);

    numParticles = 800;
    for (int i = 0; i < numParticles; i++) {
        Particle p;
        p.setup(i, numParticles);
        particles.push_back(p);
    }

    fbo.allocate(720, 1080, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
}

void ofApp::update() {
    time = ofGetElapsedTimef();
    for (auto& p : particles) {
        p.update(time, 720 / 2, 1080 / 2);
    }
}

void ofApp::draw() {
    fbo.begin();

    // Fading trail
    ofSetColor(0, 0, 0, 15);
    ofDrawRectangle(0, 0, 720, 1080);

    ofPushMatrix();
    ofTranslate(720 / 2, 1080 / 2);
    ofRotateDeg(sin(time * 1.0) * 100);
    ofTranslate(-720 / 2, -1080 / 2);

    // Draw particles
    for (auto& p : particles) {
        p.draw();
    }

    ofPopMatrix();
    fbo.end();

    // Draw final scene
    fbo.draw(0, 0);
}
