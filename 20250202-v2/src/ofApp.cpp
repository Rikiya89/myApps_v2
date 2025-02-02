#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Set up the environment.
    ofSetFrameRate(60);
    ofBackground(10, 10, 10);

    // Initialize our collection of boxes.
    boxes.resize(numBoxes);
    for (int i = 0; i < numBoxes; i++){
         // Set each box to a random size.
         float size = ofRandom(10, 50);
         boxes[i].set(size);
         // Place each box at a random position within a 3D volume.
         boxes[i].setPosition(ofRandom(-200,200), ofRandom(-200,200), ofRandom(-200,200));
    }

    // Generate a random offset to seed the noise evolution.
    timeOffset = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();

    // Update each box’s position using Perlin noise to create organic motion.
    for (int i = 0; i < numBoxes; i++){
         // Get a noise value based on the box index and elapsed time.
         float noiseVal = ofNoise(i * 0.1, time * 0.5 + timeOffset);

         // Map the noise value to a small change in position.
         float dx = ofMap(noiseVal, 0, 1, -1, 1);
         float dy = ofMap(noiseVal, 0, 1, -1, 1);
         float dz = ofMap(noiseVal, 0, 1, -1, 1);

         // Update the box's current position.
         ofVec3f pos = boxes[i].getPosition();
         pos.x += dx;
         pos.y += dy;
         pos.z += dz;
         boxes[i].setPosition(pos);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Begin the camera transformation.
    cam.begin();

    // Loop over all boxes and draw them.
    for(auto &box : boxes){
         // Use the x-position to determine a hue for each box.
         float hue = ofMap(box.getPosition().x, -200, 200, 0, 255, true);
         ofColor col;
         col.setHsb(hue, 200, 255);
         ofSetColor(col);

         // Draw the box as a wireframe.
         box.drawWireframe();
    }

    // End the camera transformation.
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' to reset the boxes to new random positions.
    if(key == 'r'){
         for (int i = 0; i < numBoxes; i++){
              boxes[i].setPosition(ofRandom(-200,200), ofRandom(-200,200), ofRandom(-200,200));
         }
    }
}
