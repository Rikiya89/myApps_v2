#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofSetBackgroundColor(1, 1, 12);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    float rotation = sin(time * 0.06) * 30;
    ofRotateDeg(rotation);

    for (int j = 1; j <= 9; j++) {
        float layerOffset = j * 0.5;

        for (int i = 0; i < 360; i += 1) {
            float angle = ofDegToRad(i + sin(time * 0.25 + j) * 360);
            float noiseFactor = ofNoise(cos(angle) * 0.7, sin(angle) * 0.7, time * 0.06 + layerOffset);
            float radius = ofMap(noiseFactor, 0, 1, 60 * j, 110 * j);

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            float r = ofMap(noiseFactor, 0, 1, 150, 255);
            float g = ofMap(sin(angle * 5 + time * 0.3), -1, 1, 140, 255);
            float b = ofMap(cos(angle * 4 + time * 0.4), -1, 1, 180, 255);

            ofSetColor(r, g, b, 140);
            ofDrawCircle(x, y, 2.5);

            if(j % 2 == 0){
                ofNoFill();
                ofSetColor(255, 255, 255, 15);
                ofDrawCircle(0, 0, radius);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        ofSaveScreen("beautiful_spiritual_animation.png");
    }
}
