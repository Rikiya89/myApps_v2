#include "ofApp.h"

vector<Particle> particles;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    cam.setup(1280, 720); // Updated resolution

    colorImg.allocate(1280, 720); // Updated resolution
    grayImage.allocate(1280, 720); // Updated resolution
    grayBg.allocate(1280, 720); // Updated resolution
    grayDiff.allocate(1280, 720); // Updated resolution

    // Initialize gradient colors
    colors.push_back(ofColor(255, 0, 0));
    colors.push_back(ofColor(0, 255, 0));
    colors.push_back(ofColor(0, 0, 255));
    colors.push_back(ofColor(255, 255, 0));
    colors.push_back(ofColor(0, 255, 255));

    gui.setup();
    gui.add(particleCount.set("Particle Count", 50, 10, 500));  // Reduced default particle count
    gui.add(particleSpeed.set("Particle Speed", 2.0, 0.1, 10.0));
    gui.add(blobAlpha.set("Blob Alpha", 100, 0, 255));
    gui.add(bgAlpha.set("Background Alpha", 50, 0, 255));
    gui.add(glowRadius.set("Glow Radius", 10.0, 1.0, 20.0));

    time = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    updateColorPalette();

    if (cam.isFrameNew()) {
        colorImg.setFromPixels(cam.getPixels());
        grayImage = colorImg;

        if (bLearnBackground) {
            grayBg = grayImage;
            bLearnBackground = false;
        }

        // Take the absolute difference of the current frame and background
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
    }

    // Update particles
    for (auto& particle : particles) {
        particle.update(particleSpeed, motionPositions);
    }

    // Remove particles that are out of screen or dead
    particles.erase(remove_if(particles.begin(), particles.end(), [](Particle& p) {
        return p.position.x < 0 || p.position.x > 1280 || p.position.y < 0 || p.position.y > 720 || p.isDead(); // Updated resolution
    }), particles.end());

    // Increment time
    time += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0); // Set background to black

    ofSetColor(255, 255, 255);
    colorImg.draw(0, 0);

    // Draw background difference with some transparency
    ofSetColor(255, 255, 255, bgAlpha);
    grayDiff.draw(0, 0);

    motionPositions.clear();

    // Find contours of the motion
    contourFinder.findContours(grayDiff, 20, (1280*720)/3, 10, true); // Updated resolution

    for (int i = 0; i < contourFinder.nBlobs; i++) {
        ofxCvBlob& blob = contourFinder.blobs[i];
        float blobSize = blob.area;
        float radius = ofMap(blobSize, 20, (1280*720)/3, 10, 60); // Updated resolution

        ofColor color = colors[i % colors.size()];

        // Draw glowing circles
        for (int j = 0; j < 10; j++) {
            float alpha = ofMap(j, 0, 9, blobAlpha, 0);
            ofSetColor(color, alpha);
            ofDrawCircle(blob.centroid.x, blob.centroid.y, radius * ofMap(j, 0, 9, 1.0, 0.1));
        }

        // Dynamic smaller circles around the main circle
        for (int j = 0; j < 5; j++) {  // Reduced the number of smaller circles
            ofSetColor(colors[(i+j) % colors.size()], 100);
            ofDrawCircle(blob.centroid.x + ofRandom(-50, 50), blob.centroid.y + ofRandom(-50, 50), radius * ofRandom(0.1, 0.3));
        }

        // Add particles
        for (int j = 0; j < particleCount / contourFinder.nBlobs; j++) {  // Distribute particles evenly across blobs
            particles.push_back(Particle(blob.centroid, colors[j % colors.size()]));
        }

        // Store motion positions
        motionPositions.push_back(blob.centroid);
    }

    // Draw particles
    for (auto& particle : particles) {
        particle.draw();
    }

    // Draw GUI
    gui.draw();

    // Draw instructions
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Press 'b' to reset background", 10, 20);
    ofDrawBitmapString("Press 'c' to change color palette", 10, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'b') {
        bLearnBackground = true;
        grayBg = grayImage; // Add this line to reset the background
    }
    else if (key == 'c') {
        // Change color palette
        colors.clear();
        for (int i = 0; i < 5; i++) {
            colors.push_back(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
        }
    }
}

//--------------------------------------------------------------
void ofApp::updateColorPalette() {
    // Update colors over time for dynamic color changes
    for (size_t i = 0; i < colors.size(); i++) {
        colors[i].r = ofMap(sin(time + i * 0.3), -1, 1, 50, 255);
        colors[i].g = ofMap(sin(time + i * 0.6), -1, 1, 50, 255);
        colors[i].b = ofMap(sin(time + i * 0.9), -1, 1, 50, 255);
    }
}
