#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    numParticles = 360;
    baseRadius = 200;
    timeSpeed = TWO_PI / 9.0;

    positions.resize(numParticles);
}

void ofApp::update(){
    float time = ofGetElapsedTimef() * timeSpeed;
    float dynamicRadius = baseRadius + sin(time) * 40.0;

    for (int i = 0; i < numParticles; i++) {
        float angle = ofDegToRad(i);
        float wave = sin(time + i * 0.1) * 50.0;
        float r = dynamicRadius + wave;

        positions[i].x = ofGetWidth() / 2 + r * cos(angle);
        positions[i].y = ofGetHeight() / 2 + r * sin(angle);
    }
}

void ofApp::draw(){
    ofBackground(0);
    float time = ofGetElapsedTimef() * timeSpeed;
    float rotation = ofMap(time, 0, TWO_PI, 0, 360); // rotate full in 15s

    for (int s = 0; s < 6; s++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateDeg(60 * s + rotation);
        ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

        // Glow layer
        for (int i = 0; i < numParticles; i++) {
            float size = 1.5 + 1.2 * sin(time + i * 0.15);
            ofSetColor(255, 100);
            ofDrawCircle(positions[i], size * 1.5);
        }
        ofPopMatrix();
    }

    for (int s = 0; s < 6; s++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateDeg(60 * s + rotation);
        ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

        for (int i = 0; i < numParticles; i++) {
            float size = 1.5 + 1.2 * sin(time + i * 0.15);
            ofSetColor(255, 200);
            ofDrawCircle(positions[i], size);

            for (int j = i + 5; j < numParticles; j += 15) {
                float dist = positions[i].distance(positions[j]);
                if (dist < 160) {
                    ofSetLineWidth(0.5 + 1.0 * sin(time + j * 0.05));
                    ofSetColor(255, ofMap(dist, 0, 160, 255, 0));
                    ofDrawLine(positions[i], positions[j]);
                }
            }
        }
        ofPopMatrix();
    }
}
