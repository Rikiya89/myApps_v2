#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofVideoGrabber cam; // Webcam feed
    ofxCvColorImage colorImg; // Color image
    ofxCvGrayscaleImage grayImage; // Grayscale image
    ofxCvGrayscaleImage grayBg; // Background image
    ofxCvGrayscaleImage grayDiff; // Difference image

    ofxCvContourFinder contourFinder; // Contour finder

    bool bLearnBackground = true;
    int threshold = 80;

    vector<ofColor> colors; // Colors for gradient

    ofxPanel gui;
    ofParameter<int> particleCount;
    ofParameter<float> particleSpeed;
    ofParameter<int> blobAlpha;
    ofParameter<int> bgAlpha;
    ofParameter<float> glowRadius;

    void updateColorPalette();

    float time;

    vector<ofVec2f> motionPositions; // Positions of detected motion
};

class Particle {
public:
    ofVec2f position;
    ofVec2f velocity;
    ofColor color;
    float lifespan;

    Particle(ofVec2f pos, ofColor col) {
        position = pos;
        color = col;
        velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        lifespan = 255;
    }

    void update(float speed, const vector<ofVec2f>& motionPositions) {
        if (!motionPositions.empty()) {
            ofVec2f closestPoint;
            float minDist = FLT_MAX;
            for (const auto& point : motionPositions) {
                float dist = position.distance(point);
                if (dist < minDist) {
                    minDist = dist;
                    closestPoint = point;
                }
            }
            ofVec2f direction = (closestPoint - position).normalized();
            velocity += direction * 0.1;
        }
        position += velocity * speed;
        lifespan -= 2.0;  // Decrease lifespan
    }

    void draw() {
        if (lifespan > 0) {
            ofSetColor(color, lifespan);
            ofDrawCircle(position, 3);
        }
    }

    bool isDead() {
        return lifespan <= 0;
    }
};
