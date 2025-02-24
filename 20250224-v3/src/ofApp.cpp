// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);

    int numPoints = 500;
    float radius = 200;

    for(int i = 0; i < numPoints; i++) {
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(PI);

        float x = radius * sin(phi) * cos(theta);
        float y = radius * sin(phi) * sin(theta);
        float z = radius * cos(phi);

        points.push_back(ofVec3f(x, y, z));
        angles.push_back(ofRandom(TWO_PI));
    }

    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.01;
    for(int i = 0; i < points.size(); i++) {
        angles[i] += 0.02;
        points[i].x += sin(angles[i]) * 2;
        points[i].y += cos(angles[i]) * 2;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofSetColor(255);

    for(auto &p : points) {
        ofDrawSphere(p, 2);
    }

    cam.end();
}

//--------------------------------------------------------------
int main(){
    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new ofApp());
}
