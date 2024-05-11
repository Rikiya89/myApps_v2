#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);  // Set the background to white
    ofSetLineWidth(2);  // Starting line width for more visible, dynamic changes

    // Initialize variables
    angleOffsetA = 0.0;
    angleOffsetB = 0.0;
    radius = 300.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // Slowly update the angle offsets for a fluid motion
    angleOffsetA += 0.001;
    angleOffsetB += 0.0015;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // Draw a fractal-inspired pattern with a dynamic radial gradient
    for (int i = 0; i < 360; i += 5) {
        drawFractalLayer(i, radius, 3, 2);  // Recursively draw fractal layers with initial line width
    }
}

//--------------------------------------------------------------
void ofApp::drawFractalLayer(int angle, float rad, int depth, float lineWidth) {
    if (depth == 0) return;

    float radian = ofDegToRad(angle);
    float x = rad * cos(radian);
    float y = rad * sin(radian);

    float endRad = rad * 0.6; // Reduce radius for each recursive call
    float xEnd = endRad * cos(radian + angleOffsetA);
    float yEnd = endRad * sin(radian + angleOffsetB);

    // Set color to black with decreasing opacity
    ofSetColor(0, 255 * (depth / 3.0));  // Fade transparency with depth
    ofSetLineWidth(lineWidth);  // Adjust line width based on depth
    ofDrawLine(x, y, xEnd, yEnd);

    // Recursive call to draw smaller layers with reduced line width and increased transparency
    drawFractalLayer(angle + 5, endRad, depth - 1, lineWidth * 0.8);
    drawFractalLayer(angle - 5, endRad, depth - 1, lineWidth * 0.8);
}
