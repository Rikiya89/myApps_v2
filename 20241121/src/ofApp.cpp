#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0); // Black background
    cam.setDistance(1000); // Set the camera's initial distance
    ofEnableDepthTest(); // Enable depth testing for 3D rendering
    ofEnableAlphaBlending(); // Enable transparency blending

    // Setup point light for glow effect
    pointLight.setDiffuseColor(ofColor(255, 150, 200)); // Soft pink light
    pointLight.setSpecularColor(ofColor(255, 255, 255)); // Specular highlights
    pointLight.setPosition(0, 0, 800);

    // Load audio
    soundPlayer.load("creative-technology-showreel-241274.mp3"); // Replace with your audio file
    soundPlayer.setLoop(true);
    soundPlayer.play();

    // Initialize FFT
    fftSmoothed.resize(512, 0.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update light position
    pointLight.setPosition(
        sin(ofGetElapsedTimef()) * 300,
        cos(ofGetElapsedTimef()) * 300,
        600
    );

    // Update audio FFT analysis
    float *val = ofSoundGetSpectrum(512); // Analyze audio into 512 bands
    for (int i = 0; i < 512; i++) {
        fftSmoothed[i] *= 0.96f; // Smooth FFT values
        if (fftSmoothed[i] < val[i]) {
            fftSmoothed[i] = val[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin(); // Start 3D camera view

    // Enable lighting
    pointLight.enable();

    float time = ofGetElapsedTimef(); // Get elapsed time
    int numParticles = 300; // Number of particles
    float radius = 500;     // Radius of 3D particle system

    for (int i = 0; i < numParticles; i++) {
        // Orbital motion using FFT to control particle positions
        float angle = ofDegToRad(i * 360.0 / numParticles + time * 20); // Rotating effect
        float audioFactor = fftSmoothed[i % 512] * 400; // React to audio frequencies
        float x = (radius + audioFactor) * sin(angle) * cos(angle * 2 + time * 0.5);
        float y = (radius + audioFactor) * cos(angle * 3 + time * 0.8);
        float z = (radius + audioFactor) * sin(angle * 4 + time * 0.3);

        float size = ofNoise(i * 0.2, time * 0.5) * 15 + 5; // Dynamic particle size

        // Dynamic glowing colors using HSB
        ofColor color;
        color.setHsb(fmod(time * 30 + i * 5, 255), 200, 255);
        ofSetColor(color, 200); // Add transparency for glow effect

        // Draw glowing sphere
        ofPushMatrix();
        ofTranslate(x, y, z);
        ofDrawSphere(size); // Draw 3D sphere
        ofPopMatrix();

        // Particle trails
        ofSetColor(color, 100); // Lighter color for trails
        ofDrawLine(x, y, z, x * 0.8, y * 0.8, z * 0.8);
    }

    pointLight.disable(); // Disable light after drawing
    cam.end(); // End 3D camera view
}
