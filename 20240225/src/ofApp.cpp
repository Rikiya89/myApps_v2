#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();

    // Mesh setup
    mesh.setMode(OF_PRIMITIVE_LINES);
    int numVertices = 300; // Reduced for clarity and performance
    for(int i = 0; i < numVertices; i++) {
        glm::vec3 position = glm::vec3(ofRandom(-600, 600), ofRandom(-600, 600), ofRandom(-600, 600));
        mesh.addVertex(position);
        mesh.addColor(ofColor(0)); // Initial color set to black

        speeds.push_back(glm::vec3(ofRandom(-3, 3), ofRandom(-3, 3), ofRandom(-3, 3)));
    }

    light.setPosition(1000, 1000, 2000);
    light.enable();

    hue = 0; // Initialize hue for color dynamics
}

void ofApp::update(){
    float time = ofGetElapsedTimef();
    hue += 0.1; // Slowly change hue over time
    if(hue > 255) hue = 0;

    mesh.clearIndices();
    for(size_t i = 0; i < mesh.getVertices().size(); i++) {
        float noiseX = ofNoise(mesh.getVertices()[i].x * 0.005, time * 0.1);
        float noiseY = ofNoise(mesh.getVertices()[i].y * 0.005, time * 0.1);
        float noiseZ = ofNoise(mesh.getVertices()[i].z * 0.005, time * 0.1);
        glm::vec3 noiseDirection = glm::vec3(noiseX, noiseY, noiseZ) - glm::vec3(0.5);
        mesh.getVertices()[i] += noiseDirection * speeds[i];

        // Dynamic color based on Perlin noise
        float colorNoise = ofNoise(mesh.getVertices()[i].x * 0.005, mesh.getVertices()[i].y * 0.005, time * 0.05);
        ofColor c;
        c.setHsb(fmod(hue + colorNoise * 100, 255), 255, 255);
        mesh.setColor(i, c);

        // Create connections based on distance
        for(size_t j = i + 3; j < mesh.getVertices().size(); j++) {
            float distance = glm::distance(mesh.getVertices()[i], mesh.getVertices()[j]);
            if(distance < 270) { // Adjust for desired density of lines
                mesh.addIndex(i);
                mesh.addIndex(j);
            }
        }
    }
}

void ofApp::draw(){
    cam.begin();
    ofEnableLighting();
    light.draw();
    mesh.draw();
    ofDisableLighting();
    cam.end();
}
