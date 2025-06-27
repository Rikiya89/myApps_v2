#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(300);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    time = 0.0f;
}

void ofApp::update(){
    time += 0.0125;  // gentle pace for spiritual visuals
}

void ofApp::draw(){
    ofBackground(0, 0, 0, 10); // long trailing glow
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    cam.begin();

    int rings = 60;
    int segments = 240;
    float symmetry = 6.0; // 6-fold symmetry like sacred mandala

    for(int r = 0; r < rings; r++){
        float baseRadius = 60 + r * 6;
        float pulse = sin(time * 1.4 + r * 0.3) * 5;
        float angleShift = TWO_PI * r / symmetry;

        ofBeginShape();
        for(int i = 0; i <= segments; i++){
            float t = ofMap(i, 0, segments, 0, TWO_PI);
            float noiseWave = ofNoise(r * 0.05, i * 0.02, time) * 20;

            float radius = baseRadius + pulse + noiseWave;
            float x = radius * cos(t + angleShift);
            float y = radius * sin(t + angleShift);
            float z = cos(t * 3.5 + r * 0.2 + time * 2.0) * 60;

            float hue = fmod(t * 50 + time * 60, 255);
            ofColor col = ofColor::fromHsb(hue, 180, 255, 160);
            ofSetColor(col);

            ofVertex(x, y, z);
        }
        ofEndShape(true);
    }

    cam.end();
    ofDisableBlendMode();
}
