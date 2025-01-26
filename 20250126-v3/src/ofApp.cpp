#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(10, 10, 40);   // Static dark cosmic background
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // Initialize stars
    int starCount = 500; // Increased star count for richer visuals
    for (int i = 0; i < starCount; i++) {
        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        stars.push_back(ofVec2f(x, y));
        starVelocities.push_back(ofVec2f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5))); // Slower movement for elegance
        starAngles.push_back(ofRandom(0, TWO_PI)); // Random angles for spiral motion
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update star positions with spiral motion
    for (int i = 0; i < stars.size(); i++) {
        float radius = 50 + i % 3 * 20; // Layered spirals
        starAngles[i] += 0.01 + 0.002 * (i % 3); // Different speeds for depth
        stars[i].x += cos(starAngles[i]) * radius * 0.005;
        stars[i].y += sin(starAngles[i]) * radius * 0.005;

        // Wrap-around effect
        if (stars[i].x < 0) stars[i].x = ofGetWidth();
        if (stars[i].x > ofGetWidth()) stars[i].x = 0;
        if (stars[i].y < 0) stars[i].y = ofGetHeight();
        if (stars[i].y > ofGetHeight()) stars[i].y = 0;
    }

    // Update comet angle and mandala rotation
    cometAngle += 0.5;  // Dynamic comet motion
    if (cometAngle >= 360) cometAngle = 0;

    mandalaRotation += 0.3;  // Mandala rotation
    if (mandalaRotation >= 360) mandalaRotation = 0;

    // Update aurora animation
    auroraTime += 0.02;
}

//--------------------------------------------------------------
void ofApp::draw() {
    drawPulsingBackground();  // Subtle pulsing background
    drawAurora();             // Flowing aurora waves with color shifts
    drawStars();              // Draw shimmering, spiraling stars
    drawRadiatingHalo();      // Draw glowing halo
    drawMandala();            // Draw intricate mandala with breathing glow
    drawComet();              // Draw the glowing comet with particles
}

// Function to draw pulsing background
void ofApp::drawPulsingBackground() {
    float time = ofGetElapsedTimef();
    float pulse = 10 + 5 * sin(time * 0.5); // Subtle pulsing effect
    ofSetColor(10 + pulse, 10 + pulse, 40 + pulse, 255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

// Function to draw aurora waves with color shifts
void ofApp::drawAurora() {
    for (int i = 0; i < 3; i++) {
        ofSetColor(50 + i * 30, 100 + i * 20, 255 - i * 30, 80); // Gradient colors
        ofBeginShape();
        for (int x = 0; x < ofGetWidth(); x += 10) {
            float y = 100 + 50 * i + 50 * sin(x * 0.01 + auroraTime + i);
            ofVertex(x, y);
        }
        ofEndShape(false);
    }
}

// Function to draw shimmering, spiraling stars
void ofApp::drawStars() {
    float time = ofGetElapsedTimef();
    for (int i = 0; i < stars.size(); i++) {
        float depth = i % 3 + 1; // Create 3 layers of depth
        float brightness = ofNoise(time + i) * 100 + 155 / depth; // Depth affects brightness
        ofSetColor(100, 150, 255, brightness);
        ofDrawCircle(stars[i].x, stars[i].y, depth); // Larger stars for closer layers
    }
}

// Function to draw sacred mandala with breathing glow
void ofApp::drawMandala() {
    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;

    ofPushMatrix();
    ofTranslate(centerX, centerY);
    ofRotateDeg(mandalaRotation);

    for (int i = 0; i < 6; i++) {  // Draw 6 intricate mandala layers
        float radius = 100 + i * 50 + 10 * sin(ofGetElapsedTimef() + i); // Pulsing radius
        int sides = 6 + i * 3;  // More sides for detailed patterns

        ofSetColor(50 + i * 20, 90 + i * 10, 255 - i * 10, 150);
        ofSetLineWidth(2);
        ofNoFill();
        ofBeginShape();
        for (int j = 0; j < sides; j++) {
            float angle = TWO_PI * j / sides;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            ofVertex(x, y);
        }
        ofEndShape(true);
    }

    ofPopMatrix();
}

// Function to draw a glowing halo
void ofApp::drawRadiatingHalo() {
    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;

    float time = ofGetElapsedTimef();
    for (int i = 0; i < 60; i++) { // Gradual halo effect
        ofSetColor(50, 100, 200, 150 - i * 2);
        float radius = 120 + i * 4 + 10 * sin(time * 0.5); // Dynamic halo radius
        ofDrawCircle(centerX, centerY, radius);
    }
}

// Function to draw glowing comet with particles
void ofApp::drawComet() {
    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;
    float cometX = centerX + 300 * cos(ofDegToRad(cometAngle));
    float cometY = centerY + 300 * sin(ofDegToRad(cometAngle));

    // Comet glow
    for (int i = 0; i < 60; i++) { // Longer tail
        ofSetColor(80, 120, 220, 200 - i * 3);
        ofDrawCircle(cometX, cometY, 30 - i * 0.5);
    }

    // Comet core
    ofSetColor(200, 220, 255);
    ofDrawCircle(cometX, cometY, 10);

    // Particle trail
    for (int i = 0; i < 10; i++) {
        float offsetX = ofRandom(-15, 15);
        float offsetY = ofRandom(-15, 15);
        ofSetColor(100, 180, 255, 150);
        ofDrawCircle(cometX + offsetX, cometY + offsetY, 5);
    }
}
