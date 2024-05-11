#pragma once

#include "ofMain.h"

class Particle {
public:
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 acc;
    ofColor color;
    float maxSpeed;
    float maxForce;

    Particle() {
        pos = glm::vec3(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
        vel = glm::vec3(0, 0, 0);
        acc = glm::vec3(0, 0, 0);
        color = ofColor::fromHsb(ofRandom(255), 255, 255);
        maxSpeed = ofRandom(1, 4);
        maxForce = 0.1;
    }

    void update() {
        vel += acc;
        vel = glm::clamp(vel, -maxSpeed, maxSpeed);
        pos += vel;
        acc *= 0;
    }

    void applyForce(glm::vec3 force) {
        acc += force;
    }

    void seek(glm::vec3 target) {
        glm::vec3 desired = target - pos;
        desired = glm::normalize(desired) * maxSpeed;
        glm::vec3 steer = desired - vel;
        steer = glm::clamp(steer, -maxForce, maxForce);
        applyForce(steer);
    }

    void draw() {
        ofSetColor(color);
        ofDrawSphere(pos, 2);
    }
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam easyCam;
    ofMesh mesh;
    vector<Particle> particles;
    ofLight pointLight, directionalLight;
    ofMaterial material;
    float radius;
    float noiseFactor;
};
