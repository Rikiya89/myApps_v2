#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofEnableDepthTest();

    // Setup lighting
    light.setup();
    light.setPosition(200, 300, 500);
    light.enable();
    ofEnableLighting();

    // Initial rotation angle and time
    angle = 0;
    time = 0;
}

void ofApp::update() {
    angle += 0.5;
    time += 0.01;
}

void ofApp::draw() {
    cam.begin();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    float offsetX = ofGetWidth() / 2 * sin(time);
    float offsetY = ofGetHeight() / 2 * cos(time);
    ofTranslate(offsetX, offsetY, 0);

    ofRotateYDeg(angle);

    // Draw the 3D Flower of Life pattern
    drawFlowerOfLife(0, 0, 0, 50, 3);

    cam.end();
}

void ofApp::drawFlowerOfLife(float x, float y, float z, float radius, int depth) {
    if (depth == 0) return;

    // Set color based on depth with a gradient
    ofSetColor(ofColor::fromHsb(ofMap(depth, 1, 3, 0, 255), 255, 255));

    // Draw sphere
    ofFill();
    ofDrawSphere(x, y, z, radius);

    float offset = radius * 1.5;
    for (int i = 0; i < 6; i++) {
        float angle = ofDegToRad(60 * i);
        float nx = x + offset * cos(angle);
        float ny = y + offset * sin(angle);
        drawFlowerOfLife(nx, ny, z, radius, depth - 1);
    }
}
