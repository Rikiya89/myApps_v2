#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);  // Deep space black
    ofSetColor(255);  // Radiant sacred white
    ofSetLineWidth(1.2);  // Ultra-fine divine lines
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += rotationSpeed;  // Infinite divine rotation
    universeExpansion = 1.0 + 0.1 * sin(ofGetElapsedTimef() * 0.5);  // Cosmic breath expansion
    corePulse = 5.0 + 3.0 * sin(ofGetElapsedTimef() * 3);  // Pulsating sacred core
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();  // Time-based animation
    int numVertices = 1200;  // Ultra-high resolution for sacred geometry

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);  // Center the sacred mandala
    ofScale(universeExpansion, universeExpansion);  // Cosmic breath effect
    ofRotateDeg(rotationAngle);  // Divine rotation

    // Loop through multiple layers of sacred geometry
    for (int layer = 0; layer < numLayers; layer++) {
        float layerRadius = baseRadius + (layer * 20);  // Expanding sacred layers
        float layerAmplitude = amplitude + (layer * 3); // Gradual wave layering

        // Unique frequency shift per layer for motion variations
        float noiseOffset = layer * 0.1;

        ofNoFill();
        ofBeginShape();
        for (int i = 0; i <= numVertices; i++) {
            float angle = ofMap(i, 0, numVertices, 0, TWO_PI);

            // Perlin noise for smooth distortions
            float noiseValue = ofNoise(cos(angle) * 0.4 + noiseOffset,
                                       sin(angle) * 0.4 + noiseOffset,
                                       time * 0.3 + layer * 0.1);

            // Breathing effect (expanding & contracting waves)
            float breath = sin(time * breathSpeed + angle * 14) * 10;

            // Rotating Sacred Spirals (Golden Ratio-based flow)
            float sacredSpiral = sin(angle * 24) * 22;

            // Final radius with all dynamic effects
            float radius = layerRadius + layerAmplitude * noiseValue + breath + sacredSpiral;

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            ofVertex(x, y);
        }
        ofEndShape(true);
    }

    // **Sacred Core (Divine Light) Pulsation**
    ofFill();
    ofDrawCircle(0, 0, corePulse);

    ofPopMatrix();
}
