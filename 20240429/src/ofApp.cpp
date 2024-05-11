#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    webcam.setup(640, 480); // Set up webcam with 640x480 resolution
    previousFrame.allocate(640, 480, OF_IMAGE_COLOR); // Allocate memory for images
    diffImage.allocate(640, 480, OF_IMAGE_COLOR);
    ofSetFrameRate(60); // Set frame rate
    ofBackground(50); // Set a dark background
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update(); // Update the webcam

    if(webcam.isFrameNew()) { // Check if a new frame has been received
        ofPixels & pixels = webcam.getPixels(); // Get the current frame pixels
        for(int i = 0; i < pixels.size(); i++) {
            // Calculate the absolute difference between the current frame and the previous frame
            // And apply a random factor to the difference for a more dynamic effect
            int noise = ofRandom(-30, 30);
            diffImage.getPixels()[i] = abs(pixels[i] - previousFrame.getPixels()[i] + noise);
        }
        diffImage.update(); // Update the difference image

        // Store the current frame to be used in the next update
        previousFrame.setFromPixels(webcam.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 100, 100, 128); // Set a translucent red color
    diffImage.draw(0, 0); // Draw the difference image

    // Blend mode for more abstract visual effects
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(100, 255, 100, 128); // Change color to a translucent green
    diffImage.draw(0, 0); // Draw the same image offset for a ghosting effect
    ofDisableBlendMode();
}
