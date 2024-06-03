#include "ofApp.h"

void ofApp::setup() {
    image.load("eye.jpg");

    mesh.setMode(OF_PRIMITIVE_POINTS);

    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            ofColor color = image.getColor(x, y);
            float brightness = color.getBrightness();
            float z = ofMap(brightness, 0, 255, -100, 100); // Map brightness to depth

            ofVec3f position(x - image.getWidth() / 2, y - image.getHeight() / 2, z);
            mesh.addVertex(position);
            mesh.addColor(color);
            originalVertices.push_back(position);
        }
    }

    ofEnableDepthTest();
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    for (int i = 0; i < originalVertices.size(); ++i) {
        ofVec3f vertex = originalVertices[i];
        float wave = sin(vertex.x * 0.05 + time) * 20.0;
        vertex.z += wave;
        mesh.setVertex(i, vertex);
    }
}

void ofApp::draw() {
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateYDeg(ofGetElapsedTimef() * 10); // Rotate the point cloud

    glPointSize(2); // Set point size
    mesh.draw();

    ofPopMatrix();
}
