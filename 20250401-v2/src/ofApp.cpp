#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    flowerImg.load("flower.jpg");
    flowerImg.resize(resolutionX, resolutionY);

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (int y = 0; y < resolutionY; ++y) {
        for (int x = 0; x < resolutionX; ++x) {
            ofColor color = flowerImg.getColor(x, y);
            float brightness = color.getBrightness() / 255.0;
            float z = brightness * heightScale;

            mesh.addVertex(glm::vec3(x * meshScale, y * meshScale, z));
            mesh.addColor(color);
        }
    }

    for (int y = 0; y < resolutionY - 1; ++y) {
        for (int x = 0; x < resolutionX - 1; ++x) {
            int i1 = x + y * resolutionX;
            int i2 = (x + 1) + y * resolutionX;
            int i3 = x + (y + 1) * resolutionX;
            int i4 = (x + 1) + (y + 1) * resolutionX;

            mesh.addTriangle(i1, i2, i3);
            mesh.addTriangle(i2, i4, i3);
        }
    }
}

void ofApp::update(){}

void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2 - resolutionX * meshScale / 2,
                ofGetHeight()/2 - resolutionY * meshScale / 2, -200);
    ofRotateDeg(ofGetElapsedTimef() * 10, 0, 1, 0);
    mesh.drawWireframe();  // Try mesh.draw() for full render
    ofPopMatrix();
}
