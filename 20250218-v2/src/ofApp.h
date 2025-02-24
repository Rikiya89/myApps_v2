// ofApp.h
#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

private:
    ofEasyCam cam;
    vector<ofVec3f> points;

    float radius = 100;
    int numCircles = 6;
    float rotationAngle = 0.0;
    float pulseFactor = 0.0;
    float waveOffset = 0.0;

    void drawFlowerOfLife();
    void drawMetatronCube();
    void drawStar();
};

#endif // OFAPP_H
