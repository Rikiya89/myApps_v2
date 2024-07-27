#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();

    sphereMesh = ofMesh::sphere(200, 30); // Reduced resolution for performance
    originalVertices = sphereMesh.getVertices();
    time = 0.0;

    // Initialize trails
    trails.resize(sphereMesh.getNumVertices());

    // Setup first light
    light1.setPosition(300, 300, 600);
    light1.setDiffuseColor(ofFloatColor(0.8, 0.8, 1.0));
    light1.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    light1.enable();

    // Setup second light
    light2.setPosition(-300, -300, 600);
    light2.setDiffuseColor(ofFloatColor(1.0, 0.8, 0.8));
    light2.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    light2.enable();

    // Setup material properties
    material.setShininess(64);
    material.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update() {
    time += 0.01;
    int i = 0;
    for (auto &vertex : sphereMesh.getVertices()) {
        glm::vec3 originalVertex = originalVertices[i++];
        glm::vec3 normalizedVertex = glm::normalize(originalVertex);
        float noise = ofNoise(normalizedVertex.x * 0.1, normalizedVertex.y * 0.1, normalizedVertex.z * 0.1, time);
        float oscillation = sin(time * 5.0 + glm::length(originalVertex) * 0.1) * 5.0;
        glm::vec3 newVertex = normalizedVertex * (200 + noise * 100 + oscillation);
        vertex = newVertex;

        // Update trails
        trails[i - 1].push_back(newVertex);
        if (trails[i - 1].size() > maxTrailLength) {
            trails[i - 1].erase(trails[i - 1].begin());
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawVertexEffects(const glm::vec3 &vertex, float colorValue) {
    // Draw small sphere at vertex
    ofSetColor(0, colorValue, 255 - colorValue, 200);
    ofDrawSphere(vertex, 3);

    // Glow effect
    ofSetColor(0, colorValue, 255 - colorValue, 50);
    ofDrawSphere(vertex, 8);

    // Additional visual effects
    ofSetColor(255, 255, 255, 50);
    ofDrawLine(vertex, vertex * 1.1);
}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin();

    ofEnableLighting();
    material.begin();

    // Rotate the sphere
    ofRotateDeg(time * 10, 0.5, 1.0, 0.3);

    ofSetColor(255, 150); // Set white color with some transparency
    sphereMesh.drawWireframe();

    for (int i = 0; i < sphereMesh.getNumVertices(); ++i) {
        auto &vertex = sphereMesh.getVertices()[i];
        float colorValue = ofMap(ofNoise(vertex.x * 0.1, vertex.y * 0.1, vertex.z * 0.1, time), 0, 1, 0, 255);
        drawVertexEffects(vertex, colorValue);

        // Draw trails
        for (size_t j = 1; j < trails[i].size(); ++j) {
            ofSetColor(0, colorValue, 255 - colorValue, ofMap(j, 0, trails[i].size(), 0, 150));
            ofDrawLine(trails[i][j - 1], trails[i][j]);
        }
    }

    material.end();
    ofDisableLighting();

    cam.end();
}
