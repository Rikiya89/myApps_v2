#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofSetBackgroundColor(0); // Black background
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255); // White lines
    
    for (int i = 0; i < numLines; i++) {
        float yOffset = ofMap(i, 0, numLines, 100, ofGetHeight() - 100);
        ofPolyline line;
        
        for (int x = 0; x < ofGetWidth(); x += 5) {
            float noiseValue = ofNoise(x * noiseScale, i * 0.1, ofGetElapsedTimef() * 0.1);
            float y = yOffset + sin(noiseValue * TWO_PI) * amplitude;
            line.addVertex(x, y);
        }
        line.draw();
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
