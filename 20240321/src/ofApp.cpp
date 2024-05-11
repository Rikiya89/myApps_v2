#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    animationPhase = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    animationPhase += 0.02; // Adjust the speed of the animation
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawBackgroundGradient(ofColor(15, 0, 30), ofColor(0, 15, 20));

    float size = 300;
    int levels = 6;
    int layers = 5; // Number of layers

    for (int i = 0; i < layers; i++) {
        float layerPhase = animationPhase + i * 0.15;
        float x = ofGetWidth() / 2 + cos(layerPhase) * 50 - i * 10;
        float y = ofGetHeight() / 2 + sin(layerPhase) * 50 - i * 10;
        float layerSize = size - i * 40;
        drawSeedOfLife(x, y, layerSize, levels, layerPhase);
    }
}

//--------------------------------------------------------------
void ofApp::drawSeedOfLife(float x, float y, float size, int levels, float phase){
    float angle = TWO_PI / levels;
    for (int i = 0; i < levels; i++) {
        float modX = cos(angle * i + phase) * size / 2;
        float modY = sin(angle * i + phase) * size / 2;
        ofSetColor(ofMap(i, 0, levels, 0, 255, true), ofMap(sin(phase), -1, 1, 0, 255, true), ofMap(cos(phase), -1, 1, 0, 255, true), 180);
        ofSetLineWidth(3);
        ofNoFill();
        ofDrawCircle(x + modX, y + modY, size / 2 + sin(ofGetFrameNum() * 0.05 + i) * 15);
    }
}

//--------------------------------------------------------------
void ofApp::drawBackgroundGradient(ofColor innerColor, ofColor outerColor) {
    ofColor color;
    for (int i = 0; i < ofGetHeight(); i++) {
        float ratio = (float)i / (float)ofGetHeight();
        color.r = (1 - ratio) * innerColor.r + ratio * outerColor.r;
        color.g = (1 - ratio) * innerColor.g + ratio * outerColor.g;
        color.b = (1 - ratio) * innerColor.b + ratio * outerColor.b;
        ofSetColor(color);
        ofDrawLine(0, i, ofGetWidth(), i);
    }
}
