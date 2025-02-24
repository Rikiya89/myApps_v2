// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(10, 10, 30);
    ofEnableSmoothing();
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {
    rotationAngle += 0.5; // Rotate elements dynamically
    pulseFactor = sin(ofGetElapsedTimef() * 2) * 10; // Pulsating effect
    waveOffset += 0.02; // Wavy movement
}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin();

    ofPushMatrix();
    ofRotateYDeg(rotationAngle);

    ofNoFill();
    ofSetColor(0, 255, 200);
    ofSetLineWidth(2);

    drawFlowerOfLife();
    ofSetColor(255, 100, 0);
    drawMetatronCube();
    ofSetColor(255, 255, 50);
    drawStar();

    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::drawFlowerOfLife() {
    for (int i = 0; i < numCircles; i++) {
        float angle = TWO_PI * i / numCircles;
        float dynamicRadius = radius + pulseFactor;
        ofVec3f center = ofVec3f(dynamicRadius * cos(angle), dynamicRadius * sin(angle), sin(angle + waveOffset) * 20);

        ofDrawCircle(center, dynamicRadius);
    }
    ofDrawCircle(ofVec3f(0, 0, sin(waveOffset) * 20), radius + pulseFactor);
}

//--------------------------------------------------------------
void ofApp::drawMetatronCube() {
    for (int i = 0; i < numCircles; i++) {
        for (int j = i + 1; j < numCircles; j++) {
            float angle1 = TWO_PI * i / numCircles;
            float angle2 = TWO_PI * j / numCircles;

            ofVec3f p1 = ofVec3f(radius * cos(angle1), radius * sin(angle1), sin(angle1 + waveOffset) * 20);
            ofVec3f p2 = ofVec3f(radius * cos(angle2), radius * sin(angle2), sin(angle2 + waveOffset) * 20);

            ofDrawLine(p1, p2);
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawStar() {
    int numPoints = 12;
    float innerRadius = radius * 0.5 + pulseFactor;
    float outerRadius = radius * 1.5 + pulseFactor;
    ofPolyline star;

    for (int i = 0; i < numPoints * 2; i++) {
        float angle = PI * i / numPoints;
        float r = (i % 2 == 0) ? outerRadius : innerRadius;
        ofVec3f point = ofVec3f(r * cos(angle), r * sin(angle), sin(angle + waveOffset) * 20);
        star.addVertex(point);
    }
    star.close();
    star.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') {
        ofSaveScreen("screenshot.png");
    }
}
