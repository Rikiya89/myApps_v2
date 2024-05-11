#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0, 0, 0); // Set background to black
    webcam.setup(1080, 720); // Updated resolution
    motionPixels.allocate(1080, 720, OF_PIXELS_RGB);
    motionTexture.allocate(motionPixels);
}

void ofApp::update(){
    webcam.update();

    if(webcam.isFrameNew()){
        processedPixels = webcam.getPixels();

        if(previousPixels.isAllocated()){
            for(int y = 0; y < processedPixels.getHeight(); y++) {
                for(int x = 0; x < processedPixels.getWidth(); x++) {
                    int index = y * processedPixels.getWidth() + x;
                    if(abs(processedPixels[index] - previousPixels[index]) > 50){
                        motionPixels[index] = 255;
                        if(particles.size() < MAX_PARTICLES){
                            addParticle(x, y);
                        }
                    } else {
                        motionPixels[index] = 0;
                    }
                }
            }
            motionTexture.loadData(motionPixels);
        }
        previousPixels = processedPixels;
    }

    for(auto it = particles.begin(); it != particles.end(); ){
        it->update();
        if(it->isDead()){
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}

void ofApp::draw(){
    texture.draw(0, 0);

    for(auto& p : particles){
        p.draw();
    }
}

void ofApp::addParticle(int x, int y){
    ofColor color = ofColor::fromHsb(ofRandom(255), 255, 255, 200);
    ofVec2f velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    float radius = ofRandom(2, 6);
    float lifespan = 150;
    particles.push_back(Particle(ofPoint(x, y), velocity, color, radius, lifespan));
}
