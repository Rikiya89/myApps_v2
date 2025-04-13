#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofBackground(0);
    cam.setDistance(300);
    ofEnableDepthTest();
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    float time = ofGetElapsedTimef();
    ofSetColor(ofColor::fromHsb(fmod(time * 20, 255), 255, 255));
    drawRecursiveTetrahedron(ofVec3f(0, 0, 0), 100, 4, time);
    
    cam.end();
}

void ofApp::drawRecursiveTetrahedron(ofVec3f pos, float size, int level, float time) {
    if (level == 0) return;
    
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateDeg(time * (30 + level * 10), sin(time * 0.5) * 2, cos(time * 0.3) * 2, 1);
    float scaleFactor = 1.0 + 0.15 * sin(time + level);
    ofScale(scaleFactor, scaleFactor, scaleFactor);
    
    drawTetrahedron(size, level);
    
    float newSize = size * 0.5;
    for (int i = 0; i < 4; i++) {
        ofVec3f newPos = pos + tetrahedronOffsets[i] * size * 0.7 * (1.0 + 0.15 * sin(time + i));
        drawRecursiveTetrahedron(newPos, newSize, level - 1, time);
    }
    
    ofPopMatrix();
}

void ofApp::drawTetrahedron(float size, int level) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    float h = sqrt(2.0/3.0) * size;
    float r = size / sqrt(3);
    
    ofVec3f v0(0, -h / 2, 0);
    ofVec3f v1(-r, h / 2, r);
    ofVec3f v2(r, h / 2, r);
    ofVec3f v3(0, h / 2, -size);
    
    mesh.addVertex(v0);
    mesh.addVertex(v1);
    mesh.addVertex(v2);
    mesh.addVertex(v3);
    
    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(0, 2, 3);
    mesh.addTriangle(0, 3, 1);
    mesh.addTriangle(1, 2, 3);
    
    ofSetColor(ofColor::fromHsb(static_cast<int>(level * 50 + ofGetElapsedTimef() * 30) % 255, 255, 255, 200));
    mesh.draw();
    
    ofSetColor(255, 100);
    mesh.drawWireframe();
}

// Offsets for recursive placement
ofVec3f ofApp::tetrahedronOffsets[4] = {
    ofVec3f(0, -0.5, 0),
    ofVec3f(-0.5, 0.5, 0.5),
    ofVec3f(0.5, 0.5, 0.5),
    ofVec3f(0, 0.5, -1.0)
};
