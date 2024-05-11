#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255); // White background
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int tileSize = 100;
    int numTiles = 5;
    ofSetColor(0, 0, 0); // Black color for lines

    for(int i = 0; i < numTiles; i++){
        for(int j = 0; j < numTiles; j++){
            int x = i * tileSize;
            int y = j * tileSize;
            drawTile(x, y, tileSize);
        }
    }
}

void ofApp::drawTile(int x, int y, int size){
    // Base color of the tile
    ofSetColor(200, 100, 50); // Brownish color
    ofDrawRectangle(x, y, size, size);

    // Add your pattern design here
    ofSetColor(0, 0, 0); // Black for the pattern
    ofDrawLine(x, y, x + size, y + size);
    ofDrawLine(x + size, y, x, y + size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

// [Rest of the methods follow the same structure]
