#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    rotationSpeed = 0.02; // Very slow rotation for subtle motion

    // Set up lighting
    light.setPointLight();
    light.setPosition(300, 300, 300);

    // Setup primary mesh as a detailed sphere
    mesh = ofSpherePrimitive(100, 160).getMesh(); // Very high resolution
    secondaryMesh = ofIcoSpherePrimitive(110, 3).getMesh(); // More detail
    tertiaryMesh = ofConePrimitive(90, 200, 16, 16).getMesh(); // Correcting the cone initialization with proper segments

    for (auto& vert : mesh.getVertices()) {
        mesh.addColor(ofColor(0));  // Initial color
    }
    for (auto& vert : secondaryMesh.getVertices()) {
        secondaryMesh.addColor(ofColor(0));  // Initial color
    }
    for (auto& vert : tertiaryMesh.getVertices()) {
        tertiaryMesh.addColor(ofColor(0));  // Initial color
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    updateMesh(mesh, time, 0.06, 6.0f); // Different noise and displacement
    updateMesh(secondaryMesh, time, 0.04, 4.0f);
    updateMesh(tertiaryMesh, time, 0.02, 2.0f); // Least displacement for the cone
}

void ofApp::updateMesh(ofMesh& meshToUpdate, float time, float noiseScale, float displacementScale) {
    for (size_t i = 0; i < meshToUpdate.getVertices().size(); i++) {
        glm::vec3& vertRef = meshToUpdate.getVertices()[i];
        float noise = ofNoise(vertRef.x * noiseScale, vertRef.y * noiseScale, vertRef.z * noiseScale, time * 0.5);
        vertRef = meshToUpdate.getVertex(i) + glm::normalize(vertRef) * ((noise - 0.5f) * displacementScale);

        // More complex color dynamics
        float hue = ofMap(noise, 0, 1, 0, 255);
        float brightness = 128 + 127 * sin(time * 0.1 + i * 0.005);
        meshToUpdate.setColor(i, ofColor::fromHsb(hue, 255, brightness));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
    ofEnableDepthTest();

    // Enable lighting
    light.enable();
    ofPushMatrix();

    // Oscillating rotation
    float angle = sin(ofGetElapsedTimef() * rotationSpeed) * 180;
    ofRotateYDeg(angle);

    // Draw the meshes with offset rotations for depth
    mesh.drawFaces();
    ofRotateYDeg(120); // Offset rotation
    secondaryMesh.drawWireframe();
    ofRotateYDeg(120); // Further offset
    tertiaryMesh.drawWireframe();

    ofPopMatrix();
    light.disable();

    ofDisableDepthTest();
    easyCam.end();
}
