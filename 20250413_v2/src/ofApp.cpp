#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(120);
    ofSetLineWidth(1.6);

    numParticles = 180;
    timeSpeed =  0.3; // Faster animation speed
    globalRotation = 0.0;
    zoom = 0.9;

    for (int i = 0; i < numParticles; i++) {
        float angle = ofDegToRad((360.0 / numParticles) * i);
        RingParticle p;
        p.baseAngle = angle;

        // Inner ring (tighter for portrait)
        p.baseRadius = 150 + ofNoise(i * 0.1) * 30;
        innerRing.push_back(p);

        // Outer ring
        p.baseRadius = 250 + ofNoise(i * 0.2) * 50;
        outerRing.push_back(p);
    }
}

void ofApp::update(){
    float time = ofGetElapsedTimef() * timeSpeed;

    globalRotation = sin(time * 1.0) * 60.0;
    zoom = 1.0 + 0.08 * sin(time * 1.2);

    for (int i = 0; i < numParticles; i++) {
        float r = innerRing[i].baseRadius
                + sin(time * 2.0 + i * 0.1) * 60.0
                + ofNoise(i * 0.01, time * 2.0) * 60.0;

        innerRing[i].pos.x = ofGetWidth() / 2 + cos(innerRing[i].baseAngle + time * 0.3) * r * zoom;
        innerRing[i].pos.y = ofGetHeight() / 2 + sin(innerRing[i].baseAngle + time * 0.3) * r * zoom;
    }

    for (int i = 0; i < numParticles; i++) {
        float r = outerRing[i].baseRadius
                + cos(time * 1.5 + i * 0.05) * 60.0
                + ofNoise(i * 0.02, time * 1.8) * 70.0;

        outerRing[i].pos.x = ofGetWidth() / 2 + cos(outerRing[i].baseAngle - time * 0.3) * r * zoom;
        outerRing[i].pos.y = ofGetHeight() / 2 + sin(outerRing[i].baseAngle - time * 0.3) * r * zoom;
    }
}

void ofApp::draw(){
    ofBackground(0);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateDeg(globalRotation);
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

    for (int s = 0; s < 9; s++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateDeg(360.0 / 9 * s);
        ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

        for (int i = 0; i < numParticles; i++) {
            float pulse = ofMap(sin(ofGetElapsedTimef() + i * 0.02), -1, 1, 1, 3);
            ofSetColor(255, 140);
            ofDrawCircle(innerRing[i].pos, pulse);
            ofDrawCircle(outerRing[i].pos, pulse * 0.8);

            float d = innerRing[i].pos.distance(outerRing[i].pos);
            if (d < 300) {
                ofSetColor(255, ofMap(d, 0, 300, 255, 0));
                ofDrawLine(innerRing[i].pos, outerRing[i].pos);
            }

            if (i % 5 == 0) {
                int next = (i + 5) % numParticles;
                ofSetColor(255, 35);
                ofDrawBezier(
                    innerRing[i].pos.x, innerRing[i].pos.y,
                    innerRing[i].pos.x, innerRing[i].pos.y - 60,
                    outerRing[next].pos.x, outerRing[next].pos.y + 60,
                    outerRing[next].pos.x, outerRing[next].pos.y
                );
            }
        }

        ofPopMatrix();
    }

    ofPopMatrix();
}
