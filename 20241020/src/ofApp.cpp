#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);  // Set background to black

    // Set up dynamic lighting with smooth movement
    pointLight.setDiffuseColor(ofFloatColor(0.8, 0.8, 0.8));
    pointLight.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    pointLight.setPosition(300, 300, 300);
    pointLight.enable();

    pointLight2.setDiffuseColor(ofFloatColor(0.5, 0.5, 0.7));
    pointLight2.setSpecularColor(ofFloatColor(0.6, 0.6, 0.8));
    pointLight2.setPosition(-400, 200, -200);
    pointLight2.enable();

    // Set up material with high shininess for reflective surfaces
    material.setShininess(150);
    material.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

    // Create a dynamic wave-like mesh
    int gridSize = 150;
    float spacing = 8;
    for(int y = -gridSize; y < gridSize; y++) {
        for(int x = -gridSize; x < gridSize; x++) {
            float z = sin(x * 0.1) * 50 + cos(y * 0.1) * 50;
            mesh.addVertex(ofVec3f(x * spacing, y * spacing, z));
        }
    }

    // Add gradient color to the mesh for smooth blending
    for (int i = 0; i < mesh.getNumVertices(); i++) {
        float brightness = ofNoise(mesh.getVertex(i).x * 0.05, mesh.getVertex(i).y * 0.05);
        mesh.addColor(ofFloatColor(0.8 + brightness * 0.2, 0.6 + brightness * 0.4, 0.9 + brightness * 0.1));
    }

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Set up the reflective, rotating, and deforming sphere
    sphere.setRadius(200);
    sphere.setPosition(0, 0, 0);

    // Set up a particle system for ambient effect
    for (int i = 0; i < numParticles; i++) {
        ofVec3f pos(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
        particles.push_back(pos);
        particleSpeeds.push_back(ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
    }
}

void ofApp::update(){
    float time = ofGetElapsedTimef();  // Get current time

    // Update mesh vertices for continuous wave-like motion
    for (int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f v = mesh.getVertex(i);
        float noise = ofNoise(v.x * 0.05, v.y * 0.05, time * timeSpeed);
        v.z = sin(v.x * 0.05 + time * 0.5) * 50 + cos(v.y * 0.05 + time * 0.5) * 50 + noise * 30;
        mesh.setVertex(i, v);
    }

    // Animate lights for a dynamic effect
    pointLight.setPosition(300 * sin(time * 0.5), 300 * cos(time * 0.5), 300);
    pointLight2.setPosition(-300 * cos(time * 0.5), 200, -300 * sin(time * 0.5));

    // Rotate and deform the sphere for an organic effect
    sphere.rotateDeg(1.0, 1.0, 1.0, 0.0);
    sphere.rotateDeg(0.5, 0.0, 0.0, 1.0);

    // Deform the sphere slightly to give it a breathing effect
    auto& sphereVertices = sphere.getMesh().getVertices();
    for (int i = 0; i < sphereVertices.size(); i++) {
        sphereVertices[i] *= 1.0 + 0.01 * sin(time * 0.5 + sphereVertices[i].x * 0.1);
    }

    // Update particles with random movement
    for (int i = 0; i < numParticles; i++) {
        particles[i] += particleSpeeds[i];
        if (particles[i].length() > 600) {  // Bring particles back to the center if too far
            particles[i].set(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
        }
    }

    // Camera path: smoothly zoom in/out and rotate
    float camDistance = 600 + 100 * sin(time * 0.3);
    float camX = 400 * cos(time * 0.2);
    float camY = 300 * sin(time * 0.2);
    cam.setPosition(camX, camY, camDistance);
    cam.lookAt(sphere.getPosition());
}

void ofApp::draw(){
    cam.begin();  // Begin camera view

    pointLight.enable();
    pointLight2.enable();

    material.begin();  // Start material reflection

    // Set line width to increase the thickness of the wireframe lines
    ofSetLineWidth(2);  // Adjust this value to increase/decrease line width

    // Draw the dynamic, glowing mesh
    mesh.drawWireframe();

    // Draw the rotating, reflective, and deforming sphere
    sphere.drawWireframe();

    // Draw ambient particles
    for (auto& particle : particles) {
        ofDrawSphere(particle, 2);  // Draw small glowing spheres
    }

    material.end();  // End material reflection

    cam.end();  // End camera view
}
