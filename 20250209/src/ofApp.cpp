#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();

    mesh = ofMesh::icosphere(200, sphereResolution); // Sacred geometry base

    shader.load("shader.vert", "shader.frag"); // Load shaders
}

void ofApp::update() {
    timeOffset += 0.015; // Slow evolution

    for (auto &vertex : mesh.getVertices()) {
        glm::vec3 original = glm::normalize(vertex) * 200.0f;

        // Apply Perlin noise for fluid motion
        float noise = ofNoise(original.x * noiseFactor, original.y * noiseFactor, original.z * noiseFactor, timeOffset);
        float displacement = ofMap(noise, 0, 1, -50, 50);

        // Pulsating waves inspired by sacred geometry
        float wave = sin(original.x * 0.02 + timeOffset) * cos(original.y * 0.02 + timeOffset) * 25;

        vertex = original + glm::normalize(original) * (displacement + wave);
    }
}

void ofApp::draw() {
    cam.begin();

    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform3f("colorA", colorA);
    shader.setUniform3f("colorB", colorB);

    mesh.drawWireframe(); // Glowing energy effect

    shader.end();

    cam.end();
}

void ofApp::keyPressed(int key) {
    if (key == 'r') {
        noiseFactor = ofRandom(0.1, 0.25); // Randomize shape
    } else if (key == '1') {
        colorA = glm::vec3(1.0, 0.5, 1.0); // Purple-Pink
        colorB = glm::vec3(0.1, 0.8, 1.0); // Blue-Cyan
    } else if (key == '2') {
        colorA = glm::vec3(1.0, 0.8, 0.2); // Gold Energy
        colorB = glm::vec3(0.8, 0.3, 0.1); // Fiery Red
    }
}
