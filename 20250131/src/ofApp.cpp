#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(0, 0, 51); // Dark blue
    ofSetFrameRate(60);

    // Create the sphere
    sphere.setRadius(200);
    sphere.setResolution(20);

    // Generate star map
    generateStarMap();

    // Initialize rotation angles
    rotationAngleX = 0.0f;
    rotationAngleY = 0.0f;

    // Initialize comet
    cometAngle = 0.0f;

    // Generate nebula particles
    for (int i = 0; i < 50; ++i) {
        nebulaParticles.push_back(ofVec3f(ofRandom(-250, 250), ofRandom(-250, 250), ofRandom(-250, 250)));
    }

    // Generate aurora waves
    for (int i = 0; i < 100; ++i) {
        auroraWaves.push_back(ofVec3f(ofRandom(-300, 300), ofRandom(100, 250), ofRandom(-300, 300)));
    }

    // Generate galaxy dust
    for (int i = 0; i < 200; ++i) {
        galaxyDustParticles.push_back(ofVec3f(ofRandom(-350, 350), ofRandom(-350, 350), ofRandom(-350, 350)));
    }
}

void ofApp::update() {
    // Update rotation angles
    rotationAngleX += 0.1f;
    rotationAngleY += 0.15f;

    // Update comet movement
    updateComet();
}

void ofApp::draw() {
    cam.begin();

    // Apply rotations
    ofPushMatrix();
    ofRotateXDeg(rotationAngleX);
    ofRotateYDeg(rotationAngleY);

    // Draw the sphere
    sphere.drawWireframe();

    // Draw the star map
    drawStarMap();

    // Draw comet
    drawComet();

    // Draw nebula
    drawNebula();

    // Draw aurora
    drawAurora();

    // Draw galaxy dust
    drawGalaxyDust();

    ofPopMatrix();
    cam.end();
}

void ofApp::generateStarMap() {
    int numStars = 100;

    for (int i = 0; i < numStars; ++i) {
        float theta = ofRandom(0, TWO_PI);
        float phi = ofRandom(0, PI);

        float x = sphere.getRadius() * sin(phi) * cos(theta);
        float y = sphere.getRadius() * sin(phi) * sin(theta);
        float z = sphere.getRadius() * cos(phi);

        stars.push_back(ofVec3f(x, y, z));
    }
}

void ofApp::drawStarMap() {
    ofSetColor(153, 101, 21);
    for (const auto& star : stars) {
        ofDrawSphere(star, 2);
    }
}

void ofApp::updateComet() {
    float radius = sphere.getRadius() * 1.2;
    cometAngle += 0.02f;
    float x = radius * cos(cometAngle);
    float y = radius * sin(cometAngle);
    float z = ofRandom(-50, 50);
    cometPosition = ofVec3f(x, y, z);
    cometTrail.push_back(cometPosition);
    if (cometTrail.size() > 20) cometTrail.erase(cometTrail.begin());
}

void ofApp::drawComet() {
    ofSetColor(255, 223, 0);
    for (const auto& pos : cometTrail) {
        ofDrawSphere(pos, 2);
    }
    ofDrawSphere(cometPosition, 4);
}

void ofApp::drawNebula() {
    ofSetColor(100, 50, 150, 150);
    for (const auto& particle : nebulaParticles) {
        ofDrawSphere(particle, 3);
    }
}

void ofApp::drawAurora() {
    ofSetColor(50, 255, 150, 150);
    for (const auto& wave : auroraWaves) {
        ofDrawSphere(wave, 5);
    }
}

void ofApp::drawGalaxyDust() {
    ofSetColor(200, 150, 255, 100);
    for (const auto& dust : galaxyDustParticles) {
        ofDrawSphere(dust, 1);
    }
}
