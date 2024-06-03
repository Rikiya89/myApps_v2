#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    time = 0;

    // Setup light
    light.setup();
    light.setPosition(1000, 1000, 2000);
    light.enable();

    // Setup gradient colors
    startColor = ofColor(0, 0, 128); // Dark Blue
    endColor = ofColor(0, 128, 128); // Teal
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.01;
    mesh.clear();
    int width = ofGetWidth();
    int height = ofGetHeight();
    float scale = 100.0;

    for (int y = 0; y < height; y += 10) {
        for (int x = 0; x < width; x += 10) {
            float noiseValue = ofNoise(x / scale, y / scale, time);
            float z = ofMap(noiseValue, 0, 1, -200, 200);
            mesh.addVertex(glm::vec3(x, y, z));
            mesh.addColor(ofColor::fromHsb(ofMap(z, -200, 200, 0, 255), 255, 255));
        }
    }

    for (int y = 0; y < height - 10; y += 10) {
        for (int x = 0; x < width - 10; x += 10) {
            int index1 = x / 10 + y / 10 * (width / 10);
            int index2 = (x + 10) / 10 + y / 10 * (width / 10);
            int index3 = x / 10 + (y + 10) / 10 * (width / 10);
            mesh.addIndex(index1);
            mesh.addIndex(index2);
            mesh.addIndex(index1);
            mesh.addIndex(index3);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw gradient background
    ofMesh gradient;
    gradient.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    gradient.addVertex(glm::vec3(0, 0, 0));
    gradient.addColor(startColor);
    gradient.addVertex(glm::vec3(ofGetWidth(), 0, 0));
    gradient.addColor(startColor);
    gradient.addVertex(glm::vec3(0, ofGetHeight(), 0));
    gradient.addColor(endColor);
    gradient.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0));
    gradient.addColor(endColor);
    gradient.draw();

    cam.begin();
    ofEnableDepthTest();
    light.enable();
    mesh.draw();
    light.disable();
    ofDisableDepthTest();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
