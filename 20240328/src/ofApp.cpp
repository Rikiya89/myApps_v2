#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    numberOfPoints = 300;
    for(int i = 0; i < numberOfPoints; i++) {
        points.push_back(ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(-300, 300)));
        speeds.push_back(ofPoint(0, 0, 0));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef() * 0.03; // Further slow down the Perlin noise time factor
    for(size_t i = 0; i < points.size(); i++) {
        float noiseX = ofSignedNoise(time, points[i].y * 0.01, points[i].z * 0.01) * 6;
        float noiseY = ofSignedNoise(points[i].x * 0.01, time, points[i].z * 0.01) * 6;
        float noiseZ = ofSignedNoise(points[i].x * 0.01, points[i].y * 0.01, time) * 6;

        speeds[i] = ofPoint(noiseX, noiseY, noiseZ);
        points[i] += speeds[i];

        if(points[i].x < 0 || points[i].x > ofGetWidth()) points[i].x = ofWrap(points[i].x, 0, ofGetWidth());
        if(points[i].y < 0 || points[i].y > ofGetHeight()) points[i].y = ofWrap(points[i].y, 0, ofGetHeight());
        if(points[i].z < -300 || points[i].z > 300) points[i].z = ofWrap(points[i].z, -300, 300);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60), ofColor(10), OF_GRADIENT_CIRCULAR);

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    // Dynamic connection distance based on a sine wave for a pulsating effect
    float dynamicConnectionDistance = ofMap(sin(ofGetElapsedTimef() * 0.2), -1, 1, 100, 300);

    for(size_t i = 0; i < points.size(); i++) {
        for(size_t j = i + 1; j < points.size(); j++) {
            if(points[i].distance(points[j]) < dynamicConnectionDistance) {
                float alpha = ofMap(points[i].distance(points[j]), 0, dynamicConnectionDistance, 255, 0);
                ofSetColor(255, alpha);
                ofDrawLine(points[i] - ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, 0),
                           points[j] - ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, 0));
            }
        }

        // Pulsating effect on point size
        float size = 3 + 3 * sin(ofGetElapsedTimef() * 0.5 + points[i].z * 0.01);
        ofColor pointColor = ofColor::fromHsb(ofMap(points[i].z, -300, 300, 0, 255), 255, 200);
        ofSetColor(pointColor);
        ofDrawCircle(points[i] - ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, 0), size);
    }

    ofPopMatrix();
}
