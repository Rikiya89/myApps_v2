#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Setup parameters
    ofSetFrameRate(60);  // Set frame rate
    ofBackground(0);  // Set background color to black
    
    // Initialize parameters
    centerX = ofGetWidth() / 2;
    centerY = ofGetHeight() / 2;
    size = 300;  // Size can be adjusted
    rotation = 0;  // Initialize rotation
    pulse = 0;     // Initialize pulse
    blurAmount = 0.85;  // Set the blur intensity

    // Setup colors for gradient effect
    startColor = ofColor(128, 0, 255);  // Purple
    endColor = ofColor(0, 255, 255);    // Cyan

    // Initialize FBO
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += 0.5;  // Increment rotation for animation
    pulse = abs(sin(ofGetElapsedTimef()));  // Create a pulsating effect

    // Update the FBO for motion blur
    fbo.begin();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 40);  // Semi-transparent black fill
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofDisableAlphaBlending();
    draw();  // Draw the current frame's visuals
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0, 0);  // Draw the buffered image for the blur effect

    ofPushMatrix();  // Save the current transformation matrix
    ofTranslate(centerX, centerY);  // Translate to the center
    ofRotateDeg(rotation);  // Rotate the whole cube

    drawMetatronCube(0, 0, size * pulse);

    ofPopMatrix();  // Restore the original transformation matrix
}

//--------------------------------------------------------------
void ofApp::drawMetatronCube(float centerX, float centerY, float size){
    float radius = size * sqrt(2) / 2;
    float angleStep = TWO_PI / 6;
    vector<ofPoint> points;

    // Calculate the points of the outer circle
    for (int i = 0; i < 6; i++) {
        float x = centerX + radius * cos(angleStep * i);
        float y = centerY + radius * sin(angleStep * i);
        points.push_back(ofPoint(x, y));
    }

    // Draw the circles with gradient colors and glow
    for (int i = 0; i < points.size(); i++) {
        ofColor color = startColor.getLerped(endColor, float(i) / points.size());
        ofSetColor(color, 180);  // Semi-transparent for a glow effect
        ofDrawCircle(points[i], (size / 6) + 10 * pulse);  // Dynamic size based on pulse
    }

    // Draw the lines with changing alpha values and dynamic width
    ofSetLineWidth(2 + 10 * pulse);  // Dynamic line width based on pulse
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            float alpha = 255 * (1 - float(j - i) / points.size());
            ofSetColor(255, 255, 255, alpha);
            ofDrawLine(points[i], points[j]);
        }
    }
}
