#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setup(640, 480);  // Initialize webcam
    // Initialize petals
    petals.clear();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();  // Update webcam

    if(cam.isFrameNew()){
        // Example logic to add petals based on movement in the webcam feed
        // This is a simple placeholder logic, you might want to replace it with something that analyzes the frame
        if(ofRandom(1) > 0.95){
            addPetals(ofRandom(cam.getWidth()), ofRandom(cam.getHeight()), 10);
        }

        // Update petal positions
        for(auto &petal : petals){
            petal.y += ofRandom(1, 5);  // Petals fall down
            if(petal.y > cam.getHeight()){
                petal.y = 0;  // Reset petal to the top
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0, 0);  // Draw the webcam input

    // Draw petals
    ofSetColor(255, 0, 0);  // Set color to red for the petals
    for(auto &petal : petals){
        ofDrawCircle(petal.x, petal.y, 10);  // Draw a petal as a circle
    }
}

//--------------------------------------------------------------
void ofApp::addPetals(int x, int y, int amount){
    for(int i = 0; i < amount; i++){
        petals.push_back(ofPoint(x + ofRandom(-15, 15), y + ofRandom(-15, 15)));
    }
}


