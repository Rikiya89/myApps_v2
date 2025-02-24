// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);

    int numPoints = 2000;
    float radius = 350;

    for(int i = 0; i < numPoints; i++) {
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(PI);

        float x = radius * sin(phi) * cos(theta);
        float y = radius * sin(phi) * sin(theta);
        float z = radius * cos(phi);

        points.push_back(ofVec3f(x, y, z));
        angles.push_back(ofRandom(TWO_PI));
        speeds.push_back(ofRandom(0.01, 0.08));
    }

    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.02;
    for(int i = 0; i < points.size(); i++) {
        angles[i] += speeds[i];
        points[i].x += sin(angles[i] + time * 0.7) * 5;
        points[i].y += cos(angles[i] + time * 0.7) * 5;
        points[i].z += sin(time * 0.9 + angles[i] * 1.8) * 4;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    for(auto &p : points) {
        float distance = p.length();
        float alpha = ofMap(distance, 0, 350, 255, 60);
        ofColor col;
        col.setHsb(fmod(ofGetElapsedTimef() * 20, 255), 220, 255, alpha);
        ofSetColor(col);
        float size = 2.5 + sin(ofGetElapsedTimef() * 1.2 + distance * 0.025) * 2.0;
        ofDrawSphere(p, size);
    }

    cam.end();
}
