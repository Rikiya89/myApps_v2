#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    easyCam.enableMouseInput();

    numParticles = 500;
    phase.resize(numParticles);
    meshWaveAmplitude = 50.0;  // Initialize the amplitude of mesh wave

    for (int i = 0; i < numParticles; i++) {
        particles.push_back(ofVec3f(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500)));
        ofColor c;
        c.setHsb(ofRandom(255), 255, 200);
        colors.push_back(c);
        phase[i] = ofRandom(TWO_PI);  // Random phase for each particle
    }

    backgroundMesh.setMode(OF_PRIMITIVE_LINES);
    for (int i = 0; i < 1000; i++) {
        float x = ofRandom(-1000, 1000);
        float y = ofRandom(-1000, 1000);
        float z = ofRandom(-500, 500);
        backgroundMesh.addVertex(ofVec3f(x, y, z));
        backgroundMesh.addColor(ofColor(255, 255, 255, 50));  // Slight transparency for depth
    }

    post.init(ofGetWidth(), ofGetHeight());
    auto bloom = post.createPass<BloomPass>();  // Create and store the bloom pass
    bloom->setEnabled(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    time += ofGetLastFrameTime();
    for (int i = 0; i < numParticles; i++) {
        float sizePulse = sin(time + phase[i]) * 0.5 + 1;  // Oscillates between 0.5 and 1.5
        particles[i].z = 100 * sin(time * 0.5 + phase[i]);  // Simple Z-axis oscillation
    }

    // Update background mesh vertices for wave effect
    for (int i = 0; i < backgroundMesh.getNumVertices(); i++) {
        ofVec3f vertex = backgroundMesh.getVertex(i);
        float wave = sin(vertex.x * 0.01 + time) * meshWaveAmplitude;
        vertex.z = wave;
        backgroundMesh.setVertex(i, vertex);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    post.begin(easyCam);

    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // Draw background mesh with wave animation
    backgroundMesh.drawWireframe();

    for (int i = 0; i < numParticles; i++) {
        float size = ofMap(particles[i].distance(ofVec3f(0, 0, 0)), 0, 500, 10, 3);
        ofSetColor(colors[i]);
        ofDrawSphere(particles[i], size * (sin(time + phase[i]) * 0.5 + 1));  // Apply pulsating size effect
    }

    ofDisableBlendMode();

    post.end();
}
