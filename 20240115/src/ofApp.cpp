#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    centerX = ofGetWidth() / 2;
    centerY = ofGetHeight() / 2;
    radius = 40.0f; // Increased initial radius
    layers = 30; // Increased number of layers for more complexity

    ofBackground(0);
    ofSetCircleResolution(100);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    radius = 40 + 10 * ofNoise(time * 0.3); // Larger dynamic radius variation
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    for (int i = 0; i < layers; ++i){
        float alpha = ofMap(i, 0, layers, 120, 30); // Adjusted alpha for more depth
        float offset = 10 * ofNoise(time + i * 0.05);

        ofColor color;
        color.setHsb(static_cast<int>(time * 10 + i * 20) % 255, 180, 220, alpha); // More vibrant color palette
        ofSetColor(color);

        drawFlowerOfLife(centerX + offset, centerY + offset, radius + i * 5, 6); // Increased spacing between layers
    }

    ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::drawFlowerOfLife(float x, float y, float radius, int layers){
    for (float angle = 0; angle < 360; angle += 30){ // Reduced angle increment for more circles
        float offsetX = radius * cos(ofDegToRad(angle));
        float offsetY = radius * sin(ofDegToRad(angle));
        ofDrawCircle(x + offsetX, y + offsetY, radius);
    }
}
