#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    radialSteps = 60;   // Like flower petals
    circleSteps = 120;  // Depth of each petal
    radius = 200;
    time = 0.0;

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    for (int i = 0; i < radialSteps; i++) {
        float angle = ofMap(i, 0, radialSteps, 0, TWO_PI);
        for (int j = 0; j < circleSteps; j++) {
            float r = ofMap(j, 0, circleSteps, 0, radius);
            glm::vec3 pos = glm::vec3(r * cos(angle), r * sin(angle), 0);
            mesh.addVertex(pos);
            mesh.addColor(ofFloatColor::fromHsb(0, 1.0, 1.0));
        }
    }

    for (int i = 0; i < radialSteps - 1; i++) {
        for (int j = 0; j < circleSteps - 1; j++) {
            int idx1 = j + i * circleSteps;
            int idx2 = j + (i + 1) * circleSteps;
            int idx3 = j + 1 + i * circleSteps;
            int idx4 = j + 1 + (i + 1) * circleSteps;

            mesh.addIndex(idx1); mesh.addIndex(idx2); mesh.addIndex(idx3);
            mesh.addIndex(idx2); mesh.addIndex(idx4); mesh.addIndex(idx3);
        }
    }
}

void ofApp::update() {
    time += 0.015;

    for (int i = 0; i < radialSteps; i++) {
        float angle = ofMap(i, 0, radialSteps, 0, TWO_PI);
        for (int j = 0; j < circleSteps; j++) {
            int index = j + i * circleSteps;
            float r = ofMap(j, 0, circleSteps, 0, radius);

            float wave = sin(time + r * 0.05 + angle * 3.0) * 30;
            glm::vec3 pos = glm::vec3(
                r * cos(angle),
                r * sin(angle),
                wave
            );

            mesh.setVertex(index, pos);

            float hue = fmod(time * 10 + r * 0.3, 255);
            float brightness = ofMap(wave, -30, 30, 0.4, 1.0);
            mesh.setColor(index, ofFloatColor::fromHsb(hue / 255.0, 0.6, brightness, 0.8));
        }
    }
}

void ofApp::draw() {
    cam.begin();

    ofPushMatrix();
    ofRotateDeg(ofGetElapsedTimef() * 5, 0, 0, 1); // Slow spin

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    mesh.draw();
    ofSetColor(255, 100);
    mesh.drawWireframe();
    ofDisableBlendMode();

    ofPopMatrix();
    cam.end();
}
