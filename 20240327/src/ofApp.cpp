#include "ofApp.h"

// Define a simple particle class
class Particle {
public:
    ofPoint pos;
    ofColor color;
    float radius;
    ofVec2f velocity;

    Particle() {
        pos = ofPoint(ofRandomWidth(), ofRandomHeight());
        radius = ofRandom(2, 5);
        velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
        color = ofColor::fromHsb(ofRandom(255), 180, 230);
    }

    void move() {
        pos += velocity;
        // Simple boundary conditions
        if (pos.x < 0 || pos.x > ofGetWidth()) velocity.x *= -1;
        if (pos.y < 0 || pos.y > ofGetHeight()) velocity.y *= -1;
    }

    void draw() {
        ofSetColor(color);
        ofDrawCircle(pos, radius);
    }
};

std::vector<Particle> particles;

void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    ofSetCircleResolution(50);  // Medium resolution for faster rendering
    ofEnableSmoothing();
    ofSetFrameRate(60);

    // Initialize particles
    for (int i = 0; i < 100; i++) {
        particles.emplace_back();
    }
}

void ofApp::update(){
    // Update particles
    for (auto& particle : particles) {
        particle.move();
    }
}

void ofApp::draw(){
    // Dynamic background based on time
    ofColor centerColor = ofColor::fromHsb(fmod(ofGetElapsedTimef() * 10, 255), 200, 200);
    ofColor edgeColor = ofColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    float baseRadius = 25;
    int layers = 5;
    float offsetX = ofGetWidth() / 2;
    float offsetY = ofGetHeight() / 2;

    // Draw the Flower of Life
    for (int layer = 0; layer <= layers; layer++) {
        int numberOfCircles = layer == 0 ? 1 : 6 * layer;
        for (int i = 0; i < numberOfCircles; i++) {
            float angle = TWO_PI / numberOfCircles * i;
            float x = offsetX + layer * baseRadius * cos(angle) * 1.5;
            float y = offsetY + layer * baseRadius * sin(angle) * 1.5;
            float radius = baseRadius + 5 * cos(ofGetElapsedTimef() + layer);
            ofColor color = ofColor::fromHsb(fmod(ofGetElapsedTimef() * 20 + layer * 10, 255), 255, 255, 120);
            ofSetColor(color);
            ofDrawCircle(x, y, radius);
        }
    }

    // Draw particles
    for (auto& particle : particles) {
        particle.draw();
    }
}

void ofApp::mouseMoved(int x, int y ){
    // Update particle colors based on mouse position
    for (auto& particle : particles) {
        float hue = ofMap(x, 0, ofGetWidth(), 0, 255);
        particle.color.setHsb(hue, 255, 230);
    }
}
