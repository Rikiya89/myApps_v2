#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Set up the webcam at the default resolution
    webcam.setup(640, 480);

    // Load a shader (make sure to have a shader file in your bin/data folder)
    shader.load("shaders/shader");

    // Additional setup can be done here
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update(); // Update the frame from webcam
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (webcam.isFrameNew()) { // Check if the new frame is available
        shader.begin();
        // Pass any uniforms you need for your shader here
        shader.setUniform1f("time", ofGetElapsedTimef());
        shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

        webcam.draw(0, 0); // Draw the webcam input
        shader.end();
    }
}

//--------------------------------------------------------------
int main(){
    ofSetupOpenGL(1024, 768, OF_WINDOW); // Setup window
    ofRunApp(new ofApp()); // Run your app
}
