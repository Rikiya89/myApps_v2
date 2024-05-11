#include "ofApp.h"

void ofApp::setup() {
    gridWidth = 60; // Adjust grid width for optimal detail
    gridHeight = 60; // Adjust grid height as well
    cellSize = 30; // Set cell size
    ofSetFrameRate(60);
    ofSetCircleResolution(50); // Increase the resolution of the circles for a smoother look
}

void ofApp::update() {
    // The main logic is still in the draw function for simplicity
}

void ofApp::draw() {
    ofBackground(15); // Darker background for better contrast
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Enable blend mode for overlapping colors

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            float noiseScale = 0.05; // Scale for noise to control granularity
            float timeScale = 0.1; // Scale for time to adjust the speed of the animation
            float noiseVal = ofNoise(i * noiseScale, j * noiseScale, ofGetElapsedTimef() * timeScale);

            // Calculate color based on Perlin noise
            ofColor color;
            color.setHsb(noiseVal * 255, 180, 255);
            ofSetColor(color);

            // Determine the radius of each circle based on noise
            float radius = cellSize * noiseVal;

            // Create wave-like movement for each circle
            float waveAmplitude = 5; // Amplitude of the wave movement
            float waveFrequency = 0.5; // Frequency of the wave movement
            float xMovement = sin(ofGetElapsedTimef() * waveFrequency + i * 0.1) * waveAmplitude;
            float yMovement = cos(ofGetElapsedTimef() * waveFrequency + j * 0.1) * waveAmplitude;

            // Draw each circle with a gradient effect
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            glm::vec3 center = glm::vec3(i * cellSize + cellSize / 2 + xMovement, j * cellSize + cellSize / 2 + yMovement, 0);
            mesh.addVertex(center);
            mesh.addColor(ofColor(color, 255)); // Center is fully opaque
            for (int k = 0; k <= 360; k += 10) {
                glm::vec3 vertex = center + glm::vec3(radius * cos(ofDegToRad(k)), radius * sin(ofDegToRad(k)), 0);
                mesh.addVertex(vertex);
                mesh.addColor(ofColor(color, 0)); // Outer vertices are transparent
            }
            mesh.draw();

            // Connect this circle to its right neighbor with a rotating line
            if (i < gridWidth - 1) {
                float rotation = sin(ofGetElapsedTimef() * waveFrequency + i * 0.15) * 45; // Rotate lines over time
                float nextNoiseVal = ofNoise((i + 1) * noiseScale, j * noiseScale, ofGetElapsedTimef() * timeScale);
                glm::vec3 nextCenter = glm::vec3((i + 1) * cellSize + cellSize / 2 + xMovement, j * cellSize + cellSize / 2 + yMovement, 0);
                ofSetColor(color);
                ofPushMatrix();
                ofTranslate(center.x, center.y);
                ofRotateZDeg(rotation);
                ofDrawLine(glm::vec3(0, 0, 0), nextCenter - center);
                ofPopMatrix();
            }
        }
    }
    ofDisableBlendMode(); // Disable blend mode after drawing
}
