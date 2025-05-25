#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(10);
    ofEnableDepthTest();
    ofEnableAlphaBlending();  // for transparency
    gridSize = 6;  // initial grid size
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    gridSize = 4 + sin(time * 0.5) * 2.0;  // oscillates between 2 and 6
}

void ofApp::draw() {
    cam.begin();

    ofPushMatrix();
    ofRotateDeg(ofGetElapsedTimef() * 10, 0, 1, 0);  // slow rotation around Y axis

    float time = ofGetElapsedTimef();
    int spacing = 25;

    for (int x = -gridSize; x <= gridSize; x++) {
        for (int y = -gridSize; y <= gridSize; y++) {
            for (int z = -gridSize; z <= gridSize; z++) {

                glm::vec3 pos(x * spacing, y * spacing, z * spacing);

                float noise = ofNoise(x * 0.1, y * 0.1, z * 0.1, time * 0.4);
                float size = ofMap(noise, 0, 1, 2, 12);

                float offsetX = ofSignedNoise(x * 0.1, time * 0.2) * 10;
                float offsetY = ofSignedNoise(y * 0.1, time * 0.2) * 10;
                float offsetZ = ofSignedNoise(z * 0.1, time * 0.2) * 10;

                float hue = fmod(sin(time + x * 0.1 + y * 0.1 + z * 0.1) * 128 + 128, 255);
                ofColor color = ofColor::fromHsb(hue, 200, 255);
                ofSetColor(color, 180);  // semi-transparent

                int shapeType = (int)(time * 0.5) % 3;

                // Primary object
                ofPushMatrix();
                ofTranslate(pos.x + offsetX, pos.y + offsetY, pos.z + offsetZ);
                ofRotateDeg(ofSignedNoise(x, y, z, time) * 360, x % 2, y % 2, z % 2);
                switch (shapeType) {
                    case 0: ofDrawBox(size); break;
                    case 1: ofDrawSphere(size * 0.6); break;
                    case 2: ofDrawCone(size * 0.5, size * 1.5); break;
                }
                ofPopMatrix();

                // Mirrored object
                ofPushMatrix();
                ofTranslate(-pos.x - offsetX, pos.y + offsetY, pos.z + offsetZ);
                ofRotateDeg(ofSignedNoise(x + 1, y + 1, z + 1, time) * 360, (x + 1) % 2, (y + 1) % 2, (z + 1) % 2);
                switch (shapeType) {
                    case 0: ofDrawBox(size); break;
                    case 1: ofDrawSphere(size * 0.6); break;
                    case 2: ofDrawCone(size * 0.5, size * 1.5); break;
                }
                ofPopMatrix();
            }
        }
    }

    ofPopMatrix();
    cam.end();
}
