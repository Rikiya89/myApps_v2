// ofApp.cpp

#include "ofApp.h"

Particle::Particle(float startX, float startY) {
    position.set(startX, startY);
    velocity.set(ofRandom(-1, 1), ofRandom(-1, 1));
    color = ofColor::fromHsb(ofRandom(255), 200, 255);
    lifespan = 255;
}

void Particle::update() {
    position += velocity;
    lifespan -= 1.5;
    if (lifespan < 0) lifespan = 0;
}

void Particle::draw() {
    ofSetColor(color, lifespan);
    ofDrawCircle(position.x, position.y, 3);
}

void ofApp::setup() {
    ofBackground(0, 0, 20); // Set background to a very dark blue to improve visibility of colors and shapes
    ofSetCircleResolution(100); // Smooth circles
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Enable blending for a glowing effect
    ofSetLineWidth(2); // Set line width for circle outlines
    theta = 0; // Initialize theta for spirals
}

void ofApp::update() {
    // Add new particles at random positions around the center
    for (int i = 0; i < 5; i++) {
        float x = ofGetWidth() / 2 + ofRandom(-150, 150);
        float y = ofGetHeight() / 2 + ofRandom(-150, 150);
        particles.push_back(Particle(x, y));
    }

    // Update all particles
    for (auto& particle : particles) {
        particle.update();
    }

    // Remove particles that have faded out
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.lifespan <= 0; }), particles.end());

    // Update theta for spirals
    theta += 0.008; // Slower theta update for a smoother animation
}

void ofApp::draw() {
    float time = ofGetElapsedTimef(); // Get the elapsed time in seconds
    int numCircles = 120; // Increase the number of circles for a more intricate effect
    float spacing = 10; // Adjust distance between circles for a tighter formation

    // Loop through circles and draw them
    for (int i = 0; i < numCircles; i++) {
        float angle = theta + i * 0.1;
        float radiusOffset = 90 * sin(time * 0.08 + i); // Reduced oscillation speed for a smoother effect
        float x = ofGetWidth() / 2 + (i * spacing + radiusOffset) * cos(angle);
        float y = ofGetHeight() / 2 + (i * spacing + radiusOffset) * sin(angle);
        float radius = 12 + 18 * sin(time * 0.12 + i); // Reduced speed for radius change for a more gentle effect

        // Set color based on time and circle index, with more vivid and softer hues for beauty
        ofSetColor(ofColor::fromHsb(fmod((time * 50 + i * 25), 255), 200, 230, 200));
        ofDrawCircle(x, y, radius);

        // Draw a subtle outline for each circle for added depth
        ofNoFill();
        ofSetColor(ofColor::fromHsb(fmod((time * 50 + i * 25), 255), 150, 200, 120));
        ofDrawCircle(x, y, radius + 5);
        ofFill();
    }

    // Draw particles
    for (auto& particle : particles) {
        particle.draw();
    }

    // Draw spiral pattern to enhance the spiritual effect
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    for (int i = 0; i < 1200; i++) {
        float spiralAngle = i * 0.06;
        float spiralRadius = 0.7 * i;
        float x = spiralRadius * cos(spiralAngle + theta);
        float y = spiralRadius * sin(spiralAngle + theta);
        ofSetColor(ofColor::fromHsb(fmod((time * 15 + i), 255), 150, 230, 140));
        ofDrawCircle(x, y, 2);
    }
    ofPopMatrix();

    // Draw radiating lines for additional spiritual effect
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    for (int i = 0; i < 180; i++) {
        float lineAngle = theta + i * TWO_PI / 180;
        float lineLength = 350 + 60 * sin(time * 0.2 + i); // Reduced speed of line length oscillation for smoother visuals
        float x = lineLength * cos(lineAngle);
        float y = lineLength * sin(lineAngle);
        ofSetColor(ofColor::fromHsb(fmod((time * 25 + i * 10), 255), 120, 220, 120));
        ofDrawLine(0, 0, x, y);
    }
    ofPopMatrix();
}
