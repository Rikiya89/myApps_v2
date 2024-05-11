#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0); // Set initial background to black
    ofSetCircleResolution(100); // Improve the circle resolution
    ofSetFrameRate(60); // Set the frame rate
}

void ofApp::update(){
    // Update the background color over time to create a dynamic background effect
    float time = ofGetElapsedTimef();
    ofColor bgColor;
    bgColor.setHsb(fmod(time * 5, 255), 180, 230);
    ofBackground(bgColor);
}

void ofApp::draw(){
    float time = ofGetElapsedTimef();
    for (int i = 0; i < 3; i++) {
        ofPushMatrix(); // Save the current coordinate system
        // Move the origin to the center of the screen
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        // Rotate each layer at a different speed and direction
        if (i % 2 == 0) {
            ofRotateDeg(fmod(time * (10 + i * 5), 360));
        } else {
            ofRotateDeg(-fmod(time * (10 + i * 5), 360));
        }
        // Draw the Flower of Life pattern with varying sizes and properties
        drawFlowerOfLife(0, 0, 6, 100 - i * 20, i % 2 == 0);
        ofPopMatrix(); // Restore the original coordinate system
    }
}

void ofApp::drawFlowerOfLife(float x, float y, int layers, float radius, bool primary){
    float time = ofGetElapsedTimef();
    for (int i = 0; i < layers; i++) {
        int numCircles = 6 * (i + 1);
        for (int j = 0; j < numCircles; j++) {
            ofPoint center = getCircleCenter(x, y, (radius + sin(time * (2 + i) + j) * (primary ? 10 : 5)) * i, j, numCircles);
            ofColor color;
            float hue = ofMap(j, 0, numCircles, 0, 255) + fmod(time * 10, 255);
            float brightness = ofMap(sin(time * (3 + i) + j), -1, 1, 0, 1) * (primary ? 255 : 120);
            color.setHsb(fmod(hue, 255), 255, brightness);
            ofSetColor(color);
            float dynamicRadius = radius + sin(time * (3 + i) + j) * (primary ? 15 : 7);
            ofDrawCircle(center.x, center.y, dynamicRadius);
        }
    }
}

ofPoint ofApp::getCircleCenter(float x, float y, float radius, int index, int total) {
    float angle = TWO_PI / total * index;
    float cx = x + cos(angle) * radius;
    float cy = y + sin(angle) * radius;
    return ofPoint(cx, cy);
}
