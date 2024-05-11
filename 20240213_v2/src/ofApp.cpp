#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
}

void ofApp::update(){
    // Dynamic background
    ofColor bgColor;
    float time = ofGetElapsedTimef();
    bgColor.setHsb(fmod(time * 10, 255), 180, 230);
    ofBackground(bgColor);

    // Update particles
    for(auto& p : particles) {
        p.update();
    }

    // Remove dead particles
    particles.erase(std::remove_if(particles.begin(), particles.end(),
                    [](const Particle& p) { return !p.isAlive(); }), particles.end());

    // Add new particle periodically
    if(ofGetFrameNum() % 15 == 0) {
        addParticle();
    }
}

void ofApp::draw(){
    for(auto& p : particles) {
        ofSetColor(p.color);
        ofDrawCircle(p.position, p.radius);
    }
}

void ofApp::addParticle() {
    glm::vec2 position = glm::vec2(ofRandomWidth(), ofRandomHeight());
    glm::vec2 velocity = glm::vec2(ofRandom(-2, 2), ofRandom(-2, 2));
    float radius = ofRandom(5, 20);
    ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
    particles.push_back(Particle(position, velocity, radius, color));
}
