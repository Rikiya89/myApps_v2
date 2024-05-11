#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);

    pointLight.setDiffuseColor(ofColor(255));
    pointLight.setSpecularColor(ofColor(255, 255, 255));
    pointLight.setPosition(-300, 300, 600);

    directionalLight.setDiffuseColor(ofColor(255));
    directionalLight.setSpecularColor(ofColor(255, 255, 255));
    directionalLight.setDirectional();
    directionalLight.setOrientation(glm::vec3(0, 90, 0));

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255));

    radius = 300;
    noiseFactor = 0;
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();

    auto resolution = 200;
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            float x = radius * sin(i * TWO_PI / resolution) * cos(j * TWO_PI / resolution);
            float y = radius * sin(i * TWO_PI / resolution) * sin(j * TWO_PI / resolution);
            float z = radius * cos(i * TWO_PI / resolution);
            mesh.addVertex(ofPoint(x, y, z));
            mesh.addColor(ofColor::fromHsb(ofRandom(255), 255, 200));
        }
    }

    for (int y = 0; y < resolution - 1; y++) {
        for (int x = 0; x < resolution - 1; x++) {
            mesh.addIndex(x + y * resolution);
            mesh.addIndex((x + 1) + y * resolution);
            mesh.addIndex(x + (y + 1) * resolution);
            mesh.addIndex((x + 1) + y * resolution);
            mesh.addIndex((x + 1) + (y + 1) * resolution);
            mesh.addIndex(x + (y + 1) * resolution);
        }
    }

    for (int i = 0; i < 1000; i++) {
        particles.push_back(Particle());
    }
}

void ofApp::update() {
    noiseFactor += 0.01;
    for (auto& vertex : mesh.getVertices()) {
        float noise = ofNoise(vertex.x * 0.05, vertex.y * 0.05, vertex.z * 0.05, noiseFactor);
        glm::vec3 displacement = glm::vec3((ofNoise(noise) - 0.5) * 5.0, (ofNoise(noise) - 0.5) * 5.0, (ofNoise(noise) - 0.5) * 5.0);
        vertex += displacement;
    }

    for (auto& particle : particles) {
        glm::vec3 target = mesh.getVertex(int(ofRandom(mesh.getVertices().size())));
        particle.seek(target);
        particle.update();
    }
}

void ofApp::draw() {
    ofEnableDepthTest();

    pointLight.enable();
    directionalLight.enable();
    material.begin();

    easyCam.begin();
    mesh.draw();
    for (auto& particle : particles) {
        particle.draw();
    }
    easyCam.end();

    material.end();
    ofDisableLighting();
    ofDisableDepthTest();
}
