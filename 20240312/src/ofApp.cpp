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
    // Slowly rotate the background hue
    backgroundColor.setHueAngle(fmod(ofGetElapsedTimef() * 10, 360));
    // Create a fading trail effect
    ofSetColor(backgroundColor, 10);  // Adjust alpha for more/less trail
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    // Update rotation speeds
    for (size_t i = 0; i < rotationSpeeds.size(); i++) {
        rotationSpeeds[i] += 0.05 * (i + 1) * 0.05;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (size_t i = 0; i < scales.size(); i++) {
        float baseRadius = 120 * scales[i];
        float rotation = rotationSpeeds[i] * ofGetElapsedTimef();
        float timeOffset = animSpeed * ofGetElapsedTimef();

        // Dynamic color change with time
        ofColor color;
        color.setHsb(i * 64 + ofGetElapsedTimef() * 10, 255, 255, 180);
        drawSeedOfLife(centerX, centerY, baseRadius, rotation, timeOffset, color);
    }

    // Draw orbiting geometric shapes
    int numShapes = 6;
    float orbitRadius = 300;
    float shapeSize = 30;
    for (int i = 0; i < numShapes; i++) {
        float angle = ofGetElapsedTimef() * (1 + i / 5.0) + i;
        float x = centerX + orbitRadius * cos(angle);
        float y = centerY + orbitRadius * sin(angle);
        ofColor shapeColor;
        shapeColor.setHsb(255 * (i / float(numShapes)), 255, 255, 128);
        ofSetColor(shapeColor);
        ofDrawEllipse(x, y, shapeSize, shapeSize);
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
    mesh.addColor(ofColor(color, 0));  // Transparent center

    for (int i = 0; i <= numPoints; i++) {
        float dx = x + cos(angleStep * i) * radius;
        float dy = y + sin(angleStep * i) * radius;
        mesh.addVertex(ofPoint(dx, dy));
        mesh.addColor(color);
    }

    mesh.draw();
}
