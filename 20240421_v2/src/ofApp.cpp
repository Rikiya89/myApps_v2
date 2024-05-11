#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    webcam.setup(1080, 970);
    colorImg.allocate(webcam.getWidth(), webcam.getHeight());
    grayImage.allocate(webcam.getWidth(), webcam.getHeight());
    grayPrev.allocate(webcam.getWidth(), webcam.getHeight());
    grayDiff.allocate(webcam.getWidth(), webcam.getHeight());

    threshold = 80;
    bLearnBackground = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update();

    if (webcam.isFrameNew()) {
        colorImg.setFromPixels(webcam.getPixels());

        grayImage = colorImg;
        if (bLearnBackground) {
            grayPrev = grayImage; // Store the previous image
            bLearnBackground = false;
        }

        // Compute the absolute difference and threshold it
        grayDiff.absDiff(grayPrev, grayImage);
        grayDiff.threshold(threshold);
        grayPrev = grayImage;

        // Find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // Also, find holes is set to true so we will get interior contours as well.
        contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);

        // Update and create fewer particles in regions where motion was detected
        for (int i = 0; i < contourFinder.nBlobs; i++) {
            for (int j = 0; j < contourFinder.blobs[i].nPts; j += 40) {  // Increased sampling gap for fewer particles
                ofPoint pt = contourFinder.blobs[i].pts[j];
                ofColor col = colorImg.getPixels().getColor(pt.x, pt.y);
                particles.push_back(Particle(pt, col, ofRandom(10, 15))); // Bigger and fewer particles
            }
        }

        // Update particles
        for (int i = 0; i < particles.size(); i++) {
            particles[i].update();
            if (particles[i].pos.x < 0 || particles[i].pos.x > webcam.getWidth() || particles[i].pos.y < 0 || particles[i].pos.y > webcam.getHeight()) {
                particles.erase(particles.begin() + i);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    for (auto& p : particles) {
        p.draw();
    }
    contourFinder.draw();
}
