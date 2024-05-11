#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0); // Set the background to black
    gui.setup(); // Setup the GUI
    gui.add(speed.set("Speed", 0.04, 0.01, 0.1));
    gui.add(numParticles.set("Num Particles", 2000, 1000, 4000));
    gui.add(startColor.set("Start Color", ofColor(127, 0, 255), ofColor(0), ofColor(255)));
    gui.add(endColor.set("End Color", ofColor(0, 255, 255), ofColor(0), ofColor(255)));
    gui.add(size.set("Size", 1.0, 0.5, 3.0));

    particles.resize(numParticles);
    for(auto &particle : particles) {
        resetParticle(particle);
    }
}

void ofApp::update(){
    for(auto &particle : particles) {
        if(!particle.alive) continue;

        particle.position += particle.velocity * speed;
        particle.lifeTime -= ofGetLastFrameTime();
        if(particle.lifeTime <= 0) {
            resetParticle(particle);
        }
    }
}

void ofApp::draw(){
    easyCam.begin();
    for(auto &particle : particles) {
        if(!particle.alive) continue;

        float lifeRatio = particle.lifeTime / 255.0;
        ofColor color = startColor.get().getLerped(endColor.get(), 1 - lifeRatio);
        ofSetColor(color);

        ofDrawSphere(particle.position, size * ofNoise(particle.position.x * 0.05, particle.position.y * 0.05, ofGetElapsedTimef()));
    }
    easyCam.end();

    gui.draw();
}

void ofApp::resetParticle(Particle &particle) {
    particle.position = ofVec3f(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
    particle.velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    particle.lifeTime = ofRandom(2, 5); // LifeTime now in seconds
    particle.alive = true;
}
