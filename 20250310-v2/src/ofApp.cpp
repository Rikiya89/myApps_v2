#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();

    numLines = 120; // Number of generative curved lines
    resolution = 100; // Number of points per line
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef(); // Get elapsed time for animation
    
    for (int i = 0; i < numLines; i++) {
        float alpha = ofMap(i, 0, numLines, 50, 255); // Gradual fade effect
        ofSetColor(255, alpha); // White with transparency

        ofPolyline line;
        for (int j = 0; j < resolution; j++) {
            float x = ofMap(i, 0, numLines, 100, ofGetWidth() - 100);
            float y = ofMap(j, 0, resolution, 0, ofGetHeight());
            
            float noiseValue = ofNoise(x * 0.005, y * 0.005, time * 0.1);
            float offsetX = ofMap(noiseValue, 0, 1, -50, 50); // Create a wavy distortion

            line.addVertex(x + offsetX, y);
        }
        line.draw();
    }
}
