#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class Particle {
public:
    ofVec2f position;
    ofVec2f velocity;
    ofColor color;
    float lifespan;
    vector<ofVec2f> trail;

    Particle(ofVec2f pos) {
        position = pos;
        velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
        color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
        lifespan = 255.0;  // Initial lifespan
    }

    void update(ofVec2f attractionPoint) {
        ofVec2f direction = attractionPoint - position;
        direction.normalize();
        velocity += direction * 0.1;  // Adjust the attraction strength
        position += velocity;
        if (position.x < 0 || position.x > ofGetWidth()) velocity.x *= -1;
        if (position.y < 0 || position.y > ofGetHeight()) velocity.y *= -1;
        lifespan -= 2.0;  // Decrease lifespan

        // Update trail
        trail.push_back(position);
        if (trail.size() > 10) {  // Limit trail length
            trail.erase(trail.begin());
        }

        // Randomly change color
        if (ofRandom(1) < 0.01) {
            color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
        }
    }

    void draw() {
        ofSetColor(color, lifespan);
        ofDrawCircle(position, 3);

        // Draw trail
        for (size_t i = 0; i < trail.size(); i++) {
            ofSetColor(color, lifespan * (i / (float)trail.size()));
            ofDrawCircle(trail[i], 2);
        }
    }

    bool isDead() {
        return lifespan < 0;
    }
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber webcam;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage prevGrayImg;
    ofxCvGrayscaleImage diffImg;
    ofxCvContourFinder contourFinder;

    ofxPanel gui;
    ofParameter<float> threshold;
    ofParameter<int> maxParticles; // Parameter for maximum particles

    vector<Particle> particles;
    void addParticles(const ofPolyline& line);

    ofFbo fbo;  // Framebuffer object for rendering the webcam feed

    // Face detection
    ofxCvHaarFinder haarFinder;
};
