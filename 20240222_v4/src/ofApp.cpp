#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60); // Set frame rate
    ofBackground(0); // Set background to black
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update logic can go here
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef(); // Get elapsed time
    for (int i = 0; i < ofGetWidth(); i += 10) {
        for (int j = 0; j < ofGetHeight(); j += 10) {
            float noiseValue = ofNoise(i * 0.05, j * 0.05, time * 0.5);
            ofSetColor(255 * noiseValue); // Set color based on noise
            ofDrawRectangle(i, j, 10, 10); // Draw a rectangle
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
