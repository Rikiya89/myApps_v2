#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetWindowShape(1080, 1920);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void ofApp::update() {
    // No update needed for now
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    cam.begin();

    float time = ofGetElapsedTimef();
    int numRings = 100;
    float radiusBase = 60.0f;
    float spiralStep = 10.0f;

    for (int i = 0; i < numRings; i++) {
        float angle = time * 10 + i * 15 + 10.0f * sin(time * 0.3 + i * 0.1);
        float spiralRadius = radiusBase + i * spiralStep;
        float x = cos(ofDegToRad(angle)) * spiralRadius;
        float y = sin(ofDegToRad(angle)) * spiralRadius + 20.0f * sin(time * 0.5 + i * 0.2); // gentle float
        float z = i * 12 - fmod(time * 60, numRings * 12) + 15.0f * sin(time * 1.5 + i * 0.3);

        float hue = fmod(time * 8 + i * 4, 255);
        float alpha = ofMap(abs(sin(time * 0.5 + i * 0.2)), 0, 1, 180, 255);

        ofSetColor(ofColor::fromHsb(hue, 180, 255, alpha));

        ofPushMatrix();
        ofTranslate(x, y, z);
        ofRotateYDeg(time * 10 + i * 6);
        ofRotateXDeg(time * 8 + i * 7);

        float pulse = 1.0 + 0.3 * sin(time * 1.5 + i * 0.3);
        ofScale(pulse, pulse, pulse);

        ofNoFill();
        ofSetLineWidth(3.0);

        // Aura layering (brighter)
        for (int j = 0; j < 4; j++) {
            float auraRadius = 25 + 8 * j + 6 * sin(time + i * 0.5 + j);
            ofSetColor(ofColor::fromHsb(hue, 255, 255, 150));
            ofDrawCircle(glm::vec3(0, 0, 0), auraRadius);
        }

        // Additional faint outer halo (more vivid)
        ofSetColor(ofColor::fromHsb(hue, 180, 255, 100));
        ofDrawCircle(glm::vec3(0, 0, 0), 80);

        // Center sphere (already maximum intensity)
        ofFill();
        ofSetColor(ofColor::fromHsb(hue, 255, 255, 255)); // (keep max intensity, no change needed)
        ofDrawSphere(glm::vec3(0, 0, 0), 3.5 + 1.2 * sin(time * 1.8 + i * 0.5));

        ofPopMatrix();
    }

    cam.end();
    ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}
