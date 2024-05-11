#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);

    // Setup FBO
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    // Initialize time
    time = 0;

    // Add initial particles
    for (int i = 0; i < 300; i++) {
        addParticle();
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    time += 0.005;

    fbo.begin();
    ofEnableAlphaBlending();

    // Dynamic gradient background
    ofColor topColor;
    topColor.setHsb(sin(time * 0.5) * 128 + 128, 180, 255);
    ofColor bottomColor;
    bottomColor.setHsb(sin(time * 0.5 + PI) * 128 + 128, 180, 255);
    ofBackgroundGradient(topColor, bottomColor, OF_GRADIENT_CIRCULAR);

    for (auto& particle : particles) {
        // Update for more fluid movement
        particle.velocity.x += ofSignedNoise(particle.position.x * 0.01, particle.position.y * 0.01, time) * 0.2;
        particle.velocity.y += ofSignedNoise(particle.position.y * 0.01, particle.position.x * 0.01, time) * 0.2;
        particle.position += particle.velocity;

        // Boundary conditions
        if (particle.position.x < 0) particle.position.x = ofGetWidth();
        if (particle.position.x > ofGetWidth()) particle.position.x = 0;
        if (particle.position.y < 0) particle.position.y = ofGetHeight();
        if (particle.position.y > ofGetHeight()) particle.position.y = 0;

        // Pulsating effect on radius and color
        particle.radius = ofMap(sin(time + particle.position.x * 0.01), -1, 1, 2, 6);
        float brightness = ofMap(cos(time + particle.position.y * 0.01), -1, 1, 128, 255);
        particle.color.setBrightness(brightness);

        // Draw particles with motion blur
        ofSetColor(particle.color, 100);
        for (int i = 0; i < 5; i++) {
            float ratio = float(i) / 5;
            ofDrawCircle(particle.position - particle.velocity * ratio, particle.radius * (1 - ratio));
        }
    }

    connectParticles();
    ofDisableAlphaBlending();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::addParticle() {
    Particle newParticle;
    newParticle.position = glm::vec2(ofRandomWidth(), ofRandomHeight());
    newParticle.velocity = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1));
    newParticle.color = ofColor::fromHsb(ofRandom(255), 200, 255);
    newParticle.radius = ofRandom(2, 6);

    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::connectParticles() {
    float maxDistance = 100;

    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            float distance = glm::distance(particles[i].position, particles[j].position);
            if (distance < maxDistance) {
                // Color shift based on the angle of the line
                float angle = atan2(particles[j].position.y - particles[i].position.y, particles[j].position.x - particles[i].position.x);
                ofColor lineColor;
                lineColor.setHsb(ofMap(angle, -PI, PI, 0, 255), 255, 255);
                ofSetColor(lineColor, ofMap(distance, 0, maxDistance, 255, 0));

                ofSetLineWidth(ofMap(distance, 0, maxDistance, 3, 1));
                ofDrawLine(particles[i].position, particles[j].position);
            }
        }
    }
    ofSetLineWidth(1);  // Reset line width
}
