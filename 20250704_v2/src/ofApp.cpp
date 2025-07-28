// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableSmoothing();
    ofSetCircleResolution(32);

    // Initialize particles
    numParticles = 800;
    particles.resize(numParticles);

    for(int i = 0; i < numParticles; i++){
        particles[i].pos.x = ofRandom(ofGetWidth());
        particles[i].pos.y = ofRandom(ofGetHeight());
        particles[i].vel.x = ofRandom(-2, 2);
        particles[i].vel.y = ofRandom(-2, 2);
        particles[i].size = ofRandom(2, 8);
        particles[i].life = ofRandom(0.5, 1.0);
        particles[i].maxLife = particles[i].life;
        particles[i].hue = ofRandom(0, 360);
    }

    time = 0;
    mouseInfluence = 100;
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.02;

    // Update particles
    for(int i = 0; i < numParticles; i++){
        // Apply noise-based force field
        float noiseX = ofNoise(particles[i].pos.x * 0.003, particles[i].pos.y * 0.003, time * 0.1);
        float noiseY = ofNoise(particles[i].pos.x * 0.003 + 100, particles[i].pos.y * 0.003 + 100, time * 0.1);

        ofVec2f force;
        force.x = (noiseX - 0.5) * 2;
        force.y = (noiseY - 0.5) * 2;



        // Update velocity and position
        particles[i].vel += force * 0.1;
        particles[i].vel *= 0.98; // Damping
        particles[i].pos += particles[i].vel;

        // Wrap around screen
        if(particles[i].pos.x < 0) particles[i].pos.x = ofGetWidth();
        if(particles[i].pos.x > ofGetWidth()) particles[i].pos.x = 0;
        if(particles[i].pos.y < 0) particles[i].pos.y = ofGetHeight();
        if(particles[i].pos.y > ofGetHeight()) particles[i].pos.y = 0;

        // Update life
        particles[i].life -= 0.005;
        if(particles[i].life <= 0){
            // Respawn particle
            particles[i].pos.x = ofRandom(ofGetWidth());
            particles[i].pos.y = ofRandom(ofGetHeight());
            particles[i].vel.x = ofRandom(-1, 1);
            particles[i].vel.y = ofRandom(-1, 1);
            particles[i].life = ofRandom(0.5, 1.0);
            particles[i].maxLife = particles[i].life;
            particles[i].hue = ofRandom(0, 360);
        }

        // Slowly shift hue
        particles[i].hue += 0.5;
        if(particles[i].hue > 360) particles[i].hue -= 360;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // Draw connections between nearby particles
    for(int i = 0; i < numParticles; i++){
        for(int j = i + 1; j < numParticles; j++){
            float distance = particles[i].pos.distance(particles[j].pos);

            if(distance < 80){
                float alpha = ofMap(distance, 0, 80, 0.3, 0.0);
                float avgHue = (particles[i].hue + particles[j].hue) / 2;

                ofSetColor(ofColor::fromHsb(avgHue, 200, 255, alpha * 255));
                ofDrawLine(particles[i].pos, particles[j].pos);
            }
        }
    }

    // Draw particles
    for(int i = 0; i < numParticles; i++){
        float alpha = particles[i].life / particles[i].maxLife;
        ofSetColor(ofColor::fromHsb(particles[i].hue, 255, 255, alpha * 200));

        ofDrawCircle(particles[i].pos.x, particles[i].pos.y, particles[i].size * alpha);

        // Draw glow effect
        ofSetColor(ofColor::fromHsb(particles[i].hue, 100, 255, alpha * 50));
        ofDrawCircle(particles[i].pos.x, particles[i].pos.y, particles[i].size * alpha * 2);
    }

    ofDisableBlendMode();

    // Draw info
    ofSetColor(255, 100);
    ofDrawBitmapString("Particles: " + ofToString(numParticles), 20, 20);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 20, 40);
    ofDrawBitmapString("Press SPACE to reset, R to randomize colors", 20, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        // Reset particles
        setup();
    }
    if(key == 'r' || key == 'R'){
        // Randomize colors
        for(int i = 0; i < numParticles; i++){
            particles[i].hue = ofRandom(0, 360);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
