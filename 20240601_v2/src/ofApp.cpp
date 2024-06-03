#include "ofApp.h"

void ofApp::setup(){
    ofBackground(10, 10, 35);  // Dark background
    numShapes = 400;
    angle = 0.0;
    angleIncrement = 0.005;
    mouseXFactor = 0.5;
    mouseYFactor = 0.5;

    // Generate a gradient of colors
    for (int i = 0; i < numShapes; i++) {
        float hue = ofMap(i, 0, numShapes, 0, 255);
        colors.push_back(ofColor::fromHsb(hue, 200, 255));
        radii.push_back(ofRandom(5, 30));
        speeds.push_back(ofRandom(0.01, 0.05));
        offsets.push_back(ofRandom(TWO_PI));
        depths.push_back(ofRandom(-500, 500));
    }
}

void ofApp::update(){
    angle += angleIncrement;
    for (int i = 0; i < numShapes; i++) {
        radii[i] = 15 + 10 * sin(ofGetElapsedTimef() * speeds[i] + offsets[i]);
    }
}

void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    // Draw background stars
    ofSetColor(255, 255, 255, 50);  // Semi-transparent white
    for (int i = 0; i < 500; i++) {
        float starX = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
        float starY = ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
        ofDrawCircle(starX, starY, ofRandom(1, 3));
    }

    for (int i = 0; i < numShapes; i++) {
        float radius = ofMap(i, 0, numShapes, 100, 600) * sin(angle + i * 0.03);
        float x = radius * cos(angle + i * TWO_PI / numShapes);
        float y = radius * sin(angle + i * TWO_PI / numShapes);
        float z = depths[i] * sin(ofGetElapsedTimef() * speeds[i] + offsets[i]);
        ofSetColor(colors[i]);

        ofPushMatrix();
        ofTranslate(x * mouseXFactor, y * mouseYFactor, z);

        // Alternate shapes for more complexity
        if (i % 4 == 0) {
            ofDrawCircle(0, 0, radii[i]);
        } else if (i % 4 == 1) {
            ofDrawRectangle(-radii[i] / 2, -radii[i] / 2, radii[i], radii[i]);
        } else if (i % 4 == 2) {
            ofDrawTriangle(0, -radii[i], -radii[i] / 2, radii[i] / 2, radii[i] / 2, radii[i] / 2);
        } else {
            ofBeginShape();
            for (int j = 0; j < 5; j++) {
                float angleOffset = TWO_PI * j / 5;
                ofVertex(radii[i] * cos(angleOffset), radii[i] * sin(angleOffset));
            }
            ofEndShape(true);
        }

        ofSetColor(colors[i], 100);  // Semi-transparent for lines
        ofDrawLine(0, 0, x, y);

        ofPopMatrix();
    }

    ofPopMatrix();
}

void ofApp::mouseMoved(int x, int y ){
    mouseXFactor = ofMap(x, 0, ofGetWidth(), 0.1, 2.0);
    mouseYFactor = ofMap(y, 0, ofGetHeight(), 0.1, 2.0);
}
