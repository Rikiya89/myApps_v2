#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);                // Smooth animation
    ofSetBackgroundColor(5, 10, 30);  // Deep cosmic blue background

    // Sacred geometry parameters
    rotationSpeed = 0.3;  // Smooth, slow rotation
    numRings = 8;         // Rings for the Flower of Life
    numPetals = 18;       // Petals per ring
    baseRadius = 80;      // Base radius of the innermost circle

    // Particle setup for glowing ambiance
    int numParticles = 300; // Number of glowing particles
    for (int i = 0; i < numParticles; i++) {
        glm::vec3 pos = glm::vec3(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
        particles.push_back(pos);
        particleColors.push_back(ofColor::fromHsb(ofRandom(200, 255), 200, 255, 150));
    }

    cam.setDistance(800); // Set the camera distance for an immersive view
}

//--------------------------------------------------------------
void ofApp::update(){
    // Animate particles for subtle motion
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].x += ofRandom(-1, 1);
        particles[i].y += ofRandom(-1, 1);
        particles[i].z += ofRandom(-1, 1);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin(); // Start the 3D camera view

    float time = ofGetElapsedTimef(); // Time for animation

    // Draw the Flower of Life
    for (int ring = 0; ring < numRings; ring++) {
        float radius = baseRadius + ring * 50; // Expand radius for each ring

        // Rotate each ring in a spiraling motion
        ofPushMatrix();
        ofRotateDeg(time * rotationSpeed * (ring + 1), 0, 1, 0); // Rotate along the Y-axis

        for (int petal = 0; petal < numPetals; petal++) {
            float angle = ofDegToRad(petal * 360.0 / numPetals); // Angle for petal position
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Create 3D spiraling effect
            float z = 40 * sin(angle * 2 + time * 0.5 + ring * 0.3);

            // Glowing petal
            ofColor color = ofColor::fromHsb(
                ofMap(petal + ring * 10, 0, numPetals * numRings, 0, 255), 180, 255
            );
            drawGlowingCircle(x, y, z, 20 + 10 * sin(time + ring * 0.2), color);
        }

        ofPopMatrix();
    }

    // Draw a glowing pulsating center
    drawGlowingCircle(0, 0, 0, 50 + 10 * sin(time * 2), ofColor(255, 180, 220));

    // Draw particles for an ethereal glow
    drawParticles();

    cam.end(); // End the 3D camera view
}

//--------------------------------------------------------------
void ofApp::drawParticles() {
    for (size_t i = 0; i < particles.size(); i++) {
        ofSetColor(particleColors[i]);
        ofDrawSphere(particles[i], 2); // Tiny glowing spheres
    }
}

//--------------------------------------------------------------
void ofApp::drawGlowingCircle(float x, float y, float z, float size, ofColor color) {
    ofPushMatrix();
    ofTranslate(x, y, z);
    ofSetColor(color, 50); // Outer glow
    ofDrawSphere(0, 0, size * 1.5);

    ofSetColor(color, 120); // Inner glow
    ofDrawSphere(0, 0, size);

    ofSetColor(color); // Core
    ofDrawSphere(0, 0, size * 0.8);
    ofPopMatrix();
}
