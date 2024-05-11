#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255); // White background
}

void ofApp::update(){

}

void ofApp::draw(){
    int tileSize = 50; // Size of each tile
    for(int x = 0; x < ofGetWidth(); x += tileSize){
        for(int y = 0; y < ofGetHeight(); y += tileSize){
            ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); // Random color for each tile
            ofDrawRectangle(x, y, tileSize, tileSize); // Draw tile
        }
    }
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}
