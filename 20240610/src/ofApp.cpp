#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    numShapes = 80;
    noiseScale = 0.02;
    colors.resize(numShapes);
    rotationSpeeds.resize(numShapes);
    offsets.resize(numShapes);

    for (int i = 0; i < numShapes; ++i) {
        colors[i] = ofColor::fromHsb(ofRandom(255), 200, 255, 150);
        rotationSpeeds[i] = ofRandom(0.1, 0.5);
        offsets[i] = ofRandom(0, 1000); // Unique offset for each shape
    }
}

void ofApp::update(){
    // No need to update anything in this simple example
}

void ofApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofNoFill();

    for (int i = 0; i < numShapes; ++i) {
        float noiseValue = ofNoise(offsets[i], ofGetElapsedTimef() * 0.1);
        float radius = ofMap(noiseValue, 0, 1, 100, 500);

        ofSetColor(colors[i]);
        ofPushMatrix();
        ofRotateDeg(ofGetElapsedTimef() * rotationSpeeds[i] * 50);

        // Draw dynamic bezier curves
        for (int j = 0; j < 8; ++j) {
            float alpha = ofMap(j, 0, 7, 255, 0);
            ofSetColor(colors[i], alpha);
            ofBeginShape();
            for (int k = 0; k < 360; k += 30) {
                float angle1 = ofDegToRad(k);
                float angle2 = ofDegToRad(k + 30);
                float x1 = cos(angle1) * (radius - j * 5);
                float y1 = sin(angle1) * (radius - j * 5);
                float x2 = cos(angle2) * (radius - j * 5);
                float y2 = sin(angle2) * (radius - j * 5);
                float cp1X = cos(angle1 + 0.5) * (radius - j * 5 + 30);
                float cp1Y = sin(angle1 + 0.5) * (radius - j * 5 + 30);
                float cp2X = cos(angle2 - 0.5) * (radius - j * 5 - 30);
                float cp2Y = sin(angle2 - 0.5) * (radius - j * 5 - 30);
                ofVertex(x1, y1);
                ofBezierVertex(cp1X, cp1Y, cp2X, cp2Y, x2, y2);
            }
            ofEndShape(true);
        }

        ofPopMatrix();
    }
}
