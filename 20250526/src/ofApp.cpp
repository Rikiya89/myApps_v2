#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableAlphaBlending();

    box2d.init();
    box2d.setGravity(0, 0);
    box2d.createBounds();
    box2d.setFPS(60);
}

void ofApp::update() {
    time += 0.01;

    // Spawn controlled particles orbiting outward
    if (ofGetFrameNum() % 4 == 0) {
        float angle = ofRandom(TWO_PI);
        float orbitRadius = ofRandom(60, 220);
        float x = ofGetWidth() / 2 + cos(angle) * orbitRadius;
        float y = ofGetHeight() / 2 + sin(angle) * orbitRadius;

        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(1.0, 0.5, 0.1);
        circle->setup(box2d.getWorld(), x, y, ofRandom(4, 10));
        circles.push_back(circle);
    }

    if (circles.size() > 300) circles.erase(circles.begin());

    for (auto& circle : circles) {
        ofVec2f pos = circle->getPosition();
        float noiseScale = 0.003;
        float flowAngle = ofNoise(pos.x * noiseScale, pos.y * noiseScale, time) * TWO_PI * 4;
        ofVec2f flowForce(cos(flowAngle), sin(flowAngle));
        flowForce *= 2.5;

        // Add spring force to center (soft orbit behavior)
        ofVec2f toCenter = ofVec2f(ofGetWidth()/2, ofGetHeight()/2) - pos;
        toCenter.limit(1.0);  // dampen the spring force
        ofVec2f totalForce = flowForce + toCenter;
        circle->addForce(totalForce, 1.0);
    }

    box2d.update();
}

void ofApp::draw() {
    // Motion trail
    ofSetColor(0, 0, 0, 18);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    for (int i = 0; i < circles.size(); i++) {
        auto& circle = circles[i];
        auto pos = circle->getPosition();

        float dist = ofDist(pos.x, pos.y, ofGetWidth()/2, ofGetHeight()/2);
        float hue = fmod(colorHue + dist * 0.15 + sin(time + i * 0.1) * 40, 255);
        ofColor c = ofColor::fromHsb(hue, 200, 255, 180);
        ofSetColor(c);

        // Add soft pulsing size
        float pulse = 1.0 + 0.3 * sin(time * 3.0 + i);
        ofDrawCircle(pos, circle->getRadius() * pulse);
    }

    colorHue += 0.3;
    if (colorHue > 255) colorHue = 0;
}
