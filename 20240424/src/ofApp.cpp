#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);  // Set the background to white
    ofSetLineWidth(0.5);  // Use a finer line width for detailed patterns

    // Initialize variables
    angleOffsetA = 0.0;
    angleOffsetB = 0.0;
    radius = 300.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // Slowly update the angle offsets for dynamic motion
    angleOffsetA += 0.002;
    angleOffsetB += 0.003;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // Draw a dynamic spiral pattern with wave influence
    for (int i = 0; i < 360; i += 2) {
        float angle = ofDegToRad(i);
        float spiralEffect = ofMap(sin(ofGetFrameNum() * 0.01), -1, 1, 0.5, 2);
        this->drawWaveFractalLayer(i, radius * spiralEffect, 3, 2);  // Recursively draw layers with proper scope
    }
}

//--------------------------------------------------------------
void ofApp::drawWaveFractalLayer(int angle, float rad, int depth, float lineWidth) {
    if (depth == 0) return;

    float radian = ofDegToRad(angle);
    float x = rad * cos(radian);
    float y = rad * sin(radian);

    // Dynamic end radius influenced by wave patterns
    float endRad = rad * 0.6 + 20 * sin(radian * 4 + ofGetFrameNum() * 0.02);
    float xEnd = endRad * cos(radian + this->angleOffsetA);  // Use 'this' to specify scope
    float yEnd = endRad * sin(radian + this->angleOffsetB);  // Use 'this' to specify scope

    ofSetColor(0, 255 * (depth / 3.0));  // Gradual fading
    ofSetLineWidth(lineWidth);  // Adjust line width based on depth
    ofDrawLine(x, y, xEnd, yEnd);

    // Recursive calls to create intricate and evolving patterns
    this->drawWaveFractalLayer(angle + 5, endRad, depth - 1, lineWidth * 0.8);
    this->drawWaveFractalLayer(angle - 5, endRad, depth - 1, lineWidth * 0.8);
}
