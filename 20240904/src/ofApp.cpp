#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    numShapes = 70;  // Number of shapes in the pattern
    mouseXFactor = 0.0f;
    mouseYFactor = 0.0f;

    baseColor = ofColor(200, 100, 255); // Base color for gradient
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // Allocate the framebuffer
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();

    // Slowly fade the background to create a trailing effect
    fbo.begin();
    ofSetColor(0, 0, 0, 10);  // Adjust alpha for a stronger or softer trail
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();

    for (int i = 0; i < numShapes; i++) {
        float x = ofGetWidth() * ofNoise(time + i);
        float y = ofGetHeight() * ofNoise(time + i + 1000);
        float radius = 40 * ofNoise(time + i + 2000) + 20;
        float rotation = ofNoise(time + i + 3000) * 360;

        float r = baseColor.r * ofNoise(time + i + 4000);
        float g = baseColor.g * ofNoise(time + i + 5000);
        float b = baseColor.b * ofNoise(time + i + 6000);

        ofColor shapeColor = ofColor(r, g, b, 200);

        ofPushMatrix();
        ofTranslate(x + mouseXFactor * 200, y + mouseYFactor * 200);
        ofRotateDeg(rotation);

        // Draw a glow effect
        drawGlow(0, 0, radius * 1.5, shapeColor);

        // Draw sacred geometry shapes
        drawSacredGeometry(0, 0, radius);

        ofPopMatrix();
    }

    fbo.end();

    // Draw the FBO content
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::drawSacredGeometry(float x, float y, float radius) {
    ofSetColor(255, 255, 255, 150);  // Soft white for spiritual feel
    float angleStep = TWO_PI / 6;

    for (int i = 0; i < 6; i++) {
        float angle = i * angleStep;
        float cx = cos(angle) * radius;
        float cy = sin(angle) * radius;
        ofDrawCircle(x + cx, y + cy, radius / 3);
    }

    // Central circle
    ofDrawCircle(x, y, radius / 2);
}

//--------------------------------------------------------------
void ofApp::drawGlow(float x, float y, float radius, ofColor color) {
    ofSetColor(color);
    for (int i = 0; i < 10; i++) {
        float glowRadius = radius + i * 2;
        ofSetColor(color.r, color.g, color.b, 128 - i * 12);
        ofDrawCircle(x, y, glowRadius);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Handle key press events here
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    // Handle key release events here
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouseXFactor = (float)x / ofGetWidth();
    mouseYFactor = (float)y / ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // Handle mouse drag events here
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // Handle mouse press events here
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int button){
    // Handle mouse release events here
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    // Handle mouse enter events here
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    // Handle mouse exit events here
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    fbo.allocate(w, h, GL_RGBA32F_ARB);  // Reallocate the FBO if the window is resized
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    // Handle received messages here
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    // Handle drag-and-drop events here
}
