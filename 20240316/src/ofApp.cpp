#include "ofApp.h"

void ofApp::setup() {
    cam.initGrabber(1820, 1080);
    prevFrame.allocate(cam.getWidth(), cam.getHeight(), OF_IMAGE_GRAYSCALE);
    diff.allocate(cam.getWidth(), cam.getHeight(), OF_IMAGE_GRAYSCALE);
    ofSetBackgroundColor(0, 0, 0);
}

void ofApp::update() {
    cam.update();

    if(cam.isFrameNew()) {
        ofImage grayImage;
        grayImage.setFromPixels(cam.getPixels());
        grayImage.setImageType(OF_IMAGE_GRAYSCALE);

        ofPixels & pixels = grayImage.getPixels();
        for (int i = 0; i < pixels.size(); i++) {
            diff.getPixels()[i] = abs(pixels[i] - prevFrame.getPixels()[i]);
        }
        diff.update();
        prevFrame.setFromPixels(grayImage.getPixels());

        // Update particles
        for (int i = particles.size() - 1; i >= 0; i--) {
            particles[i].update();
            if (particles[i].isDead()) {
                particles.erase(particles.begin() + i);
            }
        }
    }
}

void ofApp::draw() {
    ofClear(0, 0, 0);
    drawGenerativeShapes();

    for (auto &particle : particles) {
        particle.draw();
    }
}

void ofApp::drawGenerativeShapes() {
    unsigned char * pixels = diff.getPixels().getData();
    for (int i = 0; i < cam.getWidth(); i += 10) {
        for (int j = 0; j < cam.getHeight(); j += 10) {
            int index = j * cam.getWidth() + i;
            if (pixels[index] > 25) {
                addParticle(i, j);
            }
        }
    }
}

void ofApp::addParticle(int x, int y) {
    Particle newParticle(ofPoint(x, y));
    particles.push_back(newParticle);
}
