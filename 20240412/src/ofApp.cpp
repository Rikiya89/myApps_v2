#include "ofApp.h"

struct Particle {
    ofPoint position;
    ofPoint velocity;
    std::vector<ofPoint> trail;
};

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    cam.setAutoDistance(true);
    cam.setDistance(800);

    ofEnableDepthTest();
    ofEnableSmoothing();

    light1.setPosition(200, 300, 400);
    light1.setDiffuseColor(ofColor::white);
    light1.enable();

    light2.setPosition(-200, -300, 400);
    light2.setDiffuseColor(ofColor(255, 220, 200));
    light2.enable();

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    for (int i = 0; i < 1000; i++) {
        Particle particle;
        particle.position = ofPoint(ofRandomWidth(), ofRandomHeight(), ofRandom(-500, 500));
        particles.push_back(particle);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    cam.orbitDeg(0.6 * cos(time * 0.2), 0.4 * sin(time * 0.2), cam.getDistance());

    for (auto& particle : particles) {
        ofVec3f center(0, 0, 0);
        ofVec3f direction = center - particle.position;
        float distance = direction.length();
        direction.normalize();
        direction *= 0.05 * distance;
        particle.velocity.interpolate(direction, 0.05);
        particle.position += particle.velocity;

        if (particle.trail.size() > 0) {
            if (particle.position.distance(particle.trail.back()) > 1) {
                particle.trail.push_back(particle.position);
                if (particle.trail.size() > 20) {
                    particle.trail.erase(particle.trail.begin());
                }
            }
        } else {
            particle.trail.push_back(particle.position);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    material.begin();

    // Draw Flower of Life
    int layers = 5;
    int numCircles = 10;
    float baseRadius = 30.0;
    float distance = baseRadius * 1.75;

    for (int k = 0; k < layers; k++) {
        for (int i = 0; i < numCircles; i++) {
            for (int j = 0; j < numCircles; j++) {
                float x = i * distance;
                float y = j * distance;
                float z = k * distance - layers / 2 * distance;

                if (k % 2 == 0) x += baseRadius;
                if (i % 2 == 0) y += baseRadius;

                float radius = baseRadius + 5 * sin(time + x * 0.1 + y * 0.1 + z * 0.1);

                ofSetColor(ofColor::fromHsb(255 * float(i) / numCircles, 180, 255));

                ofPushMatrix();
                ofTranslate(x - numCircles / 2 * distance, y - numCircles / 2 * distance, z);
                ofDrawSphere(0, 0, 0, radius);
                ofPopMatrix();
            }
        }
    }

    material.end();

    // Draw particles and trails
    for (const auto& particle : particles) {
        ofSetColor(255, 100, 150);  // Particle color
        ofDrawSphere(particle.position, 2);

        ofSetColor(255, 100, 150, 50);  // Trail color
        for (size_t i = 0; i < particle.trail.size() - 1; i++) {
            ofDrawLine(particle.trail[i], particle.trail[i + 1]);
        }
    }

    cam.end();
}

// Implement other event handlers if needed...

