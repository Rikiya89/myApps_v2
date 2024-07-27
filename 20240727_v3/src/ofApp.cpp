#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);

    webcam.setVerbose(true);
    webcam.setup(640, 480);

    colorImg.allocate(640, 480);
    grayImg.allocate(640, 480);
    prevGrayImg.allocate(640, 480);
    diffImg.allocate(640, 480);

    gui.setup();
    gui.add(threshold.set("Threshold", 30, 0, 255));
    gui.add(maxParticles.set("Max Particles", 500, 0, 1000));  // Add max particles control

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);  // Allocate the FBO

    // Load the Haar cascade file for face detection
    haarFinder.setup("haarcascade_frontalface_default.xml");
}

void ofApp::update(){
    webcam.update();
    if (webcam.isFrameNew()) {
        colorImg.setFromPixels(webcam.getPixels());
        grayImg = colorImg;

        // Face detection
        haarFinder.findHaarObjects(grayImg);

        // Compute the difference between the current frame and the previous frame
        diffImg.absDiff(prevGrayImg, grayImg);
        diffImg.threshold(threshold);

        contourFinder.findContours(diffImg, 20, (340 * 240) / 3, 10, true);

        prevGrayImg = grayImg;

        // Add particles at the locations of detected motion
        for (int i = 0; i < contourFinder.nBlobs; i++) {
            addParticles(contourFinder.blobs[i].pts);
        }

        // Update particles with motion attraction
        for (auto& particle : particles) {
            if (contourFinder.nBlobs > 0) {
                particle.update(contourFinder.blobs[0].centroid);
            } else {
                particle.update(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
            }
        }

        // Remove dead particles
        particles.erase(remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.isDead(); }), particles.end());

        // Limit the number of particles
        if (particles.size() > maxParticles) {
            particles.erase(particles.begin(), particles.begin() + (particles.size() - maxParticles));
        }
    }
}

void ofApp::draw(){
    // Draw the webcam feed to the FBO
    fbo.begin();
    ofClear(0, 0, 0, 255);
    colorImg.draw(0, 0);
    
    // Mask or blur the detected face(s)
    for (unsigned int i = 0; i < haarFinder.blobs.size(); i++) {
        ofRectangle cur = haarFinder.blobs[i].boundingRect;
        
        // Option 1: Mask with a solid color
        ofFill();
        ofSetColor(0, 0, 0); // You can change the color to any solid color
        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
        
        // Option 2: Strong blur effect (comment out if using solid color)
        /*
         ofPixels facePixels = webcam.getPixels();
         ofImage faceImg;
         faceImg.setFromPixels(facePixels);
         faceImg.crop(cur.x, cur.y, cur.width, cur.height);
         for (int j = 0; j < 5; ++j) {  // Multiple downscale-upscale passes for stronger blur
         faceImg.resize(cur.width / 10, cur.height / 10);  // Downscale
         faceImg.resize(cur.width, cur.height);  // Upscale to create the blur effect
         }
         faceImg.draw(cur.x, cur.y);
         */
    }
    
    contourFinder.draw();
    fbo.end();
    
    // Draw the FBO with blending
    ofSetColor(255, 255, 255, 100);  // Adjust alpha for blending
    fbo.draw(0, 0);
    
    // Draw particles
    for (auto& particle : particles) {
        particle.draw();
    }
    
}
