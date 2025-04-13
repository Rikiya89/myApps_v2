#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowShape(720, 1280);
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    // Sacred Geometry (Seed of Life structure)
    int numLayers = 4;
    float baseRadius = 150;
    int numSpheres = 6;

    for (int layer = 0; layer < numLayers; layer++) {
        float layerRadius = baseRadius + layer * 80;
        for (int i = 0; i < numSpheres; i++) {
            float angle = ofMap(i, 0, numSpheres, 0, TWO_PI);
            float x = cos(angle) * layerRadius;
            float y = sin(angle) * layerRadius;
            float z = ofRandom(-70, 70);

            spherePositions.push_back(ofVec3f(x, y, z));
        }
        numSpheres += 6; // Increase sphere count for complexity
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    float time = ofGetElapsedTimef();

    // Animate spheres in a toroidal motion
    for (size_t i = 0; i < spherePositions.size(); i++) {
        spherePositions[i].z = sin(time + i * 0.2) * 40;
        spherePositions[i].x += cos(time * 0.5 + i * 0.1) * 0.5;
        spherePositions[i].y += sin(time * 0.5 + i * 0.1) * 0.5;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin();

    float time = ofGetElapsedTimef();
    ofSetLineWidth(2);

    // 🌞 Draw Central Core Sphere (pulsating divine source)
    ofSetColor(255);
    float coreSize = 25 + sin(time * 2) * 5;
    ofDrawSphere(0, 0, 0, coreSize);

    // 🌌 Draw the rotating energy ring (halo)
    ofNoFill();
    ofSetColor(255, 255, 255, 180);
    ofPushMatrix();
    ofRotateXDeg(time * 20);
    ofRotateYDeg(time * 30);
    ofDrawCircle(0, 0, 60 + sin(time) * 10);
    ofPopMatrix();
    ofFill();

    // ✨ Draw Sacred Geometry Spheres with Radiance
    for (size_t i = 0; i < spherePositions.size(); i++) {
        float glow = ofMap(sin(time + i * 0.1), -1, 1, 150, 255);
        ofSetColor(glow);
        ofDrawSphere(spherePositions[i], 12);

        // ✨ Draw Rotating Halos around spheres
        ofNoFill();
        ofSetColor(255, 255, 255, glow * 0.8);
        ofPushMatrix();
        ofTranslate(spherePositions[i]);
        ofRotateXDeg(time * 40);
        ofRotateYDeg(time * 20);
        ofDrawCircle(0, 0, 20);
        ofPopMatrix();
        ofFill();
    }

    // 🌠 Draw Cosmic Energy Lines
    for (size_t i = 0; i < spherePositions.size(); i++) {
        for (size_t j = i + 1; j < spherePositions.size(); j++) {
            float dist = spherePositions[i].distance(spherePositions[j]);
            if (dist < 200) {
                float alpha = ofMap(dist, 0, 200, 255, 50);
                ofSetColor(200, 200, 255, alpha);
                ofDrawLine(spherePositions[i], spherePositions[j]);
            }
        }
    }

    cam.end();
}
