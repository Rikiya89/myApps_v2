#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableAlphaBlending(); // allow transparency
    ofSetLineWidth(1.2);

    // Chakra-style soft color palette
    colors = {
        ofColor(255, 80, 80),    // soft red
        ofColor(255, 160, 80),   // orange
        ofColor(255, 255, 100),  // yellow
        ofColor(100, 255, 150),  // green
        ofColor(100, 200, 255),  // light blue
        ofColor(180, 100, 255),  // purple
        ofColor(255, 100, 200)   // pink
    };
}

void ofApp::update() {
    // Nothing dynamic yet
}

void ofApp::draw() {
    cam.begin();
    ofRotateYDeg(ofGetElapsedTimef() * 5); // slower rotation = more meditative

    float breathing = 1.0 + 0.2 * sin(ofGetElapsedTimef() * 0.5); // slower breathing

    spherePositions.clear(); // Clear and update each frame
    drawSacredGeometry(80, 5, breathing);

    // After drawing spheres, connect them
    for (int i = 0; i < spherePositions.size(); i++) {
        for (int j = i + 1; j < spherePositions.size(); j++) {
            float dist = spherePositions[i].distance(spherePositions[j]);
            if (dist < 150) { // only connect close spheres
                ofSetColor(255, 100); // soft white line
                ofDrawLine(spherePositions[i], spherePositions[j]);
            }
        }
    }

    cam.end();

    // Draw background stars after everything
    drawBackgroundStars();
}

void ofApp::drawSacredGeometry(float radius, int layers, float breathing) {
    for (int layer = 0; layer < layers; layer++) {
        int numSpheres = 6 * (layer + 1);
        float angleStep = 360.0f / numSpheres;
        float layerRadius = radius * (layer + 1) * 0.6 * breathing;

        for (int i = 0; i < numSpheres; i++) {
            float angle = ofDegToRad(i * angleStep);
            float x = cos(angle) * layerRadius;
            float y = sin(angle) * layerRadius;
            float z = sin(ofGetElapsedTimef() + i * 0.4) * 40; // floating z motion

            ofVec3f pos(x, y, z);
            spherePositions.push_back(pos);

            ofPushMatrix();
            ofTranslate(pos);
            ofNoFill();
            ofSetColor(colors[(layer + i) % colors.size()], 180);
            ofDrawSphere(0, 0, 0, radius * 0.4);
            ofPopMatrix();
        }
    }

    // Center sphere
    ofPushMatrix();
    ofNoFill();
    ofSetColor(colors[0], 220);
    ofDrawSphere(0, 0, 0, radius * 0.4);
    ofPopMatrix();
}

void ofApp::drawBackgroundStars() {
    ofPushStyle();
    ofPushMatrix();
    cam.begin();
    ofTranslate(0, 0, -800); // Push stars far behind

    ofSetColor(255, 40);
    for (int i = 0; i < 300; i++) {
        float x = ofRandom(-1000, 1000);
        float y = ofRandom(-1000, 1000);
        float z = ofRandom(-1000, 1000);
        ofDrawCircle(x, y, z, 1);
    }

    cam.end();
    ofPopMatrix();
    ofPopStyle();
}
