#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();

    // Initialize color palette with theme colors
    colors.push_back(ofColor::fromHex(0x362d78));
    colors.push_back(ofColor::fromHex(0x523fa3));
    colors.push_back(ofColor::fromHex(0x916ccc));
    colors.push_back(ofColor::fromHex(0xbda1e5));
    colors.push_back(ofColor::fromHex(0xc8c0e9));
    colors.push_back(ofColor::fromHex(0x84bae7));
    colors.push_back(ofColor::fromHex(0x516ad4));
    colors.push_back(ofColor::fromHex(0x333f87));
    colors.push_back(ofColor::fromHex(0x293039));
    colors.push_back(ofColor::fromHex(0x283631));

    // Create particles
    int numParticles = 150;
    for(int i = 0; i < numParticles; i++){
        Particle p;

        // Random position in a sphere
        float radius = ofRandom(100, 400);
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(PI);

        p.pos.x = radius * sin(phi) * cos(theta);
        p.pos.y = radius * sin(phi) * sin(theta);
        p.pos.z = radius * cos(phi);

        // Random velocity
        p.vel.x = ofRandom(-0.5, 0.5);
        p.vel.y = ofRandom(-0.5, 0.5);
        p.vel.z = ofRandom(-0.5, 0.5);

        // Random color from palette
        p.color = colors[(int)ofRandom(colors.size())];

        // Random size
        p.size = ofRandom(10, 40);

        // Random rotation
        p.rotation = ofRandom(360);
        p.rotationSpeed = ofRandom(-2, 2);

        // Random rotation axis
        p.axis = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)).normalize();

        // Random shape type
        p.shapeType = (int)ofRandom(3);

        particles.push_back(p);
    }

    // Setup lighting
    ofEnableLighting();
    light.setPosition(200, 300, 400);
    light.enable();

    // Set background color to darkest theme color
    ofBackground(ofColor::fromHex(0x293039));

    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.01;

    // Update particles
    for(int i = 0; i < particles.size(); i++){
        Particle& p = particles[i];

        // Add perlin noise movement
        float noiseX = ofNoise(p.pos.x * 0.005, p.pos.y * 0.005, time) - 0.5;
        float noiseY = ofNoise(p.pos.y * 0.005, p.pos.z * 0.005, time + 100) - 0.5;
        float noiseZ = ofNoise(p.pos.z * 0.005, p.pos.x * 0.005, time + 200) - 0.5;

        p.vel.x += noiseX * 0.1;
        p.vel.y += noiseY * 0.1;
        p.vel.z += noiseZ * 0.1;

        // Add attraction to center
        ofVec3f toCenter = -p.pos;
        toCenter.normalize();
        p.vel += toCenter * 0.05;

        // Apply velocity
        p.pos += p.vel;

        // Damping
        p.vel *= 0.95;

        // Keep particles within bounds
        float maxDist = 500;
        if(p.pos.length() > maxDist){
            p.pos.normalize();
            p.pos *= maxDist;
            p.vel *= -0.5;
        }

        // Update rotation
        p.rotation += p.rotationSpeed;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    // Draw some background grid lines for depth
    ofPushStyle();
    ofSetColor(colors[0], 30);
    ofNoFill();
    for(int i = 0; i < 5; i++){
        float size = 100 + i * 100;
        ofDrawBox(0, 0, 0, size, size, size);
    }
    ofPopStyle();

    // Draw connecting lines between nearby particles
    ofPushStyle();
    ofSetLineWidth(1);
    for(int i = 0; i < particles.size(); i++){
        for(int j = i + 1; j < particles.size(); j++){
            float dist = particles[i].pos.distance(particles[j].pos);
            if(dist < 150){
                float alpha = ofMap(dist, 0, 150, 100, 0);
                ofSetColor(particles[i].color, alpha);
                ofDrawLine(particles[i].pos, particles[j].pos);
            }
        }
    }
    ofPopStyle();

    // Draw particles
    for(int i = 0; i < particles.size(); i++){
        Particle& p = particles[i];

        ofPushMatrix();
        ofTranslate(p.pos.x, p.pos.y, p.pos.z);
        ofRotateDeg(p.rotation, p.axis.x, p.axis.y, p.axis.z);

        // Set material properties
        ofSetColor(p.color);

        // Draw different shapes
        switch(p.shapeType){
            case 0: // Sphere
                ofDrawSphere(0, 0, 0, p.size);
                break;
            case 1: // Box
                ofDrawBox(0, 0, 0, p.size);
                break;
            case 2: // Cone
                ofDrawCone(0, 0, 0, p.size * 0.7, p.size * 1.5);
                break;
        }

        // Draw wireframe outline
        ofPushStyle();
        ofNoFill();
        ofSetColor(255, 50);
        ofSetLineWidth(0.5);
        switch(p.shapeType){
            case 0:
                ofDrawSphere(0, 0, 0, p.size);
                break;
            case 1:
                ofDrawBox(0, 0, 0, p.size);
                break;
            case 2:
                ofDrawCone(0, 0, 0, p.size * 0.7, p.size * 1.5);
                break;
        }
        ofPopStyle();

        ofPopMatrix();
    }

    // Add some rotating rings
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);

    for(int i = 0; i < 3; i++){
        ofPushMatrix();

        float ringSize = 200 + i * 100;
        ofColor ringColor = colors[i % colors.size()];
        ofSetColor(ringColor, 80);

        ofRotateDeg(time * 10 + i * 30, 1, 0, 0);
        ofRotateDeg(time * 15 + i * 45, 0, 1, 0);

        ofDrawCircle(0, 0, 0, ringSize);

        ofPopMatrix();
    }
    ofPopStyle();

    cam.end();

    // Draw UI
    ofDisableLighting();
    ofSetColor(colors[3], 200);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 2), 10, 20);
    ofDrawBitmapString("Particles: " + ofToString(particles.size()), 10, 40);
    ofDrawBitmapString("Press 'r' to reset | Mouse to rotate camera", 10, 60);
    ofEnableLighting();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r' || key == 'R'){
        setup();
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
