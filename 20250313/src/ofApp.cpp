// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofBackground(10);
    ofSetFrameRate(60);
    numCircles = 250;
    timeOffset = ofRandom(1000);
    
    for (int i = 0; i < numCircles; i++) {
        points.push_back(ofVec2f(ofRandomWidth(), ofRandomHeight()));
        radii.push_back(ofRandom(5, 50));
        colors.push_back(ofColor::fromHsb(ofRandom(255), 200, 255));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef() * 0.5 + timeOffset;
    for (int i = 0; i < numCircles; i++) {
        float angle = ofNoise(i * 0.02, time * 0.1) * TWO_PI * 6;
        float radius = ofNoise(i * 0.05, time * 0.1) * 300;
        float x = ofGetWidth() / 2 + cos(angle) * radius;
        float y = ofGetHeight() / 2 + sin(angle) * radius;
        points[i] = ofVec2f(x, y);
        radii[i] = ofNoise(i * 0.03, time * 0.2) * 50 + 5;
        colors[i].setHsb(fmod(time * 20 + i * 7, 255), 180 + ofNoise(i * 0.1) * 75, 255);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetLineWidth(2);
    
    for (int i = 0; i < numCircles; i++) {
        ofSetColor(colors[i], 200);
        ofDrawCircle(points[i].x, points[i].y, radii[i]);
        
        // Connecting some circles for extra aesthetics
        if (i > 0) {
            ofSetColor(colors[i], 100);
            ofDrawLine(points[i].x, points[i].y, points[i-1].x, points[i-1].y);
        }
    }
    ofDisableBlendMode();
}
