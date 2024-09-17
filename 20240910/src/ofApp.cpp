#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(20);  // Dark background to highlight the pattern
    ofSetCircleResolution(100);  // Smooth circles
    time = 0;  // Initialize time variable
    ofEnableSmoothing();  // Enable smoothing for better visuals
}

//--------------------------------------------------------------
void ofApp::update(){
    time += ofGetLastFrameTime() * 0.5;  // Adjust time speed for smooth animation
}

//--------------------------------------------------------------
void ofApp::draw(){
    float baseRadius = 200;  // Base radius of the entire pattern
    int numShapes = 36;  // Increase the number of shapes in the radial pattern
    int numLoops = 16;  // Number of looping curves for complex spirograph
    float centerX = ofGetWidth() / 2;  // X center of the pattern
    float centerY = ofGetHeight() / 2;  // Y center of the pattern

    float scaleFactor = 1.0 + 0.2 * sin(time * 2);  // Breathing effect, the whole pattern expands and contracts

    // Loop through each shape in the radial symmetry
    for(int i = 0; i < numShapes; i++){
        float angle = ofDegToRad((360 / numShapes) * i);  // Calculate the angle for radial symmetry

        // Calculate x, y positions for the points based on sine and cosine
        float xOffset = cos(angle) * baseRadius * scaleFactor;
        float yOffset = sin(angle) * baseRadius * scaleFactor;

        // Draw looping spirograph-like curves
        for (int j = 0; j < numLoops; j++) {
            float loopAngle = time * 1.5 + j * TWO_PI / numLoops;  // Varying angle for the curves
            float loopRadius = 80 + sin(time * 2 + j * 0.5) * 40;  // Dynamic radius for fluid animation

            // Calculate positions for the spirograph curves
            float x = centerX + cos(angle + loopAngle) * loopRadius * scaleFactor;
            float y = centerY + sin(angle + loopAngle) * loopRadius * scaleFactor;

            // Gradient colors: transitioning smoothly between hues
            float hue = fmodf(time * 10 + i * 10 + j * 5, 255);  // Cycle through hues based on time and position
            ofColor color;
            color.setHsb(hue, 200, 255, 150 + sin(time + j) * 100);  // Gradient with alpha transparency
            ofSetColor(color);

            // Draw the point with motion trail
            ofDrawCircle(x + xOffset, y + yOffset, 10);

            // Subtle motion trail effect
            ofSetColor(color, 50);  // Lower alpha for trail
            ofDrawCircle(x + xOffset * 0.9, y + yOffset * 0.9, 20);  // Slightly offset to create trailing effect
        }
    }
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
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
