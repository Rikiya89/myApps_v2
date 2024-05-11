#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    
    light.setup();
    light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 600);
    light.setDiffuseColor(ofColor(255, 255, 255));
    light.setSpecularColor(ofColor(255, 255, 255));

    ambientLight.setup();
    ambientLight.setAmbientColor(ofColor(60, 60, 60));
    
    radius = 300;
    noiseFactor = 0;

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableIndices();

    auto resolution = 200;  // Increased resolution for finer details
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            float x = radius * sin(i * TWO_PI / resolution) * cos(j * TWO_PI / resolution);
            float y = radius * sin(i * TWO_PI / resolution) * sin(j * TWO_PI / resolution);
            float z = radius * cos(i * TWO_PI / resolution);
            mesh.addVertex(ofPoint(x, y, z));

            // Assign a more harmonious color gradient
            float hue = ofMap(i, 0, resolution, 0, 255);
            colors.push_back(ofColor::fromHsb(hue, 255, 255));
        }
    }
}

void ofApp::update(){
    noiseFactor += 0.01;
    for (auto& vertex : mesh.getVertices()) { // Use auto& for automatic type deduction
        float noise = ofNoise(vertex.x * 0.005, vertex.y * 0.005, vertex.z * 0.005, noiseFactor);
        vertex.x += (ofNoise(noise) - 0.5) * 5.0;
        vertex.y += (ofNoise(noise) - 0.5) * 5.0;
        vertex.z += (ofNoise(noise) - 0.5) * 5.0;
    }
}

void ofApp::draw(){
    easyCam.begin();
    ofEnableDepthTest();
    light.enable();
    ambientLight.enable();
    ofEnableLighting();
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        ofSetColor(colors[i]);
        ofDrawSphere(mesh.getVertices()[i], 2);
    }
    
    ofDisableLighting();
    ofDisableDepthTest();
    easyCam.end();
}
