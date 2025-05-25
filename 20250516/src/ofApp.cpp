#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofEnableAlphaBlending();

    gridSize = 8;
    spacing = 60.0f;
    time = 0.0f;

    ofSetWindowTitle("✨ Sacred Galaxy 3D Animation ✨");
}

void ofApp::update() {
    time += 0.015;
}

void ofApp::draw() {
    ofBackgroundGradient(ofColor(0, 0, 20), ofColor(5, 0, 50), OF_GRADIENT_CIRCULAR);

    cam.begin();

    // 🌐 Global scene rotation
    float globalYRot = time * 20;
    float globalXRot = sin(time * 0.5) * 10;
    ofRotateYDeg(globalYRot);
    ofRotateXDeg(globalXRot);

    for (int x = -gridSize; x <= gridSize; x++) {
        for (int y = -gridSize; y <= gridSize; y++) {
            for (int z = -gridSize; z <= gridSize; z++) {
                glm::vec3 pos(x * spacing, y * spacing, z * spacing);

                float n = ofNoise(x * 0.1, y * 0.1, z * 0.1, time);
                float floatOffset = sin(time * 2 + (x + y + z) * 0.15) * 10;
                float breathing = ofMap(sin(time * 1.2 + (x + y + z)), -1, 1, 0.7, 1.4);
                float orbit = ofMap(sin(time + x * 0.1 + y * 0.1), -1, 1, -10, 10);

                glm::vec3 animatedPos = pos + glm::vec3(
                    sin(time + x * 0.2 + y * 0.1) * orbit,
                    floatOffset,
                    cos(time + y * 0.2 + z * 0.1) * orbit
                );

                float size = ofMap(n, 0, 1, 10, 28) * breathing;
                float distFromCenter = glm::length(pos);
                float hue = fmod(distFromCenter * 0.1 + time * 30, 255);

                ofPushMatrix();
                ofTranslate(animatedPos);
                ofRotateXDeg(time * 30 + x * 2);
                ofRotateYDeg(time * 40 + y * 3);
                ofRotateZDeg(time * 50 + z * 4);

                ofColor c = ofColor::fromHsb(hue, 200, 255);
                ofSetColor(c, 230);
                ofDrawBox(size);

                // ghost trail
                ofNoFill();
                ofSetColor(c, 40);
                ofScale(1.1);
                ofDrawBox(size + 6);
                ofFill();

                ofPopMatrix();
            }
        }
    }

    cam.end();
}
