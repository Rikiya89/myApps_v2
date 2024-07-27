#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    webcam.setVerbose(true);
    webcam.setup(640, 480);

    colorImg.allocate(640, 480);

    gui.setup();
    gui.add(threshold.set("Threshold", 128, 0, 255));
}

void ofApp::update(){
    webcam.update();
    if(webcam.isFrameNew()){
        colorImg.setFromPixels(webcam.getPixels());
    }
}

void ofApp::draw(){
    colorImg.draw(0, 0);
    gui.draw();
}
