#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(60);

    // Generate random points in 3D space
    int totalPoints = 1500;  // Optimized for performance
    for (int i = 0; i < totalPoints; i++) {
        float x = ofRandom(-300, 300);
        float y = ofRandom(-300, 300);
        float z = ofRandom(-300, 300);
        points.push_back(ofVec3f(x, y, z));
    }

    time = 0.0f;
}

void ofApp::update() {
    time += 0.01f;
}

void ofApp::draw() {
    // Faint background to simulate glow trail
    ofSetColor(0, 0, 0, 18);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    float t = ofGetElapsedTimef();

    // Camera slow auto-rotation
    cam.setPosition(500 * sin(t * 0.2), 300 * sin(t * 0.15), 500 * cos(t * 0.2));
    cam.lookAt(glm::vec3(0, 0, 0));
    cam.begin();

    vector<ofVec3f> animatedPoints;
    animatedPoints.reserve(points.size());

    for (auto& p : points) {
        // Rotate around Y axis
        auto rotated = glm::vec3(glm::rotate(glm::mat4(1), t * 0.1f, glm::vec3(0, 1, 0)) * glm::vec4(p.x, p.y, p.z, 1.0f));

        // Offset using Perlin noise
        auto pos = rotated + p.getNormalized() * (50 * ofNoise(p * 0.005f + t));
        animatedPoints.push_back(pos);

        // Pastel/chakra style color
        float hue = fmod(t * 10 + p.z * 0.05f, 255);
        ofColor c; c.setHsb(hue, 100, 255);

        // Noise-based size variation
        float s = ofMap(ofNoise(p * 0.005f + t), 0, 1, 0.5, 2.5);

        // Draw glow
        ofSetColor(c, 40);
        ofDrawSphere(pos, s * 2.5);

        // Draw core
        ofSetColor(c, 220);
        ofDrawSphere(pos, s);
    }

    // Connect nearby points with soft blue lines
    for (size_t i = 0; i < animatedPoints.size(); ++i) {
        for (size_t j = i + 1; j < i + 30 && j < animatedPoints.size(); ++j) {
            float d = (animatedPoints[i] - animatedPoints[j]).length();
            if (d < 50) {
                float alpha = ofMap(d, 0, 50, 200, 0);
                ofSetColor(180, 220, 255, alpha);
                ofSetLineWidth(1.0);
                ofDrawLine(animatedPoints[i], animatedPoints[j]);
            }
        }
    }

    cam.end();
}


