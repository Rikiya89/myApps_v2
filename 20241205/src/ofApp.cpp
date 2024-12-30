#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(5); // Dark background
    numLayers = 5;   // Number of nested layers
    baseRadius = 120; // Base radius for parametric shapes
    rotationSpeed = 0.3; // Smooth rotation speed
    time = 0.0; // Animation time

    primaryColor = ofColor(255, 120, 80); // Warm gradient start
    secondaryColor = ofColor(80, 150, 255); // Cool gradient end

    ofEnableDepthTest(); // Enable 3D depth
    ofEnableLighting();  // Enable lighting
    pointLight.setPosition(0, 0, 500); // Initial light position

    // Load and play audio
    soundPlayer.load("creative-technology-showreel-241274.mp3");
    soundPlayer.setLoop(true);
    soundPlayer.play();

    // Initialize FFT
    nBandsToGet = 128; // Number of frequency bands
    fftSmoothed = new float[nBandsToGet];
    for (int i = 0; i < nBandsToGet; ++i) {
        fftSmoothed[i] = 0;
    }

    // Initialize particle system
    int numParticles = 800;
    particleMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int i = 0; i < numParticles; ++i) {
        glm::vec3 pos = glm::vec3(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300));
        particlePositions.push_back(pos);
        particleSpeeds.push_back(ofRandom(0.5, 2.0));
        particleMesh.addVertex(pos);
    }

    ofSetSmoothLighting(true);
}

//--------------------------------------------------------------
void ofApp::update() {
    time += 0.01; // Increment time for animations

    // Get audio spectrum
    float *audioData = ofSoundGetSpectrum(nBandsToGet); // Get current FFT spectrum
    for (int i = 0; i < nBandsToGet; ++i) {
        // Smooth FFT values
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < audioData[i]) {
            fftSmoothed[i] = audioData[i];
        }
    }

    // Update particle positions with FFT
    for (size_t i = 0; i < particlePositions.size(); ++i) {
        glm::vec3 &pos = particlePositions[i];
        float scaleFactor = fftSmoothed[i % nBandsToGet] * 50.0f; // Scale based on audio
        pos += glm::vec3(sin(time) * scaleFactor, cos(time) * scaleFactor, sin(time * 0.5) * scaleFactor);
        particleMesh.setVertex(i, pos);
    }

    // Update light position dynamically
    pointLight.setPosition(cos(time) * 400, sin(time * 0.8) * 400, 300);
}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin(); // Start 3D camera
    pointLight.enable(); // Enable lighting

    // Draw Recursive Fractal Layer
    drawRecursiveLayer(0, 0, 0, baseRadius, numLayers);

    // Draw Particle System
    ofSetColor(255, 255, 255, 80); // Light particles
    particleMesh.draw();

    pointLight.disable(); // Disable lighting
    cam.end(); // End 3D camera
}

//--------------------------------------------------------------
void ofApp::drawRecursiveLayer(float x, float y, float z, float size, int depth) {
    if (depth <= 0) return;

    ofPushMatrix();
    ofTranslate(x, y, z);
    ofRotateDeg(ofGetElapsedTimef() * rotationSpeed * depth, 1.0, 1.0, 0.0);

    float audioScale = fftSmoothed[depth % nBandsToGet] * 50.0f; // Scale geometry with audio

    ofSetColor(primaryColor.getLerped(secondaryColor, float(depth) / numLayers), 200);
    ofDrawSphere(0, 0, 0, size + audioScale);

    for (int i = 0; i < 6; ++i) {
        float angle = ofDegToRad(i * 60);
        float childX = cos(angle) * size * 1.5;
        float childY = sin(angle) * size * 1.5;
        drawRecursiveLayer(childX, childY, z, size * 0.5, depth - 1);
    }

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_UP) {
        numLayers++;
    } else if (key == OF_KEY_DOWN) {
        numLayers = max(3, numLayers - 1);
    } else if (key == 'r') {
        baseRadius += 10.0;
    } else if (key == 'f') {
        baseRadius = max(10.0f, baseRadius - 10.0f);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    float lightX = ofMap(x, 0, ofGetWidth(), -400, 400); // Map mouse x to light position
    float lightY = ofMap(y, 0, ofGetHeight(), -400, 400); // Map mouse y to light position
    pointLight.setPosition(lightX, lightY, 300); // Update light position with mouse movement
}
