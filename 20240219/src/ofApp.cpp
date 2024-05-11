#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0); // Set the background to black
    ofEnableDepthTest(); // Enable depth testing for 3D rendering
    cam.setAutoDistance(true); // Re-enable auto distance for easy camera control

    // Setup dynamic lights
    for (int i = 0; i < 3; i++) {
        ofLight light;
        light.enable();
        lights.push_back(light);
    }
}

void ofApp::update(){
    // Light positions can be dynamically updated here if needed
}

void ofApp::draw(){
    cam.begin();

    float time = ofGetElapsedTimef(); // Base time for noise calculations
    int layers = 5;
    float layerDistance = 60;

    for (int k = 0; k < layers; k++) {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                // Calculating noise-based dynamics for position and size
                float xNoise = ofNoise(i * 0.1, j * 0.1, k * 0.1, time * 0.5);
                float yNoise = ofNoise(j * 0.1, k * 0.1, i * 0.1, time * 0.5);
                float zNoise = ofNoise(k * 0.1, i * 0.1, j * 0.1, time * 0.5);
                float radiusNoise = ofNoise(i * 0.1, j * 0.1, k * 0.1, time) * 20 + 10;

                float x = (i - 9) * layerDistance + (xNoise - 0.5) * 100;
                float y = (j - 9) * layerDistance + (yNoise - 0.5) * 100;
                float z = (k - 2.5) * layerDistance + (zNoise - 0.5) * 100;

                // Color modulation based on Perlin noise
                ofColor sphereColor;
                sphereColor.setHsb((ofNoise(i * 0.1, j * 0.1, time) * 64 + 128),
                                   255,
                                   255);
                ofSetColor(sphereColor);
                
                ofDrawSphere(x, y, z, radiusNoise);
            }
        }
    }

    cam.end();
}
