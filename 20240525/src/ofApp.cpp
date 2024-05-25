#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();

    numShapes = 300;
    hueOffset = 0;
    for(int i = 0; i < numShapes; i++) {
        positions.push_back(ofPoint(ofRandomWidth(), ofRandomHeight()));
        radii.push_back(ofRandom(10, 50));
        colors.push_back(ofColor::fromHsb(ofRandom(255), 255, 255));
        angles.push_back(ofRandom(TWO_PI));
        shapes.push_back(ofRandom(0, 4)); // 0: Circle, 1: Rectangle, 2: Triangle, 3: Star
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    hueOffset += 0.5; // Increase hue offset for color cycling
    if(hueOffset > 255) hueOffset -= 255;
    for(int i = 0; i < numShapes; i++) {
        positions[i].x += ofMap(ofNoise(time * 0.1, i), 0, 1, -2, 2);
        positions[i].y += ofMap(ofNoise(time * 0.1, i + 1000), 0, 1, -2, 2);
        radii[i] = 10 + 20 * sin(ofGetElapsedTimef() + i);
        angles[i] += ofRandom(-0.02, 0.02);
        float hue = fmod(ofGetElapsedTimef() * 10 + i * 10 + hueOffset, 255); // Dynamic hue change
        colors[i] = ofColor::fromHsb(hue, 255, 255);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofSetColor(0, 0, 0, 10); // Fading effect
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableAlphaBlending();
    for(int i = 0; i < numShapes; i++) {
        ofSetColor(colors[i], 200); // Increase alpha for brighter colors
        ofPushMatrix();
        ofTranslate(positions[i]);
        ofRotateRad(angles[i]);
        switch(shapes[i]) {
            case 0:
                ofDrawCircle(0, 0, radii[i]);
                break;
            case 1:
                ofDrawRectangle(-radii[i]/2, -radii[i]/2, radii[i], radii[i]);
                break;
            case 2:
                ofDrawTriangle(-radii[i], radii[i], radii[i], radii[i], 0, -radii[i]);
                break;
            case 3:
                ofBeginShape();
                for (int j = 0; j < 5; j++) {
                    float angle = ofDegToRad(72 * j);
                    float x = radii[i] * cos(angle);
                    float y = radii[i] * sin(angle);
                    ofVertex(x, y);
                }
                ofEndShape(true);
                break;
        }
        ofPopMatrix();
    }

    ofSetColor(255, 100); // Brighter semi-transparent white for the connecting lines
    for(int i = 0; i < numShapes; i++) {
        for(int j = i+1; j < numShapes; j++) {
            float dist = ofDist(positions[i].x, positions[i].y, positions[j].x, positions[j].y);
            if(dist < 150) {
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }
    fbo.end();

    fbo.draw(0, 0);
}
