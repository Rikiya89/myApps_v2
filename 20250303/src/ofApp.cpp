// ofApp.cpp

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1280);
    ofSetFrameRate(60);
    ofBackground(0);
    cam.setPosition(0, 0, 800);
    cam.lookAt(glm::vec3(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    int numPoints = 300;
    float baseRadius = 250;
    float heightFactor = 150;
    float waveSpeed = 0.5;
    float sphereSize = 8;
    
    for (int i = 0; i < numPoints; i++) {
        float angle = i * TWO_PI / numPoints * 10;
        float radius = baseRadius + 50 * sin(time * waveSpeed + i * 0.1);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        float z = heightFactor * cos(time * 0.3 + i * 0.1);
        
        ofSetColor(255);
        ofDrawSphere(x, y, z, sphereSize);
        
        ofSetColor(255, 255, 255, 100);
        ofDrawLine(x, y, z, -x, -y, -z);
    }
    
    cam.end();
}
