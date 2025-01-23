#include "ofApp.h"

void ofApp::setup() {
    ofBackground(10);  // Dark background
    ofSetCircleResolution(60);
    ofSetFrameRate(30);  // Lower frame rate for performance

    time = 0.0;
    numCircles = 5;  // Limit recursion levels
    radiusMultiplier = 1.0;
    baseColor = ofColor(100, 100, 255);  // Base gradient color
    secondaryColor = ofColor(255, 150, 100);  // Complementary gradient color
}

void ofApp::update() {
    time += 0.01;  // Time-based animation
    radiusMultiplier = 1.0 + 0.3 * sin(time);  // Oscillating radius
}

void ofApp::draw() {
    drawBackground();  // Dynamic background
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);  // Center the drawing

    float globalRotation = time * 20;  // Global rotation speed
    drawSacredGeometry(0, 0, 150 * radiusMultiplier, numCircles, globalRotation);
}

void ofApp::drawSacredGeometry(float x, float y, float radius, int levels, float rotation) {
    if (levels <= 0 || radius < 5) return;  // Stop recursion at small radius

    float angleStep = TWO_PI / 6;  // Hexagonal pattern
    float hueShift = ofMap(levels, 1, numCircles, 0, 255);  // Color gradient by level
    ofColor circleColor = baseColor;
    circleColor.setHue(fmod(circleColor.getHue() + hueShift, 255));

    ofPushMatrix();
    ofRotateDeg(rotation);  // Apply global rotation
    for (int i = 0; i < 6; i++) {
        float angle = i * angleStep;
        float nx = x + radius * cos(angle);
        float ny = y + radius * sin(angle);

        // Draw circle with glow
        ofSetColor(circleColor, 50);  // Outer glow
        ofDrawCircle(nx, ny, radius / 2.5);
        ofSetColor(circleColor, 150);  // Inner circle
        ofDrawCircle(nx, ny, radius / 3);

        // Recursive drawing
        drawSacredGeometry(nx, ny, radius / 2.0, levels - 1, rotation * 0.9);
    }
    ofPopMatrix();

    // Central glow
    ofFill();
    ofSetColor(circleColor, 100);
    ofDrawCircle(x, y, radius / 10);
}

void ofApp::drawBackground() {
    ofMesh gradientMesh;
    gradientMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    glm::vec2 center(ofGetWidth() / 2, ofGetHeight() / 2);
    gradientMesh.addVertex(glm::vec3(center, 0));
    gradientMesh.addColor(ofColor::black);

    for (int i = 0; i <= 360; i += 10) {
        float angle = ofDegToRad(i);
        float x = center.x + ofGetWidth() * cos(angle);
        float y = center.y + ofGetHeight() * sin(angle);

        ofColor gradientColor = baseColor;
        gradientColor.lerp(secondaryColor, ofMap(sin(time * 0.5), -1, 1, 0, 1));  // Smooth transition
        gradientMesh.addVertex(glm::vec3(x, y, 0));
        gradientMesh.addColor(gradientColor);
    }

    gradientMesh.draw();
}

void ofApp::keyPressed(int key) {
    if (key == OF_KEY_UP && numCircles < 10) numCircles++;          // Increase levels
    if (key == OF_KEY_DOWN && numCircles > 1) numCircles--;  // Decrease levels
}
