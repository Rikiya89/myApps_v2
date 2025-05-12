#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();

    for (int i = 0; i < numParticles; i++) {
        positions.push_back(ofVec3f(
            ofRandom(-300, 300),
            ofRandom(-300, 300),
            ofRandom(-300, 300)
        ));

        // Neon cyberpunk colors
        vector<ofFloatColor> neonPalette = {
            ofFloatColor(0.0, 1.0, 1.0),   // Cyan
            ofFloatColor(1.0, 0.0, 1.0),   // Magenta
            ofFloatColor(1.0, 1.0, 0.0),   // Yellow
            ofFloatColor(0.0, 1.0, 0.5),   // Greenish
            ofFloatColor(0.5, 0.0, 1.0)    // Purple
        };

        colors.push_back(neonPalette[(int)ofRandom(neonPalette.size())]);

        // Random velocities for floating animation
        velocities.push_back(ofVec3f(
            ofRandom(-0.5, 0.5),
            ofRandom(-0.5, 0.5),
            ofRandom(-0.5, 0.5)
        ));
    }

    // Create background stars
    for (int i = 0; i < 300; i++) {
        stars.push_back(ofVec3f(
            ofRandom(-2000, 2000),
            ofRandom(-2000, 2000),
            ofRandom(-2000, 2000)
        ));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += 0.2; // Slowly rotate the scene

    for (int i = 0; i < numParticles; i++) {
        positions[i] += velocities[i];

        // Simple boundary check to bounce back
        if (positions[i].x > 300 || positions[i].x < -300) velocities[i].x *= -1;
        if (positions[i].y > 300 || positions[i].y < -300) velocities[i].y *= -1;
        if (positions[i].z > 300 || positions[i].z < -300) velocities[i].z *= -1;
    }

    cameraAngle += 0.1; // Slowly move the camera
    pulsePhase += 0.05; // For pulsing effect
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Additive blending for glow

    // Setup orbiting camera
    ofVec3f camPos;
    camPos.x = 800 * cos(ofDegToRad(cameraAngle));
    camPos.y = 400;
    camPos.z = 800 * sin(ofDegToRad(cameraAngle));

    ofCamera cam;
    cam.setPosition(camPos);
    cam.lookAt(glm::vec3(0, 0, 0));
    cam.begin();

    // Draw background stars
    ofPushStyle();
    ofSetColor(255, 100); // Soft white stars
    for (auto &star : stars) {
        ofDrawSphere(star, 1.5);
    }
    ofPopStyle();

    // Pulsing effect
    float pulseSize = ofMap(sin(pulsePhase), -1, 1, 0.9, 1.4); // Make pulsing slightly larger

    // Draw neon spheres with glow (stronger)
    for (int i = 0; i < numParticles; i++) {
        ofSetColor(colors[i], 180); // Strong outer glow
        ofDrawSphere(positions[i], 10 * pulseSize); // Slightly bigger glow size

        ofSetColor(colors[i], 255); // Full intensity solid center
        ofDrawSphere(positions[i], 5 * pulseSize);
    }
    // Draw glowing lines between nearby particles
    for (int i = 0; i < numParticles; i++) {
        for (int j = i + 1; j < numParticles; j++) {
            float distance = positions[i].distance(positions[j]);
            if (distance < 100) {
                ofSetColor(colors[i], ofMap(distance, 0, 100, 200, 30)); // Keep lines visible longer
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }

    cam.end();
    ofDisableBlendMode();
}
