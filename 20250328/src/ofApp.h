#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

struct Particle {
    ofVec2f pos;
    ofVec2f vel;
    float life;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

private:
    ofVideoGrabber cam;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg, prevGray, diff;

    std::vector<Particle> particles;

    ofFbo trailFbo;

    int camWidth = 640;
    int camHeight = 480;

    void spawnParticle(float x, float y);
    void updateParticles();
    void drawParticles();
    void drawBackground();
};
