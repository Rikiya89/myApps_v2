#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0); // Set background to black
    ofSetFrameRate(60); // Set the frame rate
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int numLines = 10;
    float maxRadius = 200;
    float angleStep = TWO_PI / numLines;
    float time = ofGetElapsedTimef();

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Move to center

    for(int i = 0; i < numLines; i++){
        float angle = i * angleStep;
        float x = cos(angle + time * 0.1) * maxRadius;
        float y = sin(angle + time * 0.1) * maxRadius;
        ofColor color;
        color.setHsb(i * (255 / numLines), 200, 255);
        ofSetColor(color);
        ofDrawLine(0, 0, x, y);
        ofDrawCircle(x, y, 10);
    }
}
