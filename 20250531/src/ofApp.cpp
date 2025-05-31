#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Additive blending for glow
    ofSetCircleResolution(64);

    gridSize = 20; // Lower = faster rendering
    spacing = 30.0f;
    time = 0.0f;

    mesh.setMode(OF_PRIMITIVE_POINTS);

    for (int z = 0; z < gridSize; ++z){
        for (int y = 0; y < gridSize; ++y){
            for (int x = 0; x < gridSize; ++x){
                ofVec3f pos(
                    (x - gridSize / 2) * spacing,
                    (y - gridSize / 2) * spacing,
                    (z - gridSize / 2) * spacing
                );
                mesh.addVertex(pos);
                mesh.addColor(ofFloatColor(1.0, 1.0, 1.0)); // initial white color
            }
        }
    }

    glPointSize(4.0); // Make points visible
}

void ofApp::update(){
    time += 0.01;

    for (int i = 0; i < mesh.getNumVertices(); ++i){
        ofVec3f original = mesh.getVertex(i);
        ofVec3f dir = original.getNormalized();  // ✅ Fix: use getNormalized()

        float n = ofNoise(original.x * 0.005, original.y * 0.005, original.z * 0.005, time);
        ofVec3f offset = dir * (n - 0.5) * 40; // subtle animated displacement

        mesh.setVertex(i, original + offset);

        float hue = fmod(n * 255 + time * 30, 255);
        mesh.setColor(i, ofColor::fromHsb(hue, 180, 255)); // pastel-like colors
    }
}

void ofApp::draw(){
    cam.begin();

    ofPushMatrix();
    float angle = ofGetElapsedTimef() * 10.0;
    ofRotateDeg(angle, 0.2, 1.0, 0.4); // rotate for more dynamic effect

    mesh.drawVertices(); // render the point cloud
    ofPopMatrix();

    cam.end();
}
