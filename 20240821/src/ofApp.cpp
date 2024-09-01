#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);

    // Setup the fluid simulation
    fluid.allocate(ofGetWidth(), ofGetHeight(), 0.5);
    fluid.dissipation = 0.98;
    fluid.velocityDissipation = 0.98;
    fluid.setGravity(ofVec2f(0.0, 0.0));

    // Initialize color and time
    baseColor = ofColor::fromHsb(ofRandom(255), 255, 255);
    colorChangeSpeed = 0.1;
    time = 0.0;
    audioLevel = 0.0;

    // Setup the particle system
    particleSystem.setup();

    // Setup audio input
    ofSoundStreamSettings settings;
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = 256;
    soundStream.setup(settings);
}

void ofApp::update() {
    // Update color and fluid
    time += colorChangeSpeed;
    baseColor.setHue(fmod(time * 50, 255));
    fluid.update();

    // Update particles
    particleSystem.update();

    // Adjust fluid dynamics based on audio input
    fluid.addTemporalForce(
        ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2),
        ofVec2f(audioLevel * 200, 0), // Create a force proportional to audio level
        baseColor,
        audioLevel * 50,
        audioLevel * 100,
        1.0f
    );
}

void ofApp::draw() {
    // Draw the fluid and particles
    fluid.draw();
    particleSystem.draw();
}

void ofApp::mouseDragged(int x, int y, int button) {
    // Add dynamic forces and particles on mouse drag
    addDynamicForce(x, y);
    addParticles(x, y);
}

void ofApp::audioIn(ofSoundBuffer &input) {
    // Calculate RMS (Root Mean Square) of the audio input
    float rms = 0.0;
    for (size_t i = 0; i < input.getNumFrames(); ++i) {
        rms += input[i] * input[i];
    }
    rms = sqrt(rms / input.getNumFrames());
    audioLevel = ofMap(rms, 0.0, 0.1, 0.0, 1.0, true); // Normalize audio level
}

void ofApp::addDynamicForce(int x, int y) {
    ofVec2f forceDirection(ofRandom(-20, 20), ofRandom(-20, 20));
    fluid.addTemporalForce(
        ofVec2f(x, y),
        forceDirection,
        baseColor,
        ofRandom(5, 15),
        ofRandom(10, 50),
        ofRandom(0.5, 2.0)
    );
}

void ofApp::addParticles(int x, int y) {
    // Create and emit particles following the fluid flow
    for (int i = 0; i < 10; i++) {
        particleSystem.addParticle(
            ofVec2f(x, y),
            ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10)),
            baseColor
        );
    }
}
