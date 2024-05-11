#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 640;  // width of the webcam video
    camHeight = 480; // height of the webcam video

    // Set up the webcam
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update the video frame
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

    if(vidGrabber.isFrameNew()){
        // Draw the webcam video
        vidGrabber.draw(0, 0);

        // You can add more effects here
    }
}

//--------------------------------------------------------------
int main(){
    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new ofApp());
}
