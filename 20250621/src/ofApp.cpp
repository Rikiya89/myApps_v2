#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetSmoothLighting(true);

    int numPoints = 200;
    float radius = 300;
    for (int i = 0; i < numPoints; i++) {
        float angle = ofMap(i, 0, numPoints, 0, TWO_PI);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        float z = ofRandom(-radius, radius);
        points.push_back(ofVec3f(x, y, z));
    }

    time = 0;
}

void ofApp::update() {
    time += ofGetLastFrameTime();
}

void ofApp::draw() {
    cam.begin();

    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 25);
    ofDrawRectangle(-ofGetWidth()/2, -ofGetHeight()/2, ofGetWidth(), ofGetHeight());

    ofRotateYDeg(sin(time * 0.5) * 5); // subtle camera drift

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);

    for (int i = 0; i < points.size(); i++) {
        float alpha = 180 * pow((sin(i * 0.08 + time * 2.0) + 1.0) * 0.5, 2.0);
        float hue = fmod(i * 1.5 + time * 30, 255);
        ofColor color = ofColor::fromHsb(hue, 200, 255, alpha);

        mesh.addVertex(points[i]);
        mesh.addColor(color);

        if (i > 0) {
            mesh.addVertex(points[i - 1]);
            mesh.addColor(color);
        }

        float baseScale = ofMap(sin(i * 0.15 + time), -1, 1, 2.0, 5.0);
        float pulsate = ofMap(sin(time * 3.0 + i), -1, 1, 0.8, 1.2);
        float scale = baseScale * pulsate;

        ofEnableBlendMode(OF_BLENDMODE_ADD); // glow effect
        ofSetColor(ofColor::fromHsb(hue, 180, 255, alpha));
        ofDrawSphere(points[i], scale);

        // Glow ring
        ofPushMatrix();
        ofTranslate(points[i]);
        ofRotateYDeg(time * 30 + i);
        ofRotateXDeg(time * 15 + i);
        ofNoFill();
        ofSetLineWidth(1.5);
        ofSetColor(ofColor::fromHsb(hue, 80, 255, alpha * 0.5));
        ofDrawCircle(0, 0, scale * 2.5);
        ofPopMatrix();

        // Ico wire
        ofNoFill();
        ofSetLineWidth(1.0);
        ofSetColor(ofColor::fromHsb(hue, 100, 255, alpha * 0.8));
        ofDrawIcoSphere(points[i], scale * 1.5);
        ofFill();
        ofDisableBlendMode();
    }

    mesh.draw();

    cam.end();
}
