#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    int numPoints = 500;
    for (int i = 0; i < numPoints; i++) {
        float angle = ofMap(i, 0, numPoints, 0, TWO_PI);
        float radius = 200;
        float x = ofGetWidth() / 2 + radius * cos(angle);
        float y = ofGetHeight() / 2 + radius * sin(angle);
        points.push_back(ofPoint(x, y));
    }
    noiseOffset = 0.0;
    time = 0.0;
    hue = 0.0;
    symmetry = 6; // sacred geometry inspired
}

//--------------------------------------------------------------
void ofApp::update(){
    noiseOffset += 0.01;
    time += 0.01;
    hue += 0.5;
    if (hue > 255) hue -= 255;
    for (auto& p : points) {
        float noise = ofNoise(p.x * 0.005, p.y * 0.005, noiseOffset);
        float angle = noise * TWO_PI * 2;
        p.x += cos(angle) * 0.5;
        p.y += sin(angle) * 0.5;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 10); // fade effect
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    for (int i = 0; i < symmetry; i++) {
        ofPushMatrix();
        ofRotateDeg(360.0 / symmetry * i);

        ofColor c = ofColor::fromHsb(static_cast<int>(hue), 200, 255);
        ofSetColor(c);
        ofNoFill();
        ofBeginShape();
        for (auto& p : points) {
            ofVertex(p.x - ofGetWidth() / 2, p.y - ofGetHeight() / 2);
        }
        ofEndShape(true);

        for (auto& p : points) {
            ofDrawCircle(p.x - ofGetWidth() / 2, p.y - ofGetHeight() / 2, 1.5);
        }

        ofPopMatrix();
    }
    ofPopMatrix();

    fbo.end();

    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
