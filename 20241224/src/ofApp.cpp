#include "ofApp.h"
#include "Snowflake.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetCircleResolution(50);
    ofEnableAlphaBlending(); // Enable transparency
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Additive blending for glowing effects

    // Create snowflakes
    int snowflakeCount = 150; // Number of snowflakes
    for (int i = 0; i < snowflakeCount; i++) {
        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        float speed = ofRandom(1, 3); // Falling speed
        float size = ofRandom(10, 30); // Size
        float rotationSpeed = ofRandom(-1, 1); // Rotation speed
        ofColor color = ofColor::fromHsb(ofRandom(200, 255), 180, 255); // Glowing colors
        snowflakes.emplace_back(x, y, speed, size, rotationSpeed, color);
    }

    // Initialize time for dynamic gradient
    timeElapsed = 0.0;
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto& snowflake : snowflakes) {
        snowflake.update(); // Update position
    }
    timeElapsed += ofGetLastFrameTime(); // Update time
}

//--------------------------------------------------------------
void ofApp::draw() {
    drawDynamicGradientBackground();
    for (auto& snowflake : snowflakes) {
        snowflake.draw(); // Draw snowflakes
    }
}

//--------------------------------------------------------------
void ofApp::drawDynamicGradientBackground() {
    ofMesh gradientMesh;
    gradientMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    // Dynamic colors based on time
    float hueTop = fmod(timeElapsed * 10, 255); // Cycle top hue
    float hueBottom = fmod((timeElapsed * 10) + 50, 255); // Offset bottom hue

    ofColor topColor = ofColor::fromHsb(hueTop, 180, 120);
    ofColor bottomColor = ofColor::fromHsb(hueBottom, 180, 60);

    gradientMesh.addColor(topColor);
    gradientMesh.addVertex(ofPoint(0, 0));
    gradientMesh.addColor(topColor);
    gradientMesh.addVertex(ofPoint(ofGetWidth(), 0));

    gradientMesh.addColor(bottomColor);
    gradientMesh.addVertex(ofPoint(0, ofGetHeight()));
    gradientMesh.addColor(bottomColor);
    gradientMesh.addVertex(ofPoint(ofGetWidth(), ofGetHeight()));

    gradientMesh.draw();
}
