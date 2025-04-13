#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowTitle("Cosmic Motion Art");
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableAlphaBlending();

    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30);
    cam.initGrabber(camWidth, camHeight);

    colorImg.allocate(camWidth, camHeight);
    grayImg.allocate(camWidth, camHeight);
    prevGray.allocate(camWidth, camHeight);
    diff.allocate(camWidth, camHeight);

    trailFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    trailFbo.begin();
    ofClear(0, 0, 0, 255);
    trailFbo.end();
}

void ofApp::update(){
    cam.update();
    if (cam.isFrameNew()) {
        colorImg.setFromPixels(cam.getPixels());
        grayImg = colorImg;

        if (prevGray.bAllocated) {
            diff.absDiff(grayImg, prevGray);
            diff.threshold(25);
        }

        prevGray = grayImg;

        unsigned char* pixels = diff.getPixels().getData();
        for (int y = 0; y < camHeight; y += 10) {
            for (int x = 0; x < camWidth; x += 10) {
                int index = x + y * camWidth;
                if (pixels[index] > 100) {
                    spawnParticle(x, y);
                }
            }
        }
    }

    updateParticles();
}

void ofApp::draw(){
    drawBackground();

    trailFbo.begin();

    // Fade the FBO slightly for trail effect
    ofSetColor(0, 0, 0, 20);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    drawParticles();

    trailFbo.end();

    ofSetColor(255);
    trailFbo.draw(0, 0);
}

void ofApp::drawBackground(){
    ofColor top = ofColor(10, 10, 30);
    ofColor bottom = ofColor(0, 0, 5);

    ofMesh bg;
    bg.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    bg.addVertex(glm::vec3(0, 0, 0));               bg.addColor(top);
    bg.addVertex(glm::vec3(0, ofGetHeight(), 0));   bg.addColor(bottom);
    bg.addVertex(glm::vec3(ofGetWidth(), 0, 0));    bg.addColor(top);
    bg.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0)); bg.addColor(bottom);
    bg.draw();
}

void ofApp::spawnParticle(float x, float y){
    Particle p;
    p.pos.set(x, y);
    p.vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    p.life = ofRandom(30, 120);
    particles.push_back(p);
}

void ofApp::updateParticles(){
    for (auto& p : particles) {
        p.pos += p.vel;
        p.vel *= 0.97;
        p.life -= 0.9;
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const Particle& p){ return p.life <= 0; }), particles.end());
}

void ofApp::drawParticles(){
    for (auto& p : particles) {
        float alpha = ofMap(p.life, 0, 120, 0, 200);
        float hue = ofMap(p.life, 0, 120, 160, 280); // Cosmic palette
        ofColor c = ofColor::fromHsb(fmod(hue + ofGetFrameNum() * 0.5, 255), 180, 255, alpha);
        ofSetColor(c);
        ofDrawCircle(p.pos, 1.5);
    }
}
