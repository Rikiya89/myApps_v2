#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    centerX = ofGetWidth() / 2;
    centerY = ofGetHeight() / 2;
    animSpeed = 0.1;
    backgroundColor = ofColor(0);

    // Initialize rotation speeds and scale factors
    rotationSpeeds = {0.015, -0.01, 0.02};
    scales = {1.0, 0.8, 1.2};
}

//--------------------------------------------------------------
void ofApp::update(){
    backgroundColor.setHueAngle(fmod(ofGetElapsedTimef() * 10, 360));
    ofBackground(backgroundColor);

    // Update rotation speeds
    for (size_t i = 0; i < rotationSpeeds.size(); i++) {
        rotationSpeeds[i] += 0.05 * (i + 1) * 0.05;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (size_t i = 0; i < scales.size(); i++) {
        float baseRadius = 100 * scales[i];
        float rotation = rotationSpeeds[i] * ofGetElapsedTimef();
        float timeOffset = animSpeed * ofGetElapsedTimef();

        // Color changing over time
        ofColor color;
        color.setHsb(i * 64 + ofGetElapsedTimef() * 10, 255, 255, 180);
        drawSeedOfLife(centerX, centerY, baseRadius, rotation, timeOffset, color);
    }
}

void ofApp::drawSeedOfLife(float x, float y, float baseRadius, float rotation, float timeOffset, ofColor color) {
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotateDeg(rotation);

    int numCircles = 6;
    float angle = TWO_PI / numCircles;
    float animatedRadius = baseRadius + 10 * sin(ofGetElapsedTimef());

    for (int i = 0; i <= numCircles; i++) {
        float dx = animatedRadius * cos(angle * i + timeOffset);
        float dy = animatedRadius * sin(angle * i + timeOffset);
        drawCircle(dx, dy, animatedRadius, color);
    }

    ofPopMatrix();
}

void ofApp::drawCircle(float x, float y, float radius, ofColor color) {
    int numPoints = 100;
    float angleStep = TWO_PI / numPoints;

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    mesh.addVertex(ofPoint(x, y));
    mesh.addColor(ofColor(color, 0));

    for (int i = 0; i <= numPoints; i++) {
        float dx = x + cos(angleStep * i) * radius;
        float dy = y + sin(angleStep * i) * radius;
        mesh.addVertex(ofPoint(dx, dy));
        mesh.addColor(color);
    }

    mesh.draw();
}
