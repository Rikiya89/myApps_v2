#include "ofApp.h"

// ---------------- PARTICLE CLASS ---------------- //
Particle::Particle() {
    position = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    velocity = ofVec2f(0, 0);
    acceleration = ofVec2f(0, 0);
    
    maxSpeed = ofRandom(1.5, 3.0); // Dynamic speed variation
    noiseOffset = ofRandom(1000);  // Unique noise offset for each particle
    size = ofRandom(0.5, 2.5);     // Randomized particle size
}

void Particle::applyForce(ofVec2f force) {
    acceleration += force;
}

void Particle::update(float timeFactor) {
    // Layered Perlin Noise for more organic movement
    float noiseValue = ofNoise(position.x * 0.003, position.y * 0.003, timeFactor * 0.05) * TWO_PI * 4;
    float noiseValue2 = ofNoise(position.x * 0.007, position.y * 0.007, timeFactor * 0.02) * TWO_PI * 2;
    
    float angle = noiseValue + noiseValue2; // Combine multiple noise fields
    ofVec2f force = ofVec2f(cos(angle), sin(angle)) * 0.6;
    
    // Dynamic speed changes
    float speedFactor = ofNoise(noiseOffset + timeFactor * 0.1) * 2.0;
    force *= speedFactor;
    
    applyForce(force);
    velocity += acceleration;
    velocity.limit(maxSpeed);
    position += velocity;
    
    acceleration *= 0;
    edges();
}

void Particle::edges() {
    if (position.x < 0) position.x = ofGetWidth();
    if (position.x > ofGetWidth()) position.x = 0;
    if (position.y < 0) position.y = ofGetHeight();
    if (position.y > ofGetHeight()) position.y = 0;
}

void Particle::draw() {
    ofSetColor(255, 180);
    ofDrawCircle(position, size);
}

// ---------------- APP CLASS ---------------- //
void ofApp::setup() {
    ofSetWindowShape(720, 1080);
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    baseNoiseScale = 0.002;
    useLines = true;

    for (int i = 0; i < 8000; i++) {
        particles.push_back(Particle());
    }
}

void ofApp::update() {
    float timeFactor = ofGetElapsedTimef(); // Get elapsed time for animation

    for (auto &p : particles) {
        p.update(timeFactor);
    }
}

void ofApp::draw() {
    fbo.begin();
    
    // Slow fading effect
    ofSetColor(0, 8);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    if (useLines) {
        for (size_t i = 0; i < particles.size(); i += 5) {
            ofSetColor(255, 90);
            ofDrawLine(particles[i].position, particles[(i + 3) % particles.size()].position);
        }
    }

    for (auto &p : particles) {
        p.draw();
    }

    fbo.end();
    fbo.draw(0, 0);
}

void ofApp::keyPressed(int key) {
    if (key == 'r') {
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
    } else if (key == 'l') {
        useLines = !useLines;
    }
}
