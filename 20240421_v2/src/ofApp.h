#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class Particle {
public:
    ofPoint pos;
    ofColor color;
    float radius;

    Particle(ofPoint position, ofColor c, float r) : pos(position), color(c), radius(r) {}
    void update() {
        pos.y += ofRandom(-5, 5); // Random motion
        pos.x += ofRandom(-5, 5);
    }
    void draw() {
        ofSetColor(color);
        ofDrawCircle(pos, radius);
    }
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber webcam;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage, grayPrev, grayDiff;
    ofxCvContourFinder contourFinder;

    vector<Particle> particles;
    float threshold;
    bool bLearnBackground;
};
